/*
 *  problem: https://leetcode-cn.com/problems/rotting-oranges/
 */

//Solution (BFS):
//Time complexity: O(row * col)
//Space complexity: O(row * col)


class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;   //For cells with a rotten orange
        vector<pair<int,int>> dirs{   //Four directions
            {1,0},{0,1},{-1,0},{0,-1}
        };
        int fresh = 0, min = 0;
        int row = grid.size();
        int col = grid[0].size();
        for(int i = 0;i != row;++i) {   //Push cells with a rotten orange into the queue and count fresh ones
            for(int j = 0;j != col;++j) {
                if(grid[i][j] == 1)
                    fresh++;
                if(grid[i][j] == 2)
                    q.push({i,j});
            }
        }
        while(!q.empty()) {   //Loop until not rotting new oranges
            int size = q.size();
            bool rotten = false;   //A flag to check whether we can rot at least one orange this time
            for(int i = 0;i != size;++i) {  //For each rotten orange this time
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(const auto& dir : dirs) {   //Try each direction
                    int new_x = x + dir.first;
                    int new_y = y + dir.second;
                    if(new_x >= 0 && new_x < row && new_y >= 0 && new_y < col
                            && grid[new_x][new_y] == 1) {    //If it's a fresh orange in the grid
                        fresh--;       //Decrease counter for fresh oranges
                        grid[new_x][new_y] = 2;  //Rot it
                        q.push({new_x,new_y});   //Push it into the queue
                        rotten = true;   //Set flag true as we've rotted an orange this time
                    }
                }
            }
            if(rotten)  //If successfully rotted oranges, increase minimum number of minutes 
                min++;
        }
        return fresh ? -1 : min;  //If no fresh oranges left, return -1. Otherwise, return minimum number of minutes
    }
};
