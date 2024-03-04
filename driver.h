/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#ifndef DRIVER
#define DRIVER

// Function to remove comments from a file
void remove_comments(const char *input_filename, const char *output_filename);

// Function to measure execution time
void measure_execution_time(char *filename);

// driver function to allow users to perform an execution of their choice
void driver();

void lexical_analysis(char *filename);
#endif