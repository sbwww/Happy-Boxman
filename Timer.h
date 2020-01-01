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
	Time getTime(void); // �����ʱ���ӿ�ʼ�����ھ�����ʱ�䣬��Time���ͷ��� 
	Time getTotTime(void); // �����ʱ���ܹ�������ʱ�䣬��Time���ͷ���
	void show(void);
private:
	clock_t start_time;
	clock_t end_time;
	Time psd_time; // ֮ǰ�Ѿ�������ʱ�� 
	Time calc_time(clock_t s, clock_t t); // ��������clock_t���͵�ʱ���� 
};
