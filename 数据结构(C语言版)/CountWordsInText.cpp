#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<fstream>
#include<algorithm>
using namespace std;

struct Word {
	Word(string str) :word(str), count(0) {}

	string word;
	size_t count;
	vector<size_t> line;
};

int main()
{
	vector<Word> word_info;
	string str;
	while (cin >> str) {
		word_info.push_back(Word(str));
	}
	ifstream is("CountWords.cpp");
	if (!is.is_open()) {
		cerr << "Fail to open file";
		exit(1);
	}
	else {
		size_t num = 1;
		while (getline(is, str)) {
			for (auto& i : word_info) { 
				if (str.find(i.word) != string::npos) {
					i.count++;
					i.line.push_back(num);
				}
			}
			num++;
		}
		for (const auto& i : word_info) {
			cout << i.word << " appears " << i.count << " times. Line: ";
			copy(i.line.begin(), i.line.end(), ostream_iterator<size_t>(cout, " "));
			cout << endl;
		}
		is.close();
	}
	system("pause");
}