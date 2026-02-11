#include "GeneUtils.h"
#include "Solution.h"
#include "ThreadPool.h"
#include <atomic>
#include <climits>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <vector>

constexpr int SAMPLE_NUMS = 100000;
constexpr std::size_t SIZE_VECTOR = 20;

void task(std::vector<int> nums, std::mutex &mtx_io, std::atomic_int &count) {
    auto num1(nums);
    auto res = Solution().stdSolution(num1);
    auto num2(nums);
    auto check = Solution().mySolution(num2);
    if (res == check) {
        ++count;
    } else {
        std::lock_guard<std::mutex> locker(mtx_io);
        std::cout << "A counter example: ";
        for (const auto &n : nums) {
            std::cout << std::setw(3) << n << " ";
        }
        std::cout << "\n     Result1     = " << res;
        std::cout << "\n     Result2     = " << check << std::endl;
    }
}

int main() {

    GeneUtils::setRange(-10, 10);

    // io
    std::mutex mtx_io;
    std::atomic_int count = 0;

    {
        ThreadPool pool(8);

        for (int i = 0; i < SAMPLE_NUMS; ++i) {
            auto v = GeneUtils::randomVectorInt(SIZE_VECTOR);
            int k = 5;
            pool.addTask(
                [v, k, &mtx_io, &count]() -> void { 
                    task(v, mtx_io, count); 
                });
        }
    }

    std::cout << count << "/" << SAMPLE_NUMS << std::endl;

    return 0;
}