//
//  user.hpp
//  Hashs
//
//  Created by Adilson Tavares on 12/09/17.
//  Copyright © 2017 Adilson Tavares. All rights reserved.
//

#ifndef user_h
#define user_h

#include <iostream>
#include <fstream>
#include <unistd.h>

#include "md5.h"
#include "global.h"

class User {
private:
    
    std::string _name;
    std::string _passwordHash;
    
    int _tries;
    
public:
    
    User(const std::string& data) {
        
        const auto index = data.find(';');
        _name = data.substr(0, index);
        _passwordHash = data.substr(index + 1);
        
        _tries = 0;
    }
    
    User(const std::string& name, const std::string& password) {
        
        _name = name;
        _passwordHash = MD5(password).hexdigest();
    }
    
    void setName(const std::string& name)
    {
        _name = name;
    }
    
    void setPassword(const std::string& password)
    {
        _tries = 0;
        _passwordHash = MD5(password).hexdigest();
    }
    
    std::string getName()
    {
        return _name;
    }
    
    std::string getPasswordHash()
    {
        return _passwordHash;
    }
    
    bool checkPassword(const std::string& password) {
        
        bool success = MD5(password).hexdigest() == _passwordHash;
        _tries = success ? 0 : _tries + 1;
        
        if (_tries >= 3) {
            sleep(1);
        }
        
        return success;
    }
    
    std::string getData() {
        return _name + ";" + _passwordHash;
    }
    
    bool login() {
        
        char password[255];
        
        std::cout << "Senha: ";
        std::cin >> password;
        
        return checkPassword(password);
    }
};

#endif /* user_h */
