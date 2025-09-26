#include "serviceUtils.h"
#include <fstream>
#include <sstream>
#include <sys/statvfs.h>
#include <iomanip>
#include <random>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

#define ALLOWED_BASE "/home"
#define MAX_LIST_ENTRIES 1000

// CPU usage calculation
float cpuStat() {
    ifstream stat("/proc/stat");
    string line;
    getline(stat, line);
    stat.close();

    size_t user, nice, system, idle;
    sscanf(line.c_str(), "cpu %zu %zu %zu %zu", &user, &nice, &system, &idle);

    static size_t prevIdle = 0, prevTotal = 0;
    size_t idleTime = idle;
    size_t totalTime = user + nice + system + idle;
    size_t deltaIdle = idleTime - prevIdle;
    size_t deltaTotal = totalTime - prevTotal;

    prevIdle = idleTime;
    prevTotal = totalTime;

    if (deltaTotal == 0) return 0.0f;
    return 100.0f * (1.0f - (float)deltaIdle / deltaTotal);
}

// RAM usage
string ramStat() {
    string used, total;
    ifstream stat("/proc/meminfo");
    string line;
    size_t totalMemory = 0, avalMemory = 0;

    while (getline(stat, line)) {
        if (line.find("MemTotal:") == 0) {
            sscanf(line.c_str(), "MemTotal: %zu kB", &totalMemory);
        }
        if (line.find("MemAvailable") == 0) {
            sscanf(line.c_str(), "MemAvailable: %zu kB", &avalMemory);
        }
    }
    stat.close();

    total = to_string(totalMemory / (1024 * 1024.0));
    used = to_string((totalMemory - avalMemory) / (1024 * 1024.0));
    return used + "/" + total;
}

// Storage usage
string storageStat() {
    struct statvfs stat;
    if (statvfs(ALLOWED_BASE, &stat) != 0) return "500";

    unsigned long long totalbytes1 = stat.f_blocks * stat.f_frsize;
    unsigned long long freebytes1 = stat.f_bfree * stat.f_frsize;
    unsigned long long usedbytes1 = totalbytes1 - freebytes1;

    if (statvfs("/", &stat) != 0) return "500";
    unsigned long long totalbytes2 = stat.f_blocks * stat.f_frsize;
    unsigned long long freebytes2 = stat.f_bfree * stat.f_frsize;
    unsigned long long usedbytes2 = totalbytes2 - freebytes2;

    string total = to_string((totalbytes1 + totalbytes2) / (1024 * 1024 * 1024));
    string used = to_string((usedbytes1 + usedbytes2) / (1024 * 1024 * 1024));
    return used + "/" + total;
}

// Token generation
string generateToken() {
    static const char chars[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, sizeof(chars) - 2);

    string token;
    for (int i = 0; i < 32; i++) {
        token += chars[dist(gen)];
    }
    return token;
}

// Token validation
bool isValidToken(const string& token) {
    lock_guard<mutex> lock(tokenMutex);
    return find(activeTokens.begin(), activeTokens.end(), token) != activeTokens.end();
}

// Add token
void addToken(const string& token) {
    lock_guard<mutex> lock(tokenMutex);
    activeTokens.push_back(token);
}

// List directory
string listDirectory(const string& path) {
    error_code ec;
    fs::path requested = fs::weakly_canonical(fs::path(path), ec);
    if (ec) return "500 Failed to resolve path";

    fs::path allowed = fs::weakly_canonical(fs::path(ALLOWED_BASE), ec);
    if (ec) return "500 Failed to resolve allowed base";

    auto allowedStr = allowed.string();
    auto reqStr = requested.string();
    if (allowedStr.back() != '/') allowedStr += '/';
    if (reqStr.back() != '/') reqStr += '/';

    if (reqStr.find(allowedStr) != 0) return "403 Forbidden";

    if (!fs::exists(requested) || !fs::is_directory(requested)) return "404 Not Found";

    ostringstream out;
    size_t count = 0;
    for (auto& entry : fs::directory_iterator(requested, ec)) {
        if (ec) break;
        if (count++ >= MAX_LIST_ENTRIES) {
            out << "... (truncated)\n";
            break;
        }
        string name = entry.path().filename().string();
        if (name[0] == '.') continue;
        if (entry.is_directory(ec)) {
            out << "[DIR]  " << name << "\n";
        }
        else if (entry.is_regular_file(ec)) {
            unsigned long long size = fs::file_size(entry.path(), ec);
            out << "[FILE] " << name << " (" << calcSize(size) << ")\n";
        }
        else {
            out << "[OTHER] " << name << "\n";
        }
    }
    return out.str();
}

// Calculate human-readable file size
string calcSize(unsigned long long bytes) {
    const char* units[] = { "B","KB","MB","GB","TB" };
    double b = (double)bytes;
    int i = 0;
    while (b >= 1024.0 && i < 4) { b /= 1024.0; ++i; }
    ostringstream ss;
    ss << fixed << setprecision(2) << b << " " << units[i];
    return ss.str();
}
