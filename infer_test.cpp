/*
 * infer_test.cpp
 *
 *  Created on: 2014年12月5日
 *      Author: xiewenbo
 */

#include "lda_infer.h"
#include "timer.h"
int main() {
  infer* ldatool = new infer;
  int numTopics = 200;
  cout << "enter main." << endl;
  ldatool->init();
  string doc1[] = { "特价", "酒店", "哪个", "好" };
  string doc2[] = { "资格", "留学", "建材" };
  string doc3[] = { "如家", "酒店", "团购", "特价", "房间" };
  string doc4[] = { "特价", "酒店", "哪个", "好" };
  string doc5[] = { "什么", "项目", "比较", "赚钱" };
  string doc6[] = { "加盟", "代理", "创业", "赚钱" };
  Timer timer;
  timer.start();
  double* pz1 = ldatool->inferenceFast(doc1, 4);
  double* pz2 = ldatool->inferenceFast(doc2, 3);
  double* pz3 = ldatool->inferenceFast(doc3, 5);
  double* pz4 = ldatool->inferenceFast(doc4, 4);
  double* pz5 = ldatool->inferenceFast(doc5, 4);
  double* pz6 = ldatool->inferenceFast(doc6, 4);
  cout << klDivergence(pz1, pz2, numTopics) << endl;
  cout << klDivergence(pz1, pz3, numTopics) << endl;
  cout << klDivergence(pz1, pz4, numTopics) << endl;
  cout << klDivergence(pz1, pz5, numTopics) << endl;
  cout << klDivergence(pz5, pz6, numTopics) << endl;
  cout << klDivergence(pz1, pz6, numTopics) << endl;
  timer.end();
  cout <<"cost:" << timer.cost()<<endl;
  delete ldatool;
  cout << "exit." << endl;
  return 0;
}
