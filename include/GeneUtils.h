#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace GeneUtils{
    namespace details {
        inline std::mt19937_64& getEngine(){
            static thread_local std::mt19937_64 eg(std::random_device{}());
            return eg;
        }
        inline static std::pair<int, int> rangement{0,100};
    }
    
    void setRange(int begin,int end);

    int randomInt();

    std::vector<int> randomVectorInt(size_t size);

    std::vector<int> randomVectorIntNoRept(size_t size);
    
}