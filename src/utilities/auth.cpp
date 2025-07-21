// this program handles authentication
// user management and api gateway
#include "auth.h"
#include "bcrypt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

int auth::registerUser(string userName, string userPassword){
    this->userName=userName;
    filesystem::create_directory("data");
    ofstream dataFile("data/userdata.txt");

    if(dataFile.is_open()){
        string hashPass = bcrypt::generateHash(userPassword);
        dataFile<<userName+":"+hashPass+"\n";
        dataFile.close();
    }
    else{
        cerr<<"failed to create file.";
        return 1;
    }
    return 0;
}

int auth::validateUser(String pass){
    
}

string auth::getUser(){
    return userName;
}