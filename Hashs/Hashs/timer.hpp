//
//  timer.hpp
//  Hashs
//
//  Created by Adilson Tavares on 13/09/17.
//  Copyright © 2017 Adilson Tavares. All rights reserved.
//

#ifndef timer_h
#define timer_h

#include <iostream>
#include <chrono>

class Timer {
private:
    
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    
public:
    
    Timer()
    {
        reset();
    }
    
    void reset()
    {
        _start = std::chrono::high_resolution_clock::now();
    }
    
    double elapsed()
    {
        auto diff = std::chrono::high_resolution_clock::now() - _start;
        return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(diff).count();
    }
};

#endif /* timer_h */
