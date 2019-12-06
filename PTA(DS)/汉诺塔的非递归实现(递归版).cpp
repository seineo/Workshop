#include<iostream>
using namespace std;

void hanoi(size_t n,char source,char temp,char target)
{
    if(n == 1) {
        printf("%c -> %c\n",source,target);   //如果用cout过不了，printf比cout快
    } else {
        hanoi(n - 1,source,target,temp);
        printf("%c -> %c\n",source,target);
        hanoi(n - 1,temp,source,target);
    }
}

int main()
{
    int n;
    cin >> n;
    hanoi(n,'a','b','c');
    return 0;
}
