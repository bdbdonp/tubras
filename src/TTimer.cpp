//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <algorithm>

#ifndef TUBRAS_PLATFORM_WINDOWS
#include <sys/time.h>
#endif

namespace Tubras {
#ifndef mymin
    #define mymin(a,b) (a > b ? a : b)
#endif

    //-----------------------------------------------------------------------
    //                             T T i m e r
    //-----------------------------------------------------------------------
    TTimer::TTimer()
    {
#ifdef TUBRAS_PLATFORM_WINDOWS
        QueryPerformanceFrequency(&mClockFrequency);
#endif
        reset();
    }

    //-----------------------------------------------------------------------
    //                            ~ T T i m e r
    //-----------------------------------------------------------------------
    TTimer::~TTimer()
    {
    }

    //-----------------------------------------------------------------------
    //                               r e s e t
    //-----------------------------------------------------------------------
    void TTimer::reset()
    {
#ifdef TUBRAS_PLATFORM_WINDOWS
        QueryPerformanceCounter(&mStartTime);
        mStartTick = GetTickCount();
        mPrevElapsedTime = 0;
#else
        gettimeofday(&mStartTime, 0);
#endif
    }

    //-----------------------------------------------------------------------
    //                       g e t M i l l i S e c o n d s
    //-----------------------------------------------------------------------
    unsigned long TTimer::getMilliSeconds()
    {
#ifdef TUBRAS_PLATFORM_WINDOWS
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        LONGLONG elapsedTime = currentTime.QuadPart - 
            mStartTime.QuadPart;

        // Compute the number of millisecond ticks elapsed.
        unsigned long msecTicks = (unsigned long)(1000 * elapsedTime / 
            mClockFrequency.QuadPart);

        // Check for unexpected leaps in the Win32 performance counter.  
        // (This is caused by unexpected data across the PCI to ISA 
        // bridge, aka south bridge.  See Microsoft KB274323.)
        unsigned long elapsedTicks = GetTickCount() - mStartTick;
        signed long msecOff = (signed long)(msecTicks - elapsedTicks);
        if (msecOff < -100 || msecOff > 100)
        {
            // Adjust the starting time forwards.
            LONGLONG msecAdjustment = mymin(msecOff * 
                mClockFrequency.QuadPart / 1000, elapsedTime - 
                mPrevElapsedTime);
            mStartTime.QuadPart += msecAdjustment;
            elapsedTime -= msecAdjustment;

            // Recompute the number of millisecond ticks elapsed.
            msecTicks = (unsigned long)(1000 * elapsedTime / 
                mClockFrequency.QuadPart);
        }

        // Store the current elapsed time for adjustments next time.
        mPrevElapsedTime = elapsedTime;

        return msecTicks;
#else
        struct timeval currentTime;
        gettimeofday(&currentTime, 0);
        return (currentTime.tv_sec - mStartTime.tv_sec) * 1000 + 
            (currentTime.tv_usec - mStartTime.tv_usec) / 1000;
#endif 
    }

    //-----------------------------------------------------------------------
    //                       g e t M i c r o S e c o n d s
    //-----------------------------------------------------------------------
    unsigned long TTimer::getMicroSeconds()
    {
#ifdef TUBRAS_PLATFORM_WINDOWS
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        LONGLONG elapsedTime = currentTime.QuadPart - 
            mStartTime.QuadPart;

        // Compute the number of millisecond ticks elapsed.
        unsigned long msecTicks = (unsigned long)(1000 * elapsedTime / 
            mClockFrequency.QuadPart);

        // Check for unexpected leaps in the Win32 performance counter.  
        // (This is caused by unexpected data across the PCI to ISA 
        // bridge, aka south bridge.  See Microsoft KB274323.)
        unsigned long elapsedTicks = GetTickCount() - mStartTick;
        signed long msecOff = (signed long)(msecTicks - elapsedTicks);
        if (msecOff < -100 || msecOff > 100)
        {
            // Adjust the starting time forwards.
            LONGLONG msecAdjustment = mymin(msecOff * 
                mClockFrequency.QuadPart / 1000, elapsedTime - 
                mPrevElapsedTime);
            mStartTime.QuadPart += msecAdjustment;
            elapsedTime -= msecAdjustment;
        }

        // Store the current elapsed time for adjustments next time.
        mPrevElapsedTime = elapsedTime;

        // Convert to microseconds.
        unsigned long usecTicks = (unsigned long)(1000000 * elapsedTime / 
            mClockFrequency.QuadPart);

        return usecTicks;
#else
        struct timeval currentTime;
        gettimeofday(&currentTime, 0);
        return (currentTime.tv_sec - mStartTime.tv_sec) * 1000000 + 
            (currentTime.tv_usec - mStartTime.tv_usec);
#endif
    }

    //-----------------------------------------------------------------------
    //                       g e t L o c a l T i m e
    //-----------------------------------------------------------------------
    void TTimer::getLocalTime(int* h, int* m, int* s, int* ms)
    {
#ifdef TUBRAS_PLATFORM_WINDOWS
        SYSTEMTIME stime;
        GetLocalTime(&stime);
        *h = stime.wHour;
        *m = stime.wMinute;
        *s = stime.wSecond;
        *ms = stime.wMilliseconds;
#else
        time_t ltime; /* calendar time */  
        ltime=time(NULL); /* get current cal time */  
        struct tm* TM = localtime(&ltime);
        *h = TM->tm_hour;
        *m = TM->tm_min;
        *s = TM->tm_sec;
        *ms = 0;
#endif
    }
}

