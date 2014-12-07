/*
 * kltool.h
 *
 *  Created on: 2014年12月4日
 *      Author: xiewenbo
 */

#include <iostream>
#include <string>
#include <math.h>
#include "kltool.h"
using namespace std;

//double log2 = log(2);
double klDivergence(double* p1,double* p2,int size){
	double kldiv = 0.0;
	int i;
	for(i=0;i<size;i++){
		if(*(p1)==0)continue;
		if(*(p2)==0)continue;
    double d1 = *(p1+i);
    double d2 = *(p2+i);
		kldiv+= d1 * log(d1/d2);
	}
	return (double)kldiv/log(2);
}


