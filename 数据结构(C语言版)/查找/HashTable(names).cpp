#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<ctime>
#include<random>
#include<algorithm>
#include<stdexcept>
using namespace std;

enum KindofEntry {
	Legal,
	Empty
};

using HashTable = struct HashEntry*;
using Position = size_t;
using State = enum KindofEntry;

size_t random_sequence[60];

struct Entry {
	string data;
	State state;	
};

size_t RandomInt(size_t lower,size_t upper)
{
	static default_random_engine e(time(NULL));
	static uniform_int_distribution<size_t> u(lower,upper);
	return u(e);
}

void CreateRandomSeq()
{
	for(size_t i = 0;i != 60;++i) {
		random_sequence[i] = i + 1;
	}
	for(size_t i = 0;i != 60;++i) {
		swap(random_sequence[i],random_sequence[RandomInt(0,59)]);
	}
}

bool isPrime(size_t n)
{
	if(n < 2) {
		return false;
	}
	for(size_t i = 2;i <= static_cast<size_t>(sqrt(n));++i) {
		if(n % i == 0) {
			return false;
		}
	}
	return true;
}

size_t NextPrime(size_t n)
{
	for(size_t i = n;;++i){
		if(isPrime(i)) {
			return i;
		}
	}
}

struct HashEntry {
	HashEntry(size_t n):table_size(NextPrime(n)){
		the_array = new Entry[table_size];
		for(size_t i = 0;i != table_size;++i){
			the_array[i].state = Empty;
		}
	}
	~HashEntry() {
		delete[] the_array;
	}
	
	size_t table_size;
	Entry* the_array;	
};
size_t HashFunc(HashTable ht, const string& target)
{
	size_t result = 0;
	for(const auto& ch : target) {
		result = (result << 5) + ch;
	}	
	return result % ht->table_size;
}

Position Find(HashTable ht,const string& target)
{
	Position loc = HashFunc(ht,target);
	Position i = 0,result = loc;
	while(ht->the_array[result].state != Empty && ht->the_array[result].data != target) {
		result = (loc + random_sequence[i++]) % ht->table_size;
	}
	return result;
}

void Insert(HashTable ht,const string& target)
{
	Position loc = Find(ht,target);
	if(ht->the_array[loc].state == Empty) {
		ht->the_array[loc].state = Legal;
		ht->the_array[loc].data = target;	
	} 
}

int main()
{	HashTable ht = new HashEntry(60);
	string names;
	CreateRandomSeq();
	ifstream is("C:\\Users\\Administrator\\Desktop\\names.txt");
	if(!is.is_open()) {
		cerr << "Fail to open file" << endl;
		return -1;
	}	
	while(getline(is,names)) {
		Insert(ht,names);
	}
	while(getline(cin,names)) {
		Position loc = Find(ht,names);
		if(ht->the_array[loc].state == Legal) {
			cout << "Found : " << names << endl;
		} else {
			cout << "Fail to find : " << names << endl;
		}
	}
	delete ht;
	return 0;	
}