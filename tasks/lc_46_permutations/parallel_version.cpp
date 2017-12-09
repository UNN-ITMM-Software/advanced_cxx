#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <thread>
#include <unistd.h>
#include <mutex>

using namespace std;
int factorial(int k)
{
	int numPermute = 1;
	for(int i = 1; i <= k; i++)
	{   
		numPermute *= i;
//		std::cout << this_thread::get_id() << ": " << numPermute << std::endl;
	}
	return numPermute;
}
void swap(std::vector<int>& nums, int i, int j)
{
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp; 
}

void whilePermute(std::vector<int> nums, int k,mutex& mtx,std::vector<std::vector<int>>& result)
{
	while(k--)
	{
		//mtx.lock();
		result.push_back(nums);
		//mtx.unlock();

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
					    i = 0;
					    break;
				    }
			    }
		    }
	    }
	}

}

std::vector<int> getNPernutation(std::vector<int> nums, int position, int n)
{
    int k = position;
	int nPost = n;  // how many ellements after i-ellement
    for(int i = 0; i < n; i++)
    {
	    std::sort(nums.begin()+i,nums.end());
	    for(int j=1;j<nPost+1;j++)
	    {
		    if(k <= j*factorial(nPost-1))
		    {
			    swap(nums,i,i+j-1);
			    if(k >= (j-1)*factorial(nPost-1))
			      k = k - (j-1)*factorial(nPost-1);
		        nPost -= 1;   
			    break;
		    }
	    }
    }
    return nums;
}

int main()
{
	int myNums[]={1,2,3,4,5,6,7};
	std::vector<int> nums(myNums,myNums+7);
	int n= 7;
	int numAllPerm = factorial(n);
	std::vector<int> secondHalfNums = getNPernutation(nums,numAllPerm/2+1,n);

	std::vector<std::vector<int>> result1;
	std::vector<std::vector<int>> result2;
	mutex mtx;
	auto start = std::chrono::steady_clock::now();

	thread t1(whilePermute, nums, numAllPerm/2, ref(mtx), ref(result1));

	thread t2(whilePermute, secondHalfNums, numAllPerm-numAllPerm/2, ref(mtx), ref(result2));

	t1.join();
	t2.join();	


	cout <<endl << result1.size() << endl;

	for(int i=0;i<result1.size();i++)
	{
		for(int j=0;j<n;j++)
			cout << result1[i][j];
		cout << endl;
	}

	cout <<endl << result2.size() << endl;


	for(int i=0;i<result2.size();i++)
	{
		for(int j=0;j<n;j++)
			cout << result2[i][j];
		cout << endl;
	}

	return 0;
}
