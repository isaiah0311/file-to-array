/**
 * \file main.c
 * \author Isaiah Lateer
 * 
 * Converts a file to a byte array.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Entry point for the program.
 * 
 * \return Exit code.
 */
int main() {
    FILE* in_file = fopen("res/test.txt", "rb");

    if (!in_file) {
        fprintf(stderr, "[ERROR] Failed to open input file.\n");
        return EXIT_FAILURE;
    }

    int result = fseek(in_file, 0, SEEK_END);
    if (result) {
        fprintf(stderr, "[ERROR] Failed to seek in file.\n");
        return EXIT_FAILURE;
    }

    long in_file_size = ftell(in_file);
    rewind(in_file);

    printf("unsigned char data[] = {\n    ");

    unsigned line_count = 0;
    unsigned total_count = 0;

    while (!feof(in_file)) {
        unsigned char byte = 0;
        
        if (!fread(&byte, sizeof(byte), 1, in_file)) {
            break;
        }

        printf("0x%.2X", (int) byte);
        
        if (++total_count == in_file_size) {
            break;
        }

        if (++line_count == 12) {
            printf(",\n    ");
            line_count = 0;
        } else {
            printf(", ");
        }
    }

    printf("\n};\n\nsize_t count = %u;\n", total_count);

    fclose(in_file);
    return EXIT_SUCCESS;
}
