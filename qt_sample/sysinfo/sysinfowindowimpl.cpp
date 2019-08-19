#include "sysinfowindowimpl.h"

#include <windows.h>

SysInfoWindowImpl::SysInfoWindowImpl() :
    SysInfo ()
{

}

double SysInfoWindowImpl::memoryUsed() {
    MEMORYSTATUSEX memoryStatus;
}
