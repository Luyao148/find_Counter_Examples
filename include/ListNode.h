constexpr int NODE_DEFAULT_VAL = 0;

struct ListNode{
    int val;
    ListNode* next;

    ListNode():val(NODE_DEFAULT_VAL),next(nullptr){}
    ListNode(int _val,ListNode* _next=nullptr):val(_val),next(_next){}
    ListNode(const ListNode&) = delete;
};