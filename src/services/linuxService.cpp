//linux service program to fetch system data
//this will run independently in background

#include <iostream>
#include <string>
#include <fstream>
#include <sys/statvfs.h>
using namespace std;

//read cpu usage
float cpuStat(){
    ifstream stat("/proc/stat");
    string line;
    getline(stat,line);
    stat.close();

    size_t user, nice, system, idle;
    sscanf(line.c_str(),"cpu %zu %zu %zu %zu", &user, &nice, &system, &idle);

    static size_t prevIdle=0, prevTotal=0;
    size_t idleTime = idle;
    size_t totalTime = user+nice+system+idle;
    size_t deltaIdle = idleTime - prevIdle;
    size_t deltaTotal = totalTime - prevTotal;

    prevIdle=idleTime;
    prevTotal=totalTime;

    if(deltaTotal==0) return 0.0f;
    return 100.0f*(1.0f-(float)deltaIdle/deltaTotal);
}

//read ram usage
void ramStat(size_t &used, size_t &total){
    ifstream stat("/proc/meminfo");
    string line;
    size_t totalMemory=0, avalMemory=0;

    while(getline(stat,line)){
        if(line.find("MemTotal:")){
            sscanf(line.c_str(),"MemTotal: %zu kB",&totalMemory);
        }
        if(line.find("MemAvailable")){
            sscanf(line.c_str(),"MemAvailable: %zu kB",&avalMemory);
        }
    }
    stat.close();
    total=totalMemory/1024;
    used=(totalMemory-avalMemory)/1024;
}

void storageStat(){
    struct statvfs stat;
    if(statvfs("/",&stat)!=0){
        cerr<<"Failed to get storage info !!! \n";
    }

    unsigned long long total = stat.f_blocks * stat.f_frsize;
    unsigned long long free = stat.f_bavail * stat.f_frsize;
    unsigned long long used = total-free;
}

void main(){

}