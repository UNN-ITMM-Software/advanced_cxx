class Solution {
public:
    void filterNums(std::vector<int> &nums, std::vector<int> &count) {
        std::vector<int> new_nums;
        new_nums.reserve(nums.size());
        count.reserve(nums.size());
        int prev = INT_MIN;
        for (auto &num: nums) {
            if (num != prev) {
                new_nums.push_back(num);
                count.push_back(0);
            }
            ++count.back();
            prev = num;
        }
        
        nums = std::move(new_nums);
    }



std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> three_sum;
    if (nums.size() < 3) {
        return three_sum;
    }
    
    std::vector<int> count;
    filterNums(nums, count);

    size_t nums_count = nums.size();
    three_sum.reserve(nums_count * nums_count);
    size_t idx[] = {0, 0, nums_count - 1};
    if (count[idx[0]] == 1) {
        ++idx[1];
    }
    std::vector<size_t> max_corresp_candidat_idx(nums_count, nums_count - 1);

    int a = nums[idx[0]], b = nums[idx[1]], c = nums[idx[2]];
    std::vector<int> triple = {a, b, c};
    while (triple[0] < 0) {
        while (triple[0] <= - 2 * triple[1]) {  
            while ((triple[1] > - triple[0] - triple[2]) && (idx[1] <= idx[2])) {
                --idx[2];
                triple[2] = nums[idx[2]];
            }
            if (((triple[0] + triple[2]) + triple[1] == 0) && ((idx[1] < idx[2]) || (count[idx[1]] > 1))) {
                three_sum.push_back(triple);
                --idx[2];
            }
            if (idx[1] <= idx[2]) {
                max_corresp_candidat_idx[idx[1]] = idx[2];
            } 
                           
            ++idx[1];
            if (idx[1] > idx[2])
                break;
            triple[1] = nums[idx[1]];
            idx[2] = std::min(max_corresp_candidat_idx[idx[1]], max_corresp_candidat_idx[idx[1] - 1]);
            triple[2] = nums[idx[2]];
        }        
       
        ++idx[0];
        idx[1] = count[idx[0]] > 1 ? idx[0] : idx[0] + 1;
        if (idx[1] >= nums_count)
            break;
        
        idx[2] = std::min(max_corresp_candidat_idx[idx[1]], max_corresp_candidat_idx[idx[1] - 1]);
        triple[0] = nums[idx[0]];
        triple[1] = nums[idx[1]];
        triple[2] = nums[idx[2]];
    }
    if ((nums[idx[0]] == 0) && (count[idx[0]] >=3)) {
        three_sum.push_back({0, 0, 0});
    }

    return three_sum;
}
};
