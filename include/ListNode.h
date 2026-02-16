#pragma once
#include <vector>
#include <memory>

constexpr int NODE_DEFAULT_VAL = 0;

struct ListNode{
    int val;
    ListNode* next;

    ListNode():val(NODE_DEFAULT_VAL),next(nullptr){}
    ListNode(int _val,ListNode* _next=nullptr):val(_val),next(_next){}
    ListNode(const ListNode&) = delete;
    ListNode(ListNode&&) = default;
};

class List {
  public:
    List(const std::vector<int>& v);
    List(const List& rhs):List(rhs.oriVec){}
    List(List&& rhs) noexcept = default;
    ~List() noexcept;

    ListNode *getHead();
  private:
    ListNode dummy;
    std::vector<std::unique_ptr<ListNode>> nodes;
    std::vector<int> oriVec;
};