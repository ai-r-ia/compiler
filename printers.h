#ifndef PRINTERS
#define PRINTERS
#define WHITE "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RED "\033[0;31m"

void debug(char *message);
void error(char *message);
void info(char *message);
void success(char *message);
#endif