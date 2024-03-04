/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
#include "printers.h"
#include "whole_include.h"
void debug(char *message) { printf("%sDebug:- %s %s\n", WHITE, message, WHITE); }
void error(char *message) { printf("%s%s %s\n", RED, message, WHITE); }
void info(char *message) { printf("%sinfo:- %s %s\n", BLUE, message, WHITE); }
void success(char *message) { printf("%sSuccess:- %s %s\n", GREEN, message, WHITE); }
