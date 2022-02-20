#include <stdio.h>
#include <sys/time.h>

int main()
{
    struct timeval tv;
    struct timezone tz;
    long ts;

    gettimeofday(&tv,&tz);
    ts = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    printf("Seconds since 1/1/1970: %lu\n",ts);
    printf("Microseconds: %d\n",tv.tv_usec);
    printf("Minutes west of Greenwich: %d\n",tz.tz_minuteswest);
    printf("Daylight Saving Time adjustment: %d\n",tz.tz_dsttime);

    return(0);
}
