#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

int MaxSubSeqSum(const vector<int>& seq)
{
	int sum = 0;
	int len = seq.size();
	int max = INT_MIN;
	for(int i = 0;i != len;++i) {
		sum += seq[i];
		if(sum > max) 
			max = sum;
		if(sum < 0)
			sum = 0;
	}	
	return max;
}

int main()
{
	int k,num;
	vector<int> seq;
	cin >> k;
	while(k--) {
		cin >> num;
		seq.push_back(num);
	}
	cout << MaxSubSeqSum(seq);
	return 0;
}	