#include "Timer.h"

Time Time::operator+(const Time& t) {
	Time time;
	int temp;
	temp = this->second + t.second;
	time.second = temp % 60;
	if (temp >= 60)	time.minute = 1;
	temp = time.minute + this->minute + t.minute;
	time.minute = temp % 60;
	if (temp >= 60)	time.hour = 1;
	time.hour = time.hour + this->hour + t.hour;
	return time;
}
bool operator == (const Time& t1, const Time& t2) {
	return (t1.hour == t2.hour) && (t1.minute == t2.minute) && (t1.second == t2.second);
}
bool operator != (const Time& t1, const Time& t2) {
	return !(t1 == t2);
}
bool operator < (const Time& t1, const Time& t2) {
	if (t1.hour < t2.hour)	return true;
	if (t1.hour == t2.hour && t1.minute < t2.minute)	return true;
	if (t1.hour == t2.hour && t1.minute == t2.minute && t1.second < t2.second)	return true;
	return false;
}
bool operator > (const Time& t1, const Time& t2) {
	return !(t1 == t2 || t1 < t2);
}
int Time::getH(void) const{
	return hour;
}
int Time::getM(void) const{
	return minute;
}
int Time::getS(void) const{
	return second;
}
void Time::show(int theX /*= 430*/, int theY /*= 25*/) {
	cvui::text(frame, theX, theY, "Time", 0.7);
	cvui::printf(frame,theX - 20, theY + 30, 0.7, 0xff0000, "%02d:%02d:%02d", hour, minute, second);
	std::cout << hour << ":" << minute << ":" << second << std::endl;
}

void Timer::start(void) {
	start_time = clock();
}
void Timer::end(void) {
	end_time = clock();
	psd_time = psd_time + calc_time(start_time, end_time);
}
void Timer::restart(void) {
	start_time = clock();
	psd_time = 0;
}

Time Timer::getTime(void) {
	time_t now = clock();
	return calc_time(start_time, now);
}
Time Timer::getTotTime(void) {
	return psd_time;
}
Time Timer::calc_time(clock_t s, clock_t t) {
	int length = (t - s) / CLOCKS_PER_SEC;
	int hour = length / 3600;
	int minute = (length % 3600) / 60;
	int second = length % 60;
	return Time(hour, minute, second);
}
void Timer::show(void) {
	int hour = psd_time.getH(), minute = psd_time.getM(), second = psd_time.getS();
	cvui::text(frame, 190, 100, "Total Time", 0.7, 0xf8f8ff);
	cvui::printf(frame, 200, 150, 0.7, 0xf8f8ff, "%02d:%02d:%02d", hour, minute, second);
	std::cout << hour << ":" << minute << ":" << second << std::endl;
}