#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<vector<int>> threeSum(vector<int>& nums) {
    if (nums.size() < 3) return std::vector<vector<int> >(); 
    std::vector<vector<int> > output;
    std::sort(nums.begin(), nums.end());//, std::greater<int>());
    do {
        if (nums[nums.size()-1] + nums[nums.size()-2] + nums[nums.size()-3] == 0){
            vector<int> v = {nums[nums.size()-1], nums[nums.size()-2], nums[nums.size()-3]};
            std::sort(v.begin(),v.end());
            output.push_back(v);
        }
    }while ( std::next_permutation(nums.begin(),nums.end()) );
    std::sort(output.begin(), output.end());
    output.erase(std::unique(output.begin(), output.end()), output.end());
    return output;  
};

int main(){
    vector<int> input = {-1,0,1,2,-1,-4};
    std::vector<std::vector<int> > res = threeSum(input);
    for (int i =0; i < res.size(); i++){
        std::cout << res[i][0] << " " << res[i][1] << " " << res[i][2] << "\n";
    }
    return 0;
}
