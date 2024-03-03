#ifndef DRIVER
#define DRIVER

// Function to remove comments from a file
void remove_comments(const char *input_filename, const char *output_filename);

// Function to measure execution time
void measure_execution_time();

// driver function to allow users to perform an execution of their choice
void driver();

void lexical_analysis();
#endif