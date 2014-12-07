#include "lda_infer.h"

//global paramter
void infer::calculateConditionalProbability(string word,int* ndz,double* pz,double doclength){
	map<string,int*>::iterator c_it = nwz.find(word);
	int* counts;
	if(c_it!=nwz.end()){
		counts = c_it->second;
	}else{
		return;
	}
	double sum = 0.0;
	double normalizer = (doclength + numTopics*alpha - 1);
	for(int i=0;i<numTopics;i++){
		pz[i] = (counts[i] + beta) / (ndz[i] + nwz.size() * beta - 1)
							* (ndz[i] + alpha) / normalizer;
		sum += pz[i];
	}
	for (int i = 0; i < numTopics; i++) {
		pz[i] /= sum;
	}
}
//remove the words not in model file
string* infer::removeUnknownWords(string* words,int length,int* res_len){
	vector<string> remainWords;
	int i = 0;
	for(;i<length;i++){
		string w = *(words + i);
		cout<<"look for word:"<<w<<endl;
		std::map<string,int>::iterator it = wordMap.find(w);
		if(it == wordMap.end())continue;
		remainWords.push_back(w);
		cout<<"find word:"<<w<<endl;
	}
	string* result = new string[remainWords.size()];
	i=0;
	vector<string>::const_iterator c_it = remainWords.begin();
	for(;c_it!=remainWords.end();c_it++){
		*(result+i) = *c_it;
		i++;
	}
	*res_len = remainWords.size();
	return result;
}
bool infer::loadModel(string modelFile){
	cout<<"debug:"<<modelFile<<endl;
	std::ifstream fin(modelFile.c_str());
	if(!fin)return false;
	string line;
	getline(fin,line);
	cout<<"alpha:"<<line<<endl;
	alpha = atof(line.c_str());
	getline(fin,line);
	cout<<"beta:"<<line<<endl;
	beta = atof(line.c_str());
	getline(fin,line);
	cout<<"numTopics:"<<line<<endl;
	numTopics = atoi(line.c_str());
	getline(fin,line);
	cout<<"n:"<<line<<endl;
	n = atoi(line.c_str());
	topicSum = new int[numTopics];
	while (getline(fin, line)) {
		std::vector<std::string> cols;
		split(" ", line, cols);
		string word = cols[0];
		int i,sum = 0;
		int* counts = new int[numTopics + 1];
	//	cout<<"debug:"<<line<<endl;
		for(i=0;i<numTopics;i++){
			*(counts+i) = atoi(cols[i+1].c_str());
			topicSum[i]+=*(counts+i);
			sum+=counts[i];
		}
		counts[numTopics] = sum;
		totalSum+=sum;
		nwz.insert(pair<string,int*>(cols[0],counts));
		words.push_back(word);
	}
	fin.close();
	ndz = new int[numTopics];
	return true;
}
bool infer::init(){
	loadModel("datainput.lda.model");
	return true;
}
int infer::sampleInDistribution(double* dist,int dist_len){
	double p = doubleRandom();
	double sum = 0;
	for(int i=0;i<dist_len;i++){
		sum+=dist[i];
		if(sum>=p){
			return i;
		}
	}
	return dist_len - 1;
}
void infer::inferenceFastImpl(string* doc,int doc_size,double* p){
	int i;
	for(i=0;i<numTopics;i++){
		*(p+i) = 0.0;
	}
	for(i=0;i<doc_size;i++){
		map<string,int*>::iterator it = nwz.find(*(doc+i));
		if(it==nwz.end()){
      cout<<"can't find word:"<<*(doc+i)<<endl;
	  }else{
      cout<<"find word:"<<*(doc+i)<<endl;
    }
    int* counts = it->second;
		int k;
		for(k=0;k<numTopics;k++){
			if(it == nwz.end()){
				*(p+k)+=LOG_MIN_PROB;
			}else{
				double num = (*(counts+k) + n * beta)
						/ (*(topicSum+k)+n * beta * nwz.size());
				*(p+k)+=log(fabs(num));
			}
		}
	}
	double norm = 0.0;
	for(i=0;i<numTopics;i++){
		norm+=exp(*(p+i));
	}
	for(i=0;i<numTopics;i++){
		*(p+i) = exp(*(p+i))/norm;
	}
}
double* infer::inferenceFast(string* doc,int doc_size){
	double* p = new double[numTopics];
  int i;
  for(i=0;i<doc_size;i++){
    cout<<"word:"<<*(doc+i)<<"."<<endl;
  }
	inferenceFastImpl(doc,doc_size,p);
	return p;
}
void infer::inference (string* words, int words_len, double* pz,
		int pz_length,
		int numBurnInIterations,
		int numSamplingIterations){
	int res_len = 0;
	words = removeUnknownWords(words,words_len,&res_len);
	int* z = new int[words_len];
	for(int i=0;i<numTopics;i++){
		*(ndz+i) = 0;
	}
	srand((unsigned)time(NULL));
	for(int i=0;i<words_len;i++){
		int rand_topic = rand()%numTopics;
		*(z+i) = rand_topic;
		*(ndz+rand_topic) = *(ndz+rand_topic)+1;
	}

	//Burn-in
	for (int i=0; i < numBurnInIterations; i++) {
		for(int j=0;j<words_len;j++){
			int oldTopic = z[j];
			--ndz[oldTopic];
			calculateConditionalProbability(words[j],ndz,pz,words_len);
			int newTopic = sampleInDistribution(pz,pz_length);
			z[j] = newTopic;
			++ndz[newTopic];
		}
	}

	// Inference.
	for(int i=0;i<numSamplingIterations;i++){
		for(int j=0;j<words_len;j++){
			calculateConditionalProbability(words[j],ndz,pz,words_len);
			int newTopic = sampleInDistribution(pz,pz_length);
			z[j] = newTopic;
			++ndz[newTopic];
		}
	}

	double norm = 0.0;
	for(int i=0;i<pz_length;i++){
		pz[i] = ndz[i] + alpha;
		norm+=pz[i];
	}
	for(int i=0;i<pz_length;i++){
		pz[i]/=norm;
	}
}

double* infer::inference(string* words,int words_len){
	double* dist = new double[numTopics];
	inference(words,words_len,dist,numTopics,30,10);
	return dist;
}
void printDocs(string* p,int doc_size){
  int i;
  for(i=0;i<doc_size;i++){
    cout<<*(p+i)<<endl;
  }
}
/*
void test(){
	cout<<"test"<<endl;
	wordMap.insert(pair<string,int>("xiewenbo",1));
	wordMap.insert(pair<string,int>("nicholas",1));
	string str_arr[] = {"xiewenbo","nich"};
	cout<<"debug"<<endl;
	string* p_str = str_arr;
	int res_size = 0;
	string* result = removeUnknownWords(p_str,2,&res_size);
	cout<<"remain size="<<res_size<<endl;
	int i;
	if(result)for(i=0;i<res_size;i++){
		cout<<*(result+i)<<endl;
	}
}*/
