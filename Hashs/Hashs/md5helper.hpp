//
//  md5helper.hpp
//  Hashs
//
//  Created by Adilson Tavares on 12/09/17.
//  Copyright © 2017 Adilson Tavares. All rights reserved.
//

#ifndef md5helper_h
#define md5helper_h

#include <iostream>
#include "user.hpp"

std::string md5_brute_force(User *user, int length, std::string current = "")
{
    if (user->checkPassword(current))
        return current;
     
    if (length <= 0)
        return "";
    
    // Try every possible value
//    std::vector<char> allowed;
//    for (int i = 0; i <= 255; ++i)
//        allowed.push_back(i);
    
    // Try only fonetic characters
    const std::string allowedChars = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::vector<char> allowed(allowedChars.size());
    allowed.reserve(allowedChars.size());
    std::transform(allowedChars.begin(), allowedChars.end(), allowed.begin(), [](char c) { return c; });
    
    for (int i = 0; i < allowed.size(); ++i) {
        
        std::string result = md5_brute_force(user, length - 1, current + std::string(1, (char)allowed[i]));
        
        if (!result.empty())
            return result;
    }
    
    return "";
}

#endif /* md5helper_h */
