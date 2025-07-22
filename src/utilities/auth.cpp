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
    filesystem::create_directory("data");
    ofstream dataFile("data/userdata.txt");

    if(dataFile.is_open()){
        string hashPass = bcrypt::generateHash(userPassword);
        dataFile<<userName+" : "+hashPass+"\n";
        dataFile.close();
    }
    else{
        cerr<<"failed to create file.";
        return 1;
    }
    return 0;
}

int auth::validateUser(string pass){
    ifstream dataFile("data/userdata.txt");
    int returnVal=0;
    if (dataFile.is_open())
    {
        string word;
        bool passflag=false;
        while (dataFile>>word)
        {
            if(passflag){
               returnVal = bcrypt::validatePassword(pass,word);
               break;
            }
            if(word==":"){
                passflag=true;
            }
        }
        dataFile.close();
    }
    else
        cerr<<"password hash or file not found \n";
    return returnVal;
}

string auth::getUser(){
    ifstream dataFile("data/userdata.txt");
    string userName;
    if(dataFile.is_open()){
       dataFile>>userName;
       dataFile.close();
       return userName;
    }
    else
        cerr<<"data file not found \n";
    return "null";
}