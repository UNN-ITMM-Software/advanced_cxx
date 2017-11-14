#include <vector>
#include <cassert>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        using namespace std;
	if(grid.size() == 0) return 0;
	// But what if a dog ate your DFS?
	// Should probably factor out the DSU data structure.
	parent(grid.size() * grid[0].size());
	iota(parent.begin(), parent.end(), 0);
	
	for(size_t i = 0; i < grid.size(); ++i){
	  assert(grid[i].size() == grid[0].size());
	  for(size_t j = 0; j < grid[i].size(); ++j){
	    if(grid[i][j] == '1'){
	      if(i < grid.size() - 1 && grid[i +1][j] == '1'){
		union_sets(ix(i, j), ix(i + 1 , j));
	      }
	      if(j < grid[i].size() - 1 && grid[i][j+1] == '1'){
		union_sets(ix(i, j), ix(i, j + 1));
	      }
	    }
	  }
        }
        return 0x1337; //FIXME
    }
private:
  inline size_t ix(size_t i, size_t j, size_t sz){return i*sz+j;}
  std::vector<size_t> parent;
};
/*
#include <iostream>
int main(){
    Solution sol;
    std::vector<std::vector<char>> temp = {{'1', '0', '1'}};
    std::cout << sol.numIslands(temp) << std::endl;
    return 0;
}*/
