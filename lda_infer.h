/*
 * lda_infer.h
 *
 *  Created on: 2014年12月5日
 *      Author: xiewenbo
 */

#ifndef LDA_INFER_H_
#define LDA_INFER_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "StringUtils.h"
#include "kltool.h"
#include <math.h>
#include <time.h>
using namespace std;
using namespace oir;
#define LOG_MIN_PROB -7
class infer{
private:
	std::map<string,int> wordMap;
	std::map<string,int*> nwz;
	std::vector<string> words;
	int numTopics,n;
	int* ndz;
	double alpha,beta;
	int* topicSum;
	int totalSum ;

public:
	~infer(){
		if(ndz)delete ndz;
		if(topicSum)delete topicSum;
		if(nwz)nwz.clear();
	}
	double doubleRandom(){
		double num = rand() % 100000;
		double p = num / 100000;
		return p;
	}
	double intRandom(int mode){
		double num = rand() % mode;
		return num;
	}
	bool loadModel(string modelFile);
	bool init();
	void calculateConditionalProbability(string word,int* ndz,double* pz,double doclength);
	string* removeUnknownWords(string* words,int length,int* res_len);
	int sampleInDistribution(double* dist,int dist_len);
	void inferenceFastImpl(string* doc,int doc_size,double* p);
	double* inferenceFast(string* doc,int doc_size);
	void inference (string* words, int words_len, double* pz,
			int pz_length,int numBurnInIterations,int numSamplingIterations);
	double* inference(string* words,int words_len);
};

#endif /* LDA_INFER_H_ */
