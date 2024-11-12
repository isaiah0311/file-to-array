/**
 * \file main.c
 * \author Isaiah Lateer
 * 
 * Converts a file to a byte array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Entry point for the program.
 * 
 * \param[in] argc Number of command line arguments.
 * \param[in] argv Array of command line arguments.
 * \return Exit code.
 */
int main(int argc, char** argv) {
    char* in_file_path = NULL;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-i")) {
            if (++i < argc) {
                in_file_path = argv[i];
            } else {
                fprintf(stderr, "[ERROR] Missing input file after -i.\n");
                return EXIT_FAILURE;
            }
        } else {
            fprintf(stderr, "[WARN] Skipping invalid parameter: %s.\n",
                argv[i]);
        }
    }

    if (!in_file_path) {
        fprintf(stderr, "[ERROR] No input file given.\n");
        return EXIT_FAILURE;
    }

    FILE* in_file = fopen(in_file_path, "rb");

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
