class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> result{nums};
        while (nextPermutation(nums)) result.push_back(nums);
        return result;
    }
private:
    bool nextPermutation(vector<int>& nums) {
        if (nums.size() < 2)
        {
            return false;
        }
        auto it(nums.rbegin() + 1);
        while (it != nums.rend() && (*it >= *(it - 1)))
        {
            ++it;
        }
        auto found(it != nums.rend());
        if (found)
        {
            auto foundIt = upper_bound(nums.rbegin(), it - 1, *it);
            std::swap(*foundIt, *it);
        }
        
        std::reverse(nums.rbegin(), it);
        return found;
    }
};
