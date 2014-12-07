#!/bin/sh
rm -rf infer
g++ infer.cpp file_reader.h StringUtils.h StringUtils.cc kltool.h -o infer 
