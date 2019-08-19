#include "sysinfo.h"

#include <QtGlobal>

#ifdef Q_OS_WIN
    #include "sysinfowindowimpl.h"
#elif defined (Q_OS_MAC)

#elif defined (Q_OS_LINUX)
    #include "sysinfolinuximpl.h"
#endif

SysInfo &SysInfo::instance() {
#ifdef Q_OS_WIN

#elif defined (Q_OS_MAC)

#elif defined (Q_OS_LINUX)
    static SysInfoLinuxImpl instance;
#endif

    return instance;
}

SysInfo::SysInfo()
{

}

SysInfo::~SysInfo()
{

}
