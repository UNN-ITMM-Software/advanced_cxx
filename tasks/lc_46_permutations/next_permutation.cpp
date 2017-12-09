class Solution {
public:
    void swap(std::vector<int>& nums, int i, int j)
    {
	    int tmp = nums[i];
	    nums[i] = nums[j];
	    nums[j] = tmp; 
    }
    
    //next lexicographically permutation
    bool nextPermutation(std::vector<int>& nums)
    {
	    int indexShouldChenge = 0;
	    for(int i=nums.size(); i > 0; i--)
	    {
		    if(nums[i-1] < nums[i])
		    {
			    indexShouldChenge = i-1;
			    std::sort(nums.begin()+i,nums.end());
			    for(int j = i; j < nums.size(); j++)
			    {
				    if(nums[indexShouldChenge] < nums[j])
				    {
					    swap(nums,indexShouldChenge,j);
					    return true;
				    }
			    }
		    }
	    }
	    return false;
    }
    std::vector<vector<int>> permute(vector<int>& nums) {
       	std::vector< vector<int> > result;
        std::sort(nums.begin(),nums.end());
        
        do
		{
		    result.push_back(nums);
		}while(nextPermutation(nums)); 
        return result;
    }

};
