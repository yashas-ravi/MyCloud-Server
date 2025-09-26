#include "crow_all.h"
#include "serviceUtils.h"
#include <iostream>
#include <unistd.h>

std::vector<std::string> activeTokens;
std::mutex tokenMutex;
const std::string PASSWORD = "mypassword";
const std::string ALLOWED_BASE = "/home";

using namespace std;

int main()
{
    crow::SimpleApp app;

    // Login route
    CROW_ROUTE(app, "/login").methods("POST"_method)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if(!body){
                return crow::response(400, "Invalid JSON");
            }
            std::string password = body["password"].s();  
            std::cout<<password;
            if (password == PASSWORD) {
                std::string token = generateToken();
                {
                    std::lock_guard<std::mutex> lock(tokenMutex);
                    activeTokens.push_back(token);
                }
                crow::json::wvalue res;
                res["token"] = token;
                return crow::response{res};
            }
            return crow::response(401, "Unauthorized");
        }
    );

    // CPU usage
    CROW_ROUTE(app, "/usage").methods("GET"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if(!body){return crow::response(400, "Invalid JSON");}
        std::string token = body["token"].s();
        if(!isValidToken(token)){
            return crow::response(401, "Unauthorized");
        }
        float cpu = cpuStat();
        sleep(1);
        cpu = cpuStat();
        crow::json::wvalue res;
        res["cpu"]=cpu;
        res["ram"]=ramStat();
        res["storage"]=storageStat();
        return crow::response{res};
    });

    // File system listing (secured)
    CROW_ROUTE(app, "/filesystem")
    .methods("GET"_method)
    ([](const crow::request& req) {
        auto token = req.url_params.get("token");
        auto path = req.url_params.get("path");

        if (!token || !isValidToken(token)) {
            return crow::response(403, "Forbidden");
        }

        std::string list = listDirectory(path ? path : ALLOWED_BASE);
        return crow::response(list);
    });

    app.port(8080).multithreaded().run();
}
