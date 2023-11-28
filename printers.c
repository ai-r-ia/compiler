#include "printers.h"
#include "whole_include.h"
void debug(char *message) { printf("%sDebug:- %s %s\n", WHITE, message, WHITE); }
void error(char *message) { printf("%sError:- %s %s\n", RED, message, WHITE); }
void info(char *message) { printf("%sinfo:- %s %s\n", BLUE, message, WHITE); }
void success(char *message) { printf("%sSuccess:- %s %s\n", GREEN, message, WHITE); }