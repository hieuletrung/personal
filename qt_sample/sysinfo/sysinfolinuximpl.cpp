#include "sysinfolinuximpl.h"

#include <QtGlobal>
#include <QFile>

#include <sys/types.h>
#include <sys/sysinfo.h>

SysInfoLinuxImpl::SysInfoLinuxImpl() : SysInfo(), mCpuLoadLastValues()
{
}

SysInfoLinuxImpl::~SysInfoLinuxImpl() {

}

void SysInfoLinuxImpl::init() {
    mCpuLoadLastValues = cpuRawData();
}

double SysInfoLinuxImpl::memoryUsed() {
    struct sysinfo memInfo;
    sysinfo(&memInfo);

    qulonglong totalMemory = memInfo.totalram;
    totalMemory += memInfo.totalswap;
    totalMemory *= memInfo.mem_unit;

    qulonglong totalMemoryUsed = memInfo.totalram - memInfo.freeram;
    totalMemoryUsed += memInfo.totalswap - memInfo.freeswap;
    totalMemoryUsed *= memInfo.mem_unit;

    double percent = (double)totalMemoryUsed / (double)totalMemory * 100.0;

    return qBound(0.0, percent, 100.0);
}

double SysInfoLinuxImpl::cpuLoadAverage() {
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;

    double overral = (secondSample[0] - firstSample[0]) +
            (secondSample[1] - firstSample[1]) +
            (secondSample[2] - firstSample[2]);

    double total = overral + (secondSample[3] - firstSample[3]);
    double percent = (overral / total) * 100.0;

    return qBound(0.0, percent, 100.0);
}

QVector<qulonglong> SysInfoLinuxImpl::cpuRawData() {
    QFile file("/proc/stat");
    file.open(QIODevice::ReadOnly);

    QByteArray line = file.readLine();
    file.close();

    qulonglong totalUser = 0;
    qulonglong totalUserNice = 0;
    qulonglong totalSystem = 0;
    qulonglong totalIdle = 0;

    std::sscanf(line.data(), "cpu %llu %llu %llu %llu", &totalUser, &totalUserNice, &totalSystem, &totalIdle);

    QVector<qulonglong> rawData;
    rawData.append(totalUser);
    rawData.append(totalUserNice);
    rawData.append(totalSystem);
    rawData.append(totalIdle);

    return rawData;
}
