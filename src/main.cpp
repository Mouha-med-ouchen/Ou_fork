#include <iostream>
#include <thread>
#include <chrono>
#include "../include/CpuMonitor.h"
#include "../include/MemoryMonitor.h"

int main() {
    CpuMonitor cpuMonitor;
    MemoryMonitor memMonitor;

    cpuMonitor.setUsageThreshold(75.0);

    cpuMonitor.setAlertCallback([](double usage) {
        std::cout << "[ALERT] CPU usage high: " << usage << "%" << std::endl;
    });

    while (true) {
        cpuMonitor.update();
        memMonitor.update();

        std::cout << cpuMonitor.exportAsText() << std::endl;
        std::cout << memMonitor.exportAsText() << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "-------------------------------------" << std::endl;
    }

    return 0;
}
