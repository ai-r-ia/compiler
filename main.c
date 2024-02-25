#include "whole_include.h"
#include "test/test.h"

void remove_comments();
void measure_execution_time();

int main(char *args)
{
    int option;
    do {
        printf("\nOptions:\n");
        printf("0: Exit\n");
        printf("1: Remove comments\n");
        printf("2: Print token list\n");
        printf("3: Parse and print parse tree\n");
        printf("4: Measure execution time\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        
        switch(option) {
            case 0:
                printf("Exiting...\n");
                break;
            case 1:
                remove_comments("test/t5.txt","test/t5_wo.txt");
                break;
            case 2:
                lexical_analysis();
                break;
            case 3:
                // parse_and_print_parse_tree();
                // break;
            case 4:
                measure_execution_time();
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while(option != 0);
    
    return 0;
}

void remove_comments(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file %s\n", input_filename);
        exit(1);
    }

    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file %s\n", output_filename);
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), input_file)) {
        char *comment_start = strchr(line, '%');
        if (comment_start != NULL) {
            *comment_start = '\0'; 
        }
        int i = strlen(line) - 1;
        while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r')) {
            line[i] = '\0';
            i--;
        }
        fprintf(output_file, "%s\n", line);
    }

    fclose(input_file);
    fclose(output_file);
}

void measure_execution_time() {
    clock_t start_time, end_time;

    double total_CPU_time, total_CPU_time_in_seconds;

    start_time = clock();

    lexical_analysis();
    // parser();

    end_time = clock();

    total_CPU_time = (double) (end_time - start_time);

    total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

    printf("\ntotal CPU time : %f",total_CPU_time);
    printf("\ntotal CPU time in seconds : %f",total_CPU_time_in_seconds);
}