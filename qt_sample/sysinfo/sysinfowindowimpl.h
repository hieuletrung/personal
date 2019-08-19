#ifndef SYSINFOWINDOWIMPL_H
#define SYSINFOWINDOWIMPL_H

#include "sysinfo.h"

class SysInfoWindowImpl : public SysInfo
{
public:
    SysInfoWindowImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;
};

#endif // SYSINFOWINDOWIMPL_H
