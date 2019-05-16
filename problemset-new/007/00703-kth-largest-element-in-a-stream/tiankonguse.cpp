/*************************************************************************
    > File Name: kth-largest-element-in-a-stream.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri May 17 01:19:55 2019
    > link: https://leetcode.com/problems/kth-largest-element-in-a-stream/
    > No: 703. Kth Largest Element in a Stream
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class KthLargest {
    multiset<int> s;
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(int i=0;i<nums.size();i++){
            this->add(nums[i]);
        }
    }

    int add(int val) {
        s.insert(val);
        while(s.size() > k){
            s.erase(s.begin());
        }
        return *s.begin();
    }
};
