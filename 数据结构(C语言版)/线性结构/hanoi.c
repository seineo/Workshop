#include<stdio.h>

void move(size_t n, char source, char target)
{
	printf("move %d from %c to %c\n", n, source, target);
}

void hanoi(size_t n, char source, char temp, char target)
{
	if(n == 1) {
		move(1, source, target);
	} else {
		hanoi(n - 1,source, target, temp);
		move(n, source, target);
		hanoi(n - 1,temp, source, target);
	}
}

int main()
{
	hanoi(3,'A', 'B', 'C');
	return 0;
}