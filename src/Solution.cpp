#include "Solution.h"
#include <unordered_map>
#include <unordered_set>

int Solution::mySolution_vectorInt(vector<int> &nums) {
    unordered_map<int, int> um;
    int res = 0;
    for (auto &num : nums) {
        if (!um.count(num)) {
            int left = um.count(num - 1) ? um[num - 1] : 0;
            int right = um.count(num + 1) ? um[num + 1] : 0;
            int count = right + left + 1;
            um[num - left] = count;
            um[num + right] = count;
            res = res > count ? res : count;
        }
    }
    return res;
}

int Solution::stdSolution_vectorInt(vector<int> &nums) {
    unordered_set<int> us;
    for (const auto &num : nums) {
        us.insert(num);
    }
    int res = 0;

    for (const auto &num : us) {
        if (!us.count(num - 1)) {
            int len = 0;
            int currentNum = num;
            while (us.count(currentNum)) {
                ++len;
                ++currentNum;
            }
            res = max(res, len);
        }
    }

    return res;
}

void Solution::mySolution(ListNode* head){
    auto p = new ListNode(99);
    auto next = head->next;
    head->next=p;
    p->next = next;
}

void Solution::stdSolution(ListNode* head){
    auto p = new ListNode(101);
    auto next = head->next;
    head->next=p;
    p->next = next;
}