#include "ListNode.h"
#include <memory>
#include <unordered_set>

List::List(const std::vector<int>& v):dummy(),oriVec(v){
    auto ptr=&dummy;
    for(const auto&e:v){
        auto p = std::make_unique<ListNode>(e);
        ptr->next=p.get();
        nodes.insert(std::move(p));
        ptr=ptr->next;
    }
}

ListNode *List::getHead() {
    return dummy.next;
}

List::~List(){
    std::unordered_set<ListNode*> nodesNow;
    auto ptr = getHead();
    while(ptr){
        nodesNow.insert(ptr);
        ptr=ptr->next;
    }
    for(const auto& i:nodes){
        nodesNow.erase(i.get());
    }
    for(auto i:nodesNow){
        nodes.insert(std::unique_ptr<ListNode>(i));
    }
}