//
//  app.hpp
//  Hashs
//
//  Created by Adilson Tavares on 12/09/17.
//  Copyright © 2017 Adilson Tavares. All rights reserved.
//

#ifndef app_h
#define app_h

#include <iostream>
#include <vector>

#include "user.hpp"
#include "md5helper.hpp"
#include "timer.hpp"

class Application {
private:
    
    std::vector<User*> _users;
    
public:
    
    void load_users()
    {
        std::ifstream file(filePath);
        std::string line;
        
        _users.clear();
        
        do
        {
            getline(file, line);
            
            if (!line.empty())
            {
                const auto user = new User(line);
                _users.push_back(user);
            }
        }
        while (!line.empty());
        
        file.close();
    }
    
    void save_users()
    {
        std::ofstream file(filePath);
        
        for (auto it = _users.begin(); it != _users.end(); ++it) {
            file << (*it)->getData() << std::endl;
        }
        
        file.close();
    }
    
    void clear_screen()
    {
        std::cout << "\033[2J\033[1;1H";
    }
    
    void wait_char()
    {
        std::cout << "-" << std::endl;
        std::cout << "Pressione ENTER para continuar.";
        
        fseek(stdin, 0, SEEK_END);
        getchar();
    }
    
    void new_user()
    {
        char name[255];
        char password[255];
        
        std::cout << "# Cadastrar usuário" << std::endl;
        
        do
        {
            std::cout << "Nome: ";
            std::cin >> name;
            
            if (strlen(name) != 4)
                std::cout << "O nome precisa ter 4 caracters." << std::endl;
        }
        while (strlen(name) != 4);
        
        auto user = find_user(name);
        if (user)
        {
            std::cout << "Usuário já cadastrado." << std::endl;
            return wait_char();
        }
        
        do
        {
            std::cout << "Senha: ";
            std::cin >> password;
            
            if (strlen(password) != 4)
                std::cout << "A senha precisa ter 4 caracters." << std::endl;
        }
        while (strlen(password) != 4);
        
        user = new User(name, password);
        _users.push_back(user);
        
        std::cout << "Usuário cadastrado." << std::endl;
        
        save_users();
        wait_char();
    }
    
    void login()
    {
        char name[255];
        char password[255];
        
        std::cout << "# Realizar login" << std::endl;
        std::cout << "Nome: ";
        std::cin >> name;
        
        auto user = find_user(name);
        if (!user)
        {
            std::cout << "Usuário não encontrado." << std::endl;
            return wait_char();
        }
        
        std::cout << "Senha: ";
        std::cin >> password;
        
        if (user->checkPassword(password))
            std::cout << "Autenticado com sucesso!" << std::endl;
        else
            std::cout << "Credenciais inválidas." << std::endl;
        
        wait_char();
    }
    
    void user_brute_force()
    {
        char name[255];
        
        std::cout << "# Atacar usuário com força bruta" << std::endl;
        std::cout << "Nome: ";
        std::cin >> name;
        
        auto user = find_user(name);
        if (!user)
        {
            std::cout << "Usuário não encontrado." << std::endl;
            return wait_char();
        }
        
        std::cout << "Descobrindo senha para o hash " << user->getPasswordHash() << "..." << std::endl;
        std::string result = md5_brute_force(user->getPasswordHash(), 4);
        
        if (result.empty())
            std::cout << "Senha não encontrada." << std::endl;
        else
            std::cout << "Senha: " << result << std::endl;
        
        wait_char();
    }
    
    void all_users_brute_force()
    {
        std::cout << "# Atacar todos os usuários com força bruta" << std::endl;
        std::cout << "Iniciando ataque aos " << _users.size() << " usuários." << std::endl;
        
        for (auto it = _users.begin(); it != _users.end(); ++it)
        {
            const auto user = *it;
            std::cout << user->getName() << " -> " << std::flush;
            
            auto timer = Timer();
            auto result = md5_brute_force(user->getPasswordHash(), 4);
            
            if (result.empty())
                result = "[NÃO ENCONTRADA]";
            else
                result = "\"" + result + "\"";
            
            std::cout << result;
            printf(" (%.04lfs)\n", timer.elapsed());
        }
        
        wait_char();
    }
    
    User *find_user(const std::string& name)
    {
        const auto it = std::find_if(_users.begin(), _users.end(), [&](User *user) { return user->getName() == name; });
        
        if (it == _users.end())
            return 0;
        
        return *it;
    }
    
    bool menu()
    {
        clear_screen();
        
        std::cout << "# O que deseja fazer?" << std::endl;
        std::cout << "1. Cadastrar usuário." << std::endl;
        std::cout << "2. Realizar login." << std::endl;
        std::cout << "3. Atacar usuário com força bruta." << std::endl;
        std::cout << "4. Atacar todos os usuários com força bruta." << std::endl;
        std::cout << "0. Sair." << std::endl;
        std::cout << "Opção: ";
        
        int option;
        std::cin >> option;
        
        clear_screen();
        
        switch (option) {
            case 0:
                return false;
                
            case 1:
                new_user();
                break;
                
            case 2:
                login();
                break;
                
            case 3:
                user_brute_force();
                break;
                
            case 4:
                all_users_brute_force();
                break;
        }
        
        return true;
    }
    
    void run()
    {
        load_users();
        while (menu());
    }
};

#endif /* app_h */
