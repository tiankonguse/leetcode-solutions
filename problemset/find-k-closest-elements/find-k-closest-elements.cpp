/*************************************************************************
    > File Name: find-k-closest-elements.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月27日 18:52:47
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int search(vector<int>& arr, int x) {
        int left = 0, right = arr.size(), mid;
        while(left < right) {
            mid = left + (right - left)/2;
            if(arr[mid] < x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        //find first >= x pos
        int mid = search(arr, x);
        int left, right;

        if(mid == arr.size()) {
            left = right = arr.size() - 1;
        } else if(mid == 0) {
            left = right = 0;
        } else {
            //if not eq x, left may be eq right, so left should be ans
            if(x - arr[mid-1] > arr[mid] - x) {
                left = right = mid;
            } else {
                left = right = mid - 1;
            }
            // if left is ans, left may be continuously eq, so should find min left
            while(left > 0 && arr[left] == arr[left - 1]) {
                left = right = left - 1;
            }
        }

        while(right - left + 1 < k && left >0 && right + 1 < arr.size()) {
            if(x - arr[left - 1] <= arr[right +1] - x) {
                left--;
            } else {
                right++;
            }
        }
        while(right - left + 1 < k && left >0) {
            left--;
        }
        while(right - left + 1 < k && right + 1 < arr.size()) {
            right++;
        }

        vector<int>ans;
        for(int i=left; i<=right; i++) {
            ans.push_back(arr[i]);
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4}); //array ro List
    // vecToTree({});  //array to Tree
    // std::reverse(a.begin(),a.end());  //反转
*/
int main() {
#define CLASS Solution
#define FUNCTION findClosestElements

    vector<int> first;
    int second;
    int third;
    vector<int> expectAns;

    first = {1,2,3,4,5};
    second = 4;
    third = 3;
    expectAns = {1,2,3,4};
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);

    first = {1,2,3,4,5};
    second = 4;
    third = -1;
    expectAns = {1,2,3,4};
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);

    return 0;
}
