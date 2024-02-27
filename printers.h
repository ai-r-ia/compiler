#ifndef PRINTERS
#define PRINTERS
#define WHITE "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RED "\033[0;31m"
#define traceback(...)                             \
    do                                             \
    {                                              \
        printf("@ %s (%d): ", __FILE__, __LINE__); \
        printf(__VA_ARGS__);                       \
    } while (0)

void debug(char *message);
void error(char *message);
void info(char *message);
void success(char *message);
#endif