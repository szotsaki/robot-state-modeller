#include "Sleep.h"
#include <assert.h>
#include <QtGlobal>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

void r_sleepMs(const int ms)
{
    assert(ms > 0);

#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}

