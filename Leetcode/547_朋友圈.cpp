class Solution {
public:
    void DFS(vector<vector<int>>& M,vector<int>& visited, int i) {
        visited[i] = 1;
        for(int j = 0;j != M.size();++j) {
            if(M[i][j] && !visited[j]) 
                DFS(M,visited,j);
        }
    }
    int findCircleNum(vector<vector<int>>& M) {
        vector<int> visited(M.size(),0);
        int count = 0;
        for(int i = 0;i != M.size();++i) {
            if(!visited[i]) {
                count++;
                DFS(M,visited,i);
            }
        }
        return count;
    }
};