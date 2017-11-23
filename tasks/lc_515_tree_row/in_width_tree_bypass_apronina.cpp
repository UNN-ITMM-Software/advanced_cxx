// in_width_tree_bypass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	std::vector<int> largestValues(TreeNode* root) {
		if (root == nullptr)
		{
			return {};
		}

		std::vector<int> result;

		std::queue<TreeNode*> bypass;
		bypass.push(root);

		TreeNode *current = root;
		int originLevelLimit = 1;
		int levelLimit = 1;
		int nextLevelLimit = originLevelLimit << 1;
		int count = 0;
		int maxValue = INT_MIN;

		do
		{
			current = bypass.front();
			maxValue = current->val > maxValue ? current->val : maxValue;

			bypass.pop();
			++count;

			if (current->left != nullptr)
			{
				bypass.push(current->left);
			}
			else
			{
				--nextLevelLimit;
			}

			if (current->right != nullptr)
			{
				bypass.push(current->right);
			}
			else
			{
				--nextLevelLimit;
			}

			if (count == levelLimit)
			{
				count = 0;
				levelLimit = nextLevelLimit;
				nextLevelLimit = nextLevelLimit << 1;
				result.push_back(maxValue);
				maxValue = INT_MIN;
			}

		} while (!bypass.empty());

		return result;
	}
};

int main()
{

	TreeNode *root = new TreeNode(10);
	TreeNode *left = new TreeNode(3);
	TreeNode *leftLeft = new TreeNode(5);
	
	root->left = left;
	left->left = leftLeft;
	auto result = Solution().largestValues(root);

    return 0;
}

