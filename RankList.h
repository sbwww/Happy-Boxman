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
#include <sstream>
#include <iterator>
#include <regex>
#include "Timer.h"
#include "cvui.h"

class Rec {
public:
	Rec(std::string nm = "", int score = 0, Time tm = Time(0)) :name(nm), score(score), use_time(tm) {}
	Rec(std::string nm = "", int score = 0, int h = 0, int m = 0, int s = 0) :name(nm), score(score), use_time(h, m, s) {}
	friend std::ostream& operator <<(std::ostream& out, const Rec& rec);
	bool operator < (const Rec& r) const;
	bool operator == (const Rec& r) const;
	bool operator > (const Rec& r) const;
	int score;
	std::string name;
	Time use_time;
	
};

class RankList {
public:
	RankList();
	void Save(const Rec& r); //将时间写入到一个空的文件里 
	void Show();//读取文档中的内容并显示出来 
private:
	const std::string file_name = ".\\Data\\ranklist.dat";
};