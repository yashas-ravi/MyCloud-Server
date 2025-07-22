#pragma once
#ifndef AUTH_H
#define AUTH_H

#include <string>

class auth{
    public:
        int registerUser(std::string userName, std::string userPassword);
        int validateUser(std::string pass);
        std::string getUser();
};

#endif