#include<iostream>     //其实可以直接将哈夫曼树设为全局变量
#include<fstream>      //但因题目要弄读写文件，便每次都需从文件复原哈夫曼树处理
#include<vector>
#include<map>
#include<deque>
#include<string>
#include<algorithm>
using namespace std;

size_t num;

struct HuffmanNode {
	HuffmanNode() :data('#'), weight(0), parent(0), left(0), right(0) {}
	HuffmanNode(char c, int w) :data(c), weight(w), parent(0), left(0), right(0) {}
	HuffmanNode(char c, int w, size_t p, size_t l, size_t r) :
		data(c), weight(w), parent(p), left(l), right(r) {}

	char data;
	int weight;
	size_t parent;
	size_t left;
	size_t right;
};


void Select(vector<HuffmanNode>& HuffmanTree, size_t pos, int& min1, int& min2)
{                                
	int min1_val = INT_MAX;
	int min2_val = INT_MAX;
	for (size_t i = 1; i <= pos; ++i) {
		if (HuffmanTree[i].weight < min1_val && HuffmanTree[i].parent == 0) {
			min2_val = min1_val;
			min1_val = HuffmanTree[i].weight;
			min2 = min1;
			min1 = i;
		}
		else if (HuffmanTree[i].weight < min2_val && HuffmanTree[i].parent == 0) {
			min2_val = HuffmanTree[i].weight;
			min2 = i;
		}
	}
}

void CreateHuffmanTree()
{
	ofstream os("hfmTree.txt");
	cout << "Please input alphabet(size, character and weight):" << endl;
	cin >> num;    //字符集中字符个数
	vector<HuffmanNode> HuffmanTree(2 * num);  
	char data;
	int weight;
	for (size_t i = 1; i <= num; ++i) {   //读入字符与对应权值，要考虑空格、换行符等
		cin.ignore();
		cin.get(data);
		cin >> weight;
		HuffmanTree[i] = HuffmanNode(data, weight);
	}

	int min1, min2;
	for (size_t i = num + 1; i != HuffmanTree.size(); ++i) {
		Select(HuffmanTree, i - 1, min1, min2); 
		HuffmanTree[i].weight = HuffmanTree[min1].weight + HuffmanTree[min2].weight;
		HuffmanTree[i].left = min1;
		HuffmanTree[i].right = min2;
		HuffmanTree[min1].parent = HuffmanTree[min2].parent = i;
	}
	for (const auto i : HuffmanTree) {
		os << i.data << " " << i.weight << " " << i.parent << " " << i.left << " " << i.right << endl;
	}
	os.close();
}

void Encode()
{
	ifstream huff("hfmTree.txt");
	if (!huff.is_open()) {
		cerr << "Fail to open file hfmTree.txt" << endl;
		return;
	}
	vector<HuffmanNode> HuffmanTree;
	char data;
	int weight;
	size_t parent, left, right;
	while (huff.get(data) && huff >> weight >> parent >> left >> right) { //复原哈夫曼树 注意空格字符的情况
		huff.ignore();
		HuffmanTree.push_back(HuffmanNode(data, weight, parent, left, right));
	}
	huff.close();
	//for (const auto i : HuffmanTree) {   //测试哈夫曼树的复原
	//	cout << i.data << " " << i.weight << " " << i.parent << " " << i.left << " " << i.right << endl;
	//}
	map<char, deque<char>> code_list;  //将各个字符的编码对应地存起来
	for (size_t i = 1; i <= num; ++i) {      //对哈夫曼树已有字符编码
		deque<char> each_code;
		int child = i;
		int parent = HuffmanTree[child].parent;
		while (parent != 0) {
			if (HuffmanTree[parent].left == child)
				each_code.push_front('0');
			else
				each_code.push_front('1');
			child = parent;
			parent = HuffmanTree[parent].parent;
		}
		code_list.insert({ HuffmanTree[i].data,each_code });
	}
	//for (const auto& i : code_list) {   //测试文本的编码
	//	cout << i.first << " ";
	//	for (const auto& j : i.second) {
	//		cout << j;
	//	}
	//	cout << endl;
	//}
	ifstream to_be_tran("to_be_tran.txt");  //要转换的文本
	if (!to_be_tran.is_open()) {
		cerr << "Fail to open file to_be_tran.txt" << endl;
		return;
	}
	ofstream code_file("code_file.txt");
	char text;
	map<char, deque<char>>::iterator p;
	while(to_be_tran.get(text)) {  //对文本编码
		if ((p = code_list.find(text)) != code_list.end()) {
			for (const auto& i : p->second)
				code_file << i;
			code_file << " ";   //每个字符的编码以空格隔开
		} else {
			cerr << "Code not match" << endl;
			return;
		}
	}
	to_be_tran.close();
	code_file.close();
	//ifstream for_test("code_file.txt");  //测试code_file的输出
	//string str;
	//while (for_test >> str)
	//	cout << str << endl;
}

void Decode()
{
	ifstream huff("hfmTree.txt");
	if (!huff.is_open()) {
		cerr << "Fail to open file hfmTree.txt" << endl;
		return;
	}
	vector<HuffmanNode> HuffmanTree;
	char data;
	int weight;
	size_t parent, left, right;
	while (huff.get(data) && huff >> weight >> parent >> left >> right) { //复原哈夫曼树 注意空格字符的情况
		huff.ignore();
		HuffmanTree.push_back(HuffmanNode(data, weight, parent, left, right));
	}
	huff.close();
	ifstream code_file("code_file.txt");
	if (!code_file.is_open()) {
		cerr << "Fail to open file code_file.txt" << endl;
		return;
	}
	ofstream text_file("text_file.txt");
	string str;
	while (code_file >> str) {
		size_t pos = 2 * num - 1;
		for (const auto& i : str) {
			if (i == '0') {
				pos = HuffmanTree[pos].left;
			} else {
				pos = HuffmanTree[pos].right;
			}
		}
		text_file << HuffmanTree[pos].data;
	}
	code_file.close();
	text_file.close();
	//ifstream for_test("text_file.txt");   //测试译码结果
	//while (getline(for_test, str))
	//	cout << str << endl;
	//for_test.close();
}

int main()
{
	CreateHuffmanTree();
	//ofstream to_be_tran("to_be_tran.txt");   //测试encode的翻译文本
	//for (char c = 'a'; c <= 'e'; ++c)
	//	to_be_tran << c;
	//to_be_tran.close();
	Encode();
	Decode();
	return 0;
}