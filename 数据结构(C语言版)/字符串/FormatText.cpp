#include<iostream>
#include<string>
#include<fstream>
using namespace std;

size_t page_length, page_width, left_margin, head_length, foot_length, start_page_num;
size_t num = 0, line = 1;  //num为字符数  line为文字的行数

inline void StartFormat(ofstream& os)  //新页开头的头长+1 到直接输入的那一行
{
	for (size_t i = 0; i != head_length; ++i) {
		os << endl;
	}
}

inline void PrintLeftMargin(ofstream& os)  //打印左空白
{
	for (size_t i = 0; i != left_margin; ++i) {
		os << " ";
		num++;
	}
}

inline void ChangePage(ofstream& os)
{
	if (foot_length >= 3) {
		os << endl;
		size_t width = page_width / 2;
		for (size_t i = 0; i != width; ++i)  //第二空行输出
			os << " ";
		os << start_page_num++ << endl;
		for (size_t i = 0; i != foot_length - 2; ++i)
			os << endl;
	}
	else {
		for (size_t i = 0; i != foot_length; ++i)
			os << endl;
	}
	line = 1;   //换页后行数更新
	StartFormat(os);
}

int main()
{
	ifstream is("input.txt");
	ofstream os("output.txt");
	if (!is.is_open() || !os.is_open()) {
		cerr << "Fail to open file" << endl;
		exit(1);
	}
	cin >> page_length >> page_width >> left_margin >> head_length >> foot_length >> start_page_num;
	string word;
	StartFormat(os);
	PrintLeftMargin(os);
	while (is >> word) {
		if (word == "@") {
			if (line + 2 <= page_length) {
				os << endl;
				os << endl;
				for (size_t i = 0; i != 8; ++i)
					os << " ";
				line += 2;
				num = 8;
			} 
			else if (line + 1 == page_length) {
				os << endl;
				ChangePage(os);
				for (size_t i = 0; i != 8; ++i)
					os << " ";
				num = 8;
			}
			else {
				ChangePage(os);
				os << endl;
				line += 1;
				for (size_t i = 0; i != 8; ++i)
					os << " ";
				num = 8;
			}
			continue;
		}
		if (num + word.size() > page_width) {
			os << endl;
			line++;
			for (size_t i = 0; i != left_margin; ++i) 
				os << " ";
			num = left_margin;
		}
		if (line > page_length) {
			ChangePage(os);
			PrintLeftMargin(os);
		}
		os << word << " ";
		num += word.size() + 1;
	} 
}