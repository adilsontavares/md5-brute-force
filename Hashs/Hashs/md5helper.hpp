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

std::string md5_brute_force(std::string target, int length, std::string current = "")
{
    if (MD5(current).hexdigest() == target)
        return current;
    
    if (length <= 0)
        return "";
    
    const std::string allowed = "abcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < allowed.size(); ++i) {
        
        std::string result = md5_brute_force(target, length - 1, current + std::string(1, allowed[i]));
        if (!result.empty())
            return result;
    }
    
    return "";
}

#endif /* md5helper_h */
