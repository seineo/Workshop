#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct Position {
	Position(size_t xi, size_t yi, size_t dir) :x(xi), y(yi), direction(dir) {}
	bool operator==(const Position& pos) { return x == pos.x && y == pos.y; }  //只比较坐标而不比较方向
	bool operator!=(const Position& pos) { return x != pos.x || y != pos.y; }

	size_t x;
	size_t y;
	size_t direction;  //初始为0  1到4是从右开始的顺时针
};

vector<vector<size_t>> maze;

void InitMaze(size_t m, size_t n)
{
	size_t num;
	maze.resize(m);
	for (size_t i = 0; i != m; ++i) {   //初始化地图
		for (size_t j = 0; j != n; ++j) {
			cin >> num;
			maze[i].push_back(num);
		}
	}
}

bool FindPath(Position start, Position end)
{
	stack<Position> path;
	size_t x, y, dir;
	bool find = false;
	path.push(start);  //先将入口位置设为当前位置
	maze[start.x][start.y] = 1; //已经走过不能再走
	while (!path.empty()) {
		if (path.top() == end) {   //如果当前位置就是出口则输出并返回成功
			while (!path.empty()) {
				cout << "(" << path.top().x << "," << path.top().y << "," << path.top().direction << ") ";
				path.pop();
			}
			return true;
		} else {  //不是则继续探索
			find = false;
			dir = path.top().direction;
			while (dir <= 4 && find == false) {
				dir++;
				switch (dir) {
				case 1:
					x = path.top().x + 1;
					y = path.top().y;
					break;
				case 2:
					x = path.top().x;
					y = path.top().y + 1;
					break;
				case 3:
					x = path.top().x - 1;
					y = path.top().y;
					break;
				case 4:
					x = path.top().x;
					y = path.top().y - 1;
					break;
				}
				if (maze[x][y] == 0)
					find = true;
			}
			if (find) {
				path.top().direction = dir;
				path.push(Position(x, y, 0));
				maze[x][y] = 1;  //已经走过，不能再走
			} else {
				maze[path.top().x][path.top().y] = 0; //回退 让这个点可走
				path.pop();
			}
		}
	}
	return false;
}

int main()
{
	size_t m, n, start_x, start_y, end_x, end_y;
	cout << "Input size of maze(row,col):" << endl;
	cin >> m >> n;
	cout << "Input maze in detail:" << endl;
	InitMaze(m, n);
	cout << "Input entrance and exit position:" << endl;
	cin >> start_x >> start_y >> end_x >> end_y;
	if(!FindPath(Position(start_x,start_y,0),Position(end_x,end_y,0)))
		cout << "No path" << endl;
	system("pause");
}