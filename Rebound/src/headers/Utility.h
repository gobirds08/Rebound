# pragma once

#include <random>

namespace RandomUtils {

    inline int getRandomInt(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());  
        std::uniform_int_distribution<> distr(min, max);
        return distr(gen);
    }

}

