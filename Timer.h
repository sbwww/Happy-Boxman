#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include "cvui.h"

extern cv::Mat frame;

class Time {
public:
	Time(int h = 0, int m = 0, int s = 0) :hour(h), minute(m), second(s) {}
	~Time() {}
	Time operator +(const Time& t);
	friend bool operator == (const Time& t1, const Time& t2);
	friend bool operator != (const Time& t1, const Time& t2);
	friend bool operator < (const Time& t1, const Time& t2);
	friend bool operator > (const Time& t1, const Time& t2);
	void show(int theX = 430, int theY = 75);
	int getH(void) const;
	int getM(void) const;
	int getS(void) const;
private:
	int hour;
	int minute;
	int second;
};

class Timer {
public:
	Timer() :start_time(0), end_time(0) {}
	void start(void);
	void end(void);
	void restart(void);
	Time getTime(void); // 计算计时器从开始到现在经过的时间，以Time类型返回 
	Time getTotTime(void); // 计算计时器总共经过的时间，以Time类型返回
	void show(void);
private:
	clock_t start_time;
	clock_t end_time;
	Time psd_time; // 之前已经经过的时间 
	Time calc_time(clock_t s, clock_t t); // 计算两个clock_t类型的时间间隔 
};
