#include "GeneUtils.h"
#include <cassert>
#include <cstddef>
#include <random>
#include <unordered_set>
#include <vector>

using uniIntDis = std::uniform_int_distribution<int>;

void GeneUtils::setRange(int begin,int end){
    details::rangement={begin,end};
}

int GeneUtils::randomInt(){
    auto& eg = details::getEngine();
    uniIntDis int_dis(details::rangement.first,details::rangement.second);
    return int_dis(eg);
}

std::vector<int> GeneUtils::randomVectorInt(size_t size){
    auto& eg = details::getEngine();
    uniIntDis int_dis(details::rangement.first,details::rangement.second);
    std::vector<int> ret(size);
    for(auto &i:ret){
        i=int_dis(eg);
    }
    return ret;
}

std::vector<int> GeneUtils::randomVectorIntNoRept(size_t size){
    assert(size<=details::rangement.second-details::rangement.first+1);
    auto& eg = details::getEngine();
    uniIntDis int_dis(details::rangement.first,details::rangement.second);
    std::vector<int> ret(size);
    std::unordered_set<int> us;
    for(auto &i:ret){
        int t=int_dis(eg);
        while(us.count(t)){
            t=int_dis(eg);
        }
        i=t;
        us.insert(t);
    }
    return ret;
}

List GeneUtils::randomList(size_t size){
    std::vector<int> v{};
    for(size_t i=0;i<size;++i){
        v.push_back(randomInt());
    }
    return List(std::move(v));
}