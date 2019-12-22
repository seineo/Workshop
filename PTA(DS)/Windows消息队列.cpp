#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

struct Node {
	Node(char* m,int p):prio(p){
		strcpy(message,m);
	}
	// friend bool operator<(const Node& n1,const Node& n2) {   //另一种比较方法
	// 	return n1.prio > n2.prio;
	// }

	char message[15];
	int prio;
};

struct Cmp {
	bool operator()(const Node& n1,const Node& n2) {
		return n1.prio > n2.prio;
	}
};

int main()
{
	priority_queue<Node,vector<Node>,Cmp> p;   //对于优先队列，如果要用比较类给出第三个参数
	int n,prio;                            //那么第二个参数（即用于实现优先队列的容器）也一定要给出
	char op[5];     //当数据量很大的时候，要用C语言的输入输出才能通过，所以此处用C字符串
	char message[15];
	scanf("%d",&n);
	while(n--) {
		scanf("%s",op);
		if(strcmp(op,"PUT") == 0) {
			scanf("%s",message);
			scanf("%d",&prio);
			p.push(Node(message,prio));
		} else {
			if(p.empty()) {
				printf("EMPTY QUEUE!\n");
			} else {
				printf("%s\n",p.top().message);
				p.pop();
			}
		}
	}
	return 0;
}