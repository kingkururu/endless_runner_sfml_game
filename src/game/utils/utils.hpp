#pragma once

#ifndef utils_hpp
#define utils_hpp

#include <vector>
#include <memory>


namespace utils {
    std::vector<std::weak_ptr<unsigned char[]>> convertToWeakPtrVector(const std::vector<std::shared_ptr<unsigned char[]>>& bitMask);
    
    // template<typename SpriteType>
    // std::shared_ptr<SpriteType> convertToWe
}


#endif // utils_hpp