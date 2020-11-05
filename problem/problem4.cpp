#include "problem4.h"
#include<vector>
#include<algorithm>
using namespace std;

double problem4::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	for (int i = 0; i < nums2.size(); i++) {
		nums1.push_back(nums2[i]);
	}
	sort(nums1.begin(), nums1.end());
	return((double)(nums1[(int)((nums1.size() - 1) / 2)] + nums1[(int)((nums1.size()) / 2)]) / 2);		
};