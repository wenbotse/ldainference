/*
 * timer.h
 *
 *  Created on: 2014年12月5日
 *      Author: xiewenbo
 */
#include<sys/time.h>
#include<unistd.h>
#ifndef TIMER_H_
#define TIMER_H_

class Timer{
    struct timeval start_;
    struct timeval end_;
    size_t timeuse_;

  public:
    Timer(): timeuse_(0) {}

    void clear()
    {
      timeuse_ = 0;
    }

    void start()
    {
      gettimeofday(&start_, NULL);
    }

    void end()
    {
      gettimeofday(&end_, NULL);
      size_t cost = 1000000 * (end_.tv_sec - start_.tv_sec)
        + end_.tv_usec - start_.tv_usec;
      timeuse_ += cost;
    }

    size_t cost()
    {
      return timeuse_;
    }

    float cost_sec()
    {
      return timeuse_ / 1000000.0;
    }
  };

#endif /* TIMER_H_ */
