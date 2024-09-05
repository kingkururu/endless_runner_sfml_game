#include "utils.hpp"


namespace utils {
    std::vector<std::weak_ptr<unsigned char[]>> convertToWeakPtrVector(const std::vector<std::shared_ptr<unsigned char[]>>& bitMask) {
        std::vector<std::weak_ptr<unsigned char[]>> result;
        result.reserve(bitMask.size());
        for (const auto& ptr : bitMask) {
            result.push_back(std::weak_ptr<unsigned char[]>(ptr));
        }
         return result;
    }
}

