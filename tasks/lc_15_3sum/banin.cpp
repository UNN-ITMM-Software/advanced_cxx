#include <set>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        using std::set;
        using std::vector;

        sort(nums.begin(), nums.end());
        set<vector<int>> ans;
        // Might want to squash repetitions for nums with many repeating values
        // $O(n^2)$ search * $O(\log^2 n)$ binary search and set insertion
        for(auto it = nums.begin(); it != nums.end(); ++it){
            // Not iteration with :, since you can't quite cut corners as effectively
            for(auto jt = it + 1; jt != nums.end(); ++jt){
                int a = *it, b = *jt, target = -(a + b);
                auto kt = lower_bound(jt + 1, nums.end(), target);
                if(kt != nums.end() && *kt == target){
                    ans.insert(vector<int>{a, b, *kt}); // Modern brace initializer
                }
            }
        }
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};
