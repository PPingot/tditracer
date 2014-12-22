
#include <unistd.h>

/*
 **************************************
 */
#ifdef __cplusplus
extern "C" {
#endif
int  tditrace_init(void);
void tditrace(const char *format, ...);
#ifdef __cplusplus
}
#endif
int tditrace_inited = 0;
#define TDITRACE(...)               \
    do                              \
    {                               \
        if (!tditrace_inited) {     \
            tditrace_init();        \
            tditrace_inited = 1;    \
        }                           \
        tditrace(__VA_ARGS__);      \
    } while (0)                     \
/*
 **************************************
 */

int main(int argc, char **argv)
{
    int i;

    printf("start...\n");

    for (i = 0; i < 10; i++) {
        // will all appear in the same "HELLO" , "NOTES"-timeline
        TDITRACE("HELLO");
        TDITRACE("HELLO %d", i);
        TDITRACE("HELLO %d %s %s", i, "yes", "no");

        // create separate "HELLO1", "HELLO2" ,..   "NOTES"-timelines
        TDITRACE("HELLO%d", i);

        // variable~value creates a QUEUES-timeline
        TDITRACE("i~%d", 12);
        usleep(10000);

        TDITRACE("i~%d", 16);
        usleep(10000);

        TDITRACE("i~%d", 8);
        usleep(100000);

        // create "TASKS"-timeline, using the @T+ and #T- identifier
        TDITRACE("@T+HELLO");
        usleep(50000);
        TDITRACE("@T-HELLO");

        usleep(50000);

        // create "EVENTS"-timeline, using the @E+ identifier
        TDITRACE("@E+HELLO");

        usleep(50000);
    }

    usleep(100000);
    TDITRACE("END");

    printf("...end\n");

    return 0;
}
