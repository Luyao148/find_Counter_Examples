#include "ListNode.h"
#include <memory>

List::List(const std::vector<int>& v):dummy(),oriVec(v){
    auto ptr=&dummy;
    for(const auto&e:v){
        auto p = std::make_unique<ListNode>(e);
        ptr->next=p.get();
        nodes.emplace_back(std::move(p));
        ptr=ptr->next;
    }
}

ListNode *List::getHead() {
    return dummy.next;
}

List::~List(){
    auto p = getHead();
    auto pFast(p);
    auto pSlow(p);
    while(pFast){
        pFast=pFast->next;
        if(pFast==nullptr) break;
        pFast=pFast->next;
        pSlow=pSlow->next; 
        if(pFast==pSlow) break;
    }
    if(pFast){
        // has circle
        while(p!=pSlow){
            p=p->next;
            pSlow=pSlow->next;
        }
        while(pSlow->next!=p){
            pSlow=pSlow->next;
        }
        pSlow->next=nullptr;
    }
    p=dummy.next;
    while(p){
        bool flag = true;
        for(const auto& node:nodes){
            if(node.get()==p){
                flag = false;
                break;
            }
        }
        if(flag){
            auto t(p->next);
            delete p;
            p=t;
        }else{
            p=p->next;
        }
    }
}