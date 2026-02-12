#include "FileWrite.h"
#include "GeneUtils.h"
#include "Solution.h"
#include "ThreadPool.h"
#include <atomic>
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int SAMPLE_NUMS = 1000;
constexpr std::size_t SIZE_VECTOR = 20;

void task(
    std::vector<int> nums,
    std::atomic_int &count,
    FileWrite *fw) 
{
    auto num1(nums);
    auto res = Solution().stdSolution(num1);
    auto num2(nums);
    auto check = Solution().mySolution(num2);

    std::string s{"Sample: "};
    ostringstream oss(s);
    for (const auto &i : nums) {
        oss << setw(3) << i << " ";
    }
    oss << "Result: ";
    if (res == check) {
        ++count;
        oss << setw(6) << res << "\n";
    } else {
        oss << "    stdSolution = " << res << ";"
            << "mySolution  = " << check << "\n";
    }
    fw->writeData(oss.str());
}

int main() {

    GeneUtils::setRange(0, 20);

    // io
    auto fw = FileWrite::getFileWritrHandle();
    std::atomic_int count = 0;

    {
        ThreadPool pool(8);

        for (int i = 0; i < SAMPLE_NUMS; ++i) {
            auto v = GeneUtils::randomVectorInt(SIZE_VECTOR);
            int k = 5;
            pool.addTask([v, k, &count, &fw]() -> void {
                task(v, count, fw.get());
            });
        }
    }

    std::string sum{};
    ostringstream oss(sum);
    oss << count << "/" << SAMPLE_NUMS;
    fw->writeData(oss.str());
    std::cout << oss.str() << std::endl;

    return 0;
}