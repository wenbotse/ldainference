infer_test:infer_test.o infer.o kltool.o StringUtils.o
	g++  infer_test.o infer.o kltool.o StringUtils.o -o infer
infer_test.o:infer_test.cpp lda_infer.h timer.h
	g++ -c infer_test.cpp
infer.o:lda_infer.h StringUtils.h kltool.h
	g++ -c infer.cpp
kltool.o:kltool.h
	g++ -c kltool.cc
StringUtils.o:StringUtils.h
	g++ -c StringUtils.cc
clean:
	rm *.o infer