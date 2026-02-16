#include "FileWrite.h"
#include "GeneUtils.h"
#include "ListNode.h"
#include "Solution.h"
#include "ThreadPool.h"
#include <atomic>
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>

constexpr int SAMPLE_NUMS = 10;
constexpr std::size_t SIZE_VECTOR = 20;

void task(
    std::atomic_int &count,
    FileWrite *fw) 
{
    auto l = GeneUtils::randomList(SIZE_VECTOR);
    auto l1(l);
    Solution().stdSolution(l1.getHead());
    auto l2(l);
    Solution().mySolution(l2.getHead());

    std::string s{};
    ostringstream oss(s);
    oss << "Sample: \n";

    auto p=l1.getHead();
    std::unordered_set<ListNode*> st1;
    while(p){
        if(st1.count(p)) break;
        st1.insert(p);
        oss << setw(6) << p->val;
        p=p->next;
    }
    oss << "\n";
    p=l2.getHead();
    std::unordered_set<ListNode*> st2;
    while(p){
        if(st2.count(p)) break;
        st2.insert(p);
        oss << setw(6) << p->val;
        p=p->next;
    }
    oss << "\n";

    fw->writeData(oss.str());

}

int main() {
    
    GeneUtils::setRange(0, 20);

    auto fw = FileWrite::getFileWritrHandle();
    std::atomic_int count = 0;

    {
        ThreadPool pool(8);
        for (int i = 0; i < SAMPLE_NUMS; ++i) {
            pool.addTask([&count, &fw]() -> void {
                task(count, fw.get());
            });
        }
    }

    // std::string sum{};
    // ostringstream oss(sum);
    // oss << count << "/" << SAMPLE_NUMS;
    // fw->writeData(oss.str());
    // std::cout << oss.str() << std::endl;

    return 0;
}