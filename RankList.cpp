#include "RankList.h"
namespace utility {
	std::vector<std::string> split(const std::string& in, const std::string& delimiters = " ") {
		std::regex re{ delimiters };
		return std::vector<std::string> {
			std::sregex_token_iterator(in.begin(), in.end(), re, -1),
				std::sregex_token_iterator()
		};
	}
}

std::ostream& operator <<(std::ostream& out, const Rec& rec) {
	out << rec.name << "," << rec.score << "," << rec.use_time.getH() << "," << rec.use_time.getM() << "," << rec.use_time.getS() << std::endl;
	return out;
}
bool Rec::operator < (const Rec& r)const {
	if (this->score > r.score) return true;
	if (this->score == r.score) {
		if (this->use_time < r.use_time)	return true;
		if (this->use_time == r.use_time) {
			if (this->name < r.name)	return true;
		}
	}
	return false;
}
bool Rec::operator == (const Rec& r) const {
	return this->score == r.score && this->use_time == r.use_time && this->name == r.name;
}
bool Rec::operator > (const Rec& r)const {
	return !(*this == r || *this < r);
}

namespace utility {
	class _cmp {
	public:
		bool operator()(const Rec& r1, const Rec& r2) {
			return r1 > r2;
		}
	};
};

RankList::RankList() {
	std::ofstream out;
	out.open(file_name.c_str(), std::ios::out | std::ios::app);
	out.close();
	std::cout << "A new file has been created!" << std::endl;
}

void RankList::Save(const Rec& r) {
	bool save_flag = 0;
	std::priority_queue <Rec, std::vector<Rec>, utility::_cmp> q;
	std::ifstream in;
	in.open(file_name.c_str(), std::ios::in);
	std::string ss;
	while (std::getline(in, ss)) {//一行一行读取
		std::vector<std::string> dat = utility::split(ss, ",");
		Rec rec(dat[0], std::stoi(dat[1]), std::stoi(dat[2]), std::stoi(dat[3]), std::stoi(dat[4]));
		for (auto i : dat) {
			std::cout << i << std::endl;
		}
		if (rec.name == r.name) {
			if (rec > r)	q.push(r);
			else q.push(rec);
			save_flag = 1;
		}
		else q.push(rec);
	}
	if (!save_flag)	q.push(r);
	in.close();
	
	// 最多存8条数据
	int count = 0;
	std::ofstream out;
	out.open(file_name.c_str(), std::ios::out);
	while (!q.empty() && count < 8) {
		count++;
		Rec rec = q.top(); q.pop();
		out << rec;
	}
	out.close();
	return;
}

void RankList::Show() {
	std::string ss;
	std::ifstream in;
	in.open(this->file_name.c_str(), std::ios::in);
	int top = 50, spacing = 30, n = 1;
	int left = 87;
	int rank = 1;
	cvui::printf(
		frame, 10, 10, 0.8, 0xff0000,
		"    -----R A N K L I S T-----"
	);
	cvui::printf(
		frame, 10, top, 0.5, 0xf8f8ff,
		"     %10s     %10s    %10s",
		"Player", "Game Clearances", "Total Play Time"
	);

	while (std::getline(in, ss)) {//一行一行读取
		std::vector<std::string> dat = utility::split(ss, ",");
		switch (rank) {
		case 1: {
			cvui::printf(
				frame, left, top + n * spacing, 0.5, 0xff0000,
				dat[0].c_str()
			);
			break;
		}
		case 2: {
			cvui::printf(
				frame, left, top + n * spacing, 0.5, 0x6a5acd,
				dat[0].c_str()
			);
			break;
		}
		case 3: {
			cvui::printf(
				frame, left, top + n * spacing, 0.5, 0x00bfff,
				dat[0].c_str()
			);
			break;
		}
		default: {
			cvui::printf(
				frame, left, top + n * spacing, 0.5, 0xf8f8ff,
				dat[0].c_str()
			);
			break;
		}
		}

		cvui::printf(
			frame, left + 150, top + n * spacing, 0.5, 0xf8f8ff,
			"%d",
			std::stoi(dat[1])
		);
		cvui::printf(
			frame, left + 275, top + n * spacing, 0.5, 0xf8f8ff,
			"%02d:%02d:%02d",
			std::stoi(dat[2]), std::stoi(dat[3]), std::stoi(dat[4])
		);
		rank++;
		n++;
		for (auto i : dat) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
		std::cout << "n = " << n << std::endl;
	}
	in.close();
	return;
}