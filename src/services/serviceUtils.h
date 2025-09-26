#ifndef SERVICEUTILS_H
#define SERVICEUTILS_H

#include <string>
#include <vector>
#include <mutex>

extern std::mutex tokenMutex;
extern std::vector<std::string> activeTokens;

float cpuStat();
std::string ramStat();
std::string storageStat();
std::string generateToken();
bool isValidToken(const std::string& token);
void addToken(const std::string& token);
std::string listDirectory(const std::string& path);
std::string calcSize(unsigned long long bytes);

#endif
