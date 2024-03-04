/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
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

#include "tree.h"

void debug(char *message);
void error(char *message);
void info(char *message);
void success(char *message);
#endif