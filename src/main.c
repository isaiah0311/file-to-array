/**
 * \file main.c
 * \author Isaiah Lateer
 * 
 * Converts a file to a byte array.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Entry point for the program. Reads in a file, then converts the data into a
 * byte array.
 * 
 * \param[in] argc Number of command line arguments.
 * \param[in] argv Array of command line arguments.
 * \return Exit code.
 */
int main(int argc, char** argv) {
    char* file_path = NULL;
    unsigned bytes_per_line = 12;
    bool vector_mode = false;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-i")) {
            if (++i < argc) {
                file_path = argv[i];
            } else {
                fprintf(stderr, "[ERROR] Missing input file after -i.\n");
                return EXIT_FAILURE;
            }
        } else if (!strcmp(argv[i], "-n")) {
            if (++i < argc) {
                int result = sscanf(argv[i], "%u", &bytes_per_line);
                if (!result) {
                    fprintf(stderr, "[ERROR] Invalid number of bytes per "
                        "line.\n");
                    return EXIT_FAILURE;
                }
            } else {
                fprintf(stderr, "[ERROR] Missing bytes per line after -n.\n");
                return EXIT_FAILURE;
            }
        } else if (!strcmp(argv[i], "-v")) {
            vector_mode = true;
        } else {
            fprintf(stderr, "[WARN] Skipping invalid parameter: %s.\n",
                argv[i]);
        }
    }

    if (!file_path) {
        fprintf(stderr, "[ERROR] No input file given.\n");
        return EXIT_FAILURE;
    }

    FILE* file = fopen(file_path, "rb");

    if (!file) {
        fprintf(stderr, "[ERROR] Failed to open input file.\n");
        return EXIT_FAILURE;
    }

    int result = fseek(file, 0, SEEK_END);
    if (result) {
        fprintf(stderr, "[ERROR] Failed to seek in file.\n");
        return EXIT_FAILURE;
    }

    long file_size = ftell(file);
    rewind(file);

    if (vector_mode) {
        printf("const std::vector<unsigned char> data = {\n    ");
    } else {
        printf("const unsigned char data[] = {\n    ");
    }

    unsigned line_count = 0;
    unsigned total_count = 0;

    while (!feof(file)) {
        unsigned char byte = 0;
        
        if (!fread(&byte, sizeof(byte), 1, file)) {
            break;
        }

        printf("0x%.2X", (int) byte);
        
        if (++total_count == file_size) {
            break;
        }

        if (bytes_per_line && ++line_count == bytes_per_line) {
            printf(",\n    ");
            line_count = 0;
        } else {
            printf(", ");
        }
    }

    if (vector_mode) {
        printf("\n};\n");
    } else {
        printf("\n};\n\nsize_t count = %u;\n", total_count);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
