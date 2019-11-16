#include<iostream>
#include<string>
#include<vector>

std::vector<int> next;

void GetNext(const std::string& str, std::vector<int>& next)
{
	int k = -1;
	int j = 0;
	int len = str.size();
	next.resize(len);
	next[0] = -1;
	while (j != len - 1) {  //因为next[0]已设置，只需求剩下字符的next数组值
		if (k == -1 || str[j] == str[k]) {
			j++;
			k++;
			if (str[j] != str[k])
				next[j] = k;
			else
				next[j] = next[k];
		}
		else {
			k = next[k];
		}
	}
}

int StringMatching(const std::string& source, const std::string& target)
{
	int i = 0, j = 0;
	int s_len = source.size(), t_len = target.size();
	while (i != s_len && j != t_len) {
		if (j == -1 || source[i] == target[j]) {  //当j==-1时，相当于source下移一个位置与target[0]比较
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == t_len)
		return i - j;
	else
		return -1;
}

int main()
{
	std::string source, target;
	std::cin >> source >> target;
	GetNext(target, next);
	std::cout << StringMatching(source, target) << std::endl;
	return 0;
}