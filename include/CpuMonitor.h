#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <string>
#include <map>
#include <functional>

class CpuMonitor {
public:
    CpuMonitor();
    ~CpuMonitor();

    bool update();
    double getTotalUsage() const;
    std::map<std::string, double> getCoreUsage() const;
    std::string exportAsText() const;
    std::string exportAsCSV() const;

    // Alert feature
    void setUsageThreshold(double threshold);
    void setAlertCallback(std::function<void(double)> callback);

private:
    struct CPUData {
        unsigned long long user = 0;
        unsigned long long nice = 0;
        unsigned long long system = 0;
        unsigned long long idle = 0;
        unsigned long long iowait = 0;
        unsigned long long irq = 0;
        unsigned long long softirq = 0;
        unsigned long long steal = 0;
        unsigned long long guest = 0;
        unsigned long long guest_nice = 0;
    };

    std::map<std::string, CPUData> prevCpuData;
    std::map<std::string, CPUData> currentCpuData;
    std::map<std::string, double> cpuUsage;

    double calculateUsage(const CPUData& prev, const CPUData& current) const;
    bool readCpuData();
    void checkAlerts();

    // Alert members
    double usageThreshold = 90.0; // default threshold 90%
    std::function<void(double)> alertCallback = nullptr;
};

#endif
