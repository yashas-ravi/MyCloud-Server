//linux service program to fetch system data
//this will run independently in background

#include <iostream>
#include <string>
#include <fstream>
#include <sys/statvfs.h>
#include <unistd.h>
#include <iomanip>
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
void ramStat(double &used, double &total){
    ifstream stat("/proc/meminfo");
    string line;
    size_t totalMemory=0, avalMemory=0;

    while(getline(stat,line)){
        if(line.find("MemTotal:")==0){
            sscanf(line.c_str(),"MemTotal: %zu kB",&totalMemory);
        }
        if(line.find("MemAvailable")==0){
            sscanf(line.c_str(),"MemAvailable: %zu kB",&avalMemory);
        }
    }
    stat.close();
    total=totalMemory/(1024.0*1024.0);
    used=(totalMemory-avalMemory)/(1024.0*1024.0);
}

void storageStat(){
    struct statvfs stat;
    if(statvfs("/home",&stat)!=0){
        cerr<<"Failed to get storage info !!! \n";
        return;
    }
    unsigned long long totalbytes = stat.f_blocks * stat.f_frsize;
    unsigned long long freebytes = stat.f_bfree * stat.f_frsize;
    unsigned long long usedbytes = totalbytes-freebytes;
    double total = totalbytes/(1024*1024*1024);
    double used = usedbytes/(1024*1024*1024);
    cout<<fixed<<setprecision(2);
    cout<<"Storage: "<<used<<" / "<<total<<" GB\n";
}

int main(){
    float cpu = cpuStat();
    sleep(1);
    cpu=cpuStat();
    double ramUsed=0.0, ramTotal=0.0;
    ramStat(ramUsed,ramTotal);
    cout<<fixed<<setprecision(2);
    cout<<"CPU: "<<cpu<<" usage\n";
    cout<<"RAM: "<<ramUsed<<" / "<<ramTotal<<" GB\n";
    storageStat();
    return 0;
}