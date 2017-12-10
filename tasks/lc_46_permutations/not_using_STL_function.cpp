typedef pair<int, int> perm_element;


class Solution {
private:

void addPerm(vector<perm_element>& perm, vector<vector<int> > & permutes)
{
    const int n = perm.size();
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        p[i] = perm[i].second;

    permutes.push_back(p);
}
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        int n = nums.size();
        vector<vector<int> > permutes;

        // initial permutation
        vector<perm_element> perm(n);
        for (int i = 0; i < n; i++)
            perm[i] = perm_element(i, nums[i]);
    
        addPerm(perm, permutes);

        while (true)
        {
            //  finding i: (perm[i] < perm[i + 1]) AND (perm[k]>=perm[k+1], k=(i+1,...,n-2))
            int i = n-2;
            for (; i >= 0; i--)
            {
                if (perm[i].first < perm[i+1].first) break;
            }
            if (i == -1) break; // all permutes are generated; perm[0]=n-1, perm[1]=n-2, ..., perm[n-1]=0
        
            // k = max{k: n-1 >= k >= i+1; perm[k] >= perm[i]}
            int k = i + 1;
            for (; k <= n-1; k++)
            {
                if (perm[k].first < perm[i].first) break;
            }
            k--;

            swap(perm[k], perm[i]);

            // swap the order of numbers - get the minimum number out of "digits" {perm[i+1], perm[i+2],..., perm[n-1]}
            for (int k = 0; k < ((n-1)-(i+1)+1) / 2; k++)
                swap(perm[i+1 + k], perm[n-1 - k]);

            addPerm(perm, permutes);
        }
        return permutes;
    }
};