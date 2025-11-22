#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Argument count check
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    char *inputName = argv[1];
    char *outputName = NULL;
    FILE *inputFile, *outputFile;

    if (argc == 3)
        outputName = argv[2];

    // Input and output must differ
    if (outputName && strcmp(inputName, outputName) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
    }

    // Open input file
    inputFile = fopen(inputName, "r");
    if (!inputFile) {
        fprintf(stderr, "error: cannot open file '%s'\n", inputName);
        exit(1);
    }

    // Open output file (if specified)
    if (outputName) {
        outputFile = fopen(outputName, "w");
        if (!outputFile) {
            fprintf(stderr, "error: cannot open file '%s'\n", outputName);
            fclose(inputFile);
            exit(1);
        }
    } else {
        outputFile = stdout;
    }

    // Read all lines dynamically into memory
    size_t capacity = 100;  // initial number of lines
    size_t lineCount = 0;
    char **lines = malloc(capacity * sizeof(char*));
    if (!lines) {
        fprintf(stderr, "malloc failed\n");
        fclose(inputFile);
        if (outputName) fclose(outputFile);
        exit(1);
    }

    size_t bufsize = 256;
    char *buffer = malloc(bufsize);
    if (!buffer) {
        fprintf(stderr, "malloc failed\n");
        free(lines);
        fclose(inputFile);
        if (outputName) fclose(outputFile);
        exit(1);
    }

    size_t len = 0;
    int ch;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (len + 1 >= bufsize) {
            bufsize *= 2;
            char *newBuffer = realloc(buffer, bufsize);
            if (!newBuffer) {
                fprintf(stderr, "malloc failed\n");
                free(buffer);
                for (size_t i = 0; i < lineCount; i++)
                    free(lines[i]);
                free(lines);
                fclose(inputFile);
                if (outputName) fclose(outputFile);
                exit(1);
            }
            buffer = newBuffer;
        }

        buffer[len++] = (char)ch;

        // End of a line
        if (ch == '\n') {
            buffer[len] = '\0';
            if (lineCount >= capacity) {
                capacity *= 2;
                char **newLines = realloc(lines, capacity * sizeof(char*));
                if (!newLines) {
                    fprintf(stderr, "malloc failed\n");
                    free(buffer);
                    for (size_t i = 0; i < lineCount; i++)
                        free(lines[i]);
                    free(lines);
                    fclose(inputFile);
                    if (outputName) fclose(outputFile);
                    exit(1);
                }
                lines = newLines;
            }

            lines[lineCount] = malloc(len + 1);
            if (!lines[lineCount]) {
                fprintf(stderr, "malloc failed\n");
                free(buffer);
                for (size_t i = 0; i < lineCount; i++)
                    free(lines[i]);
                free(lines);
                fclose(inputFile);
                if (outputName) fclose(outputFile);
                exit(1);
            }

            strcpy(lines[lineCount], buffer);
            lineCount++;
            len = 0;
        }
    }

    // Handle last line if file doesn’t end with newline
    if (len > 0) {
        buffer[len] = '\0';
        if (lineCount >= capacity) {
            capacity *= 2;
            char **newLines = realloc(lines, capacity * sizeof(char*));
            if (!newLines) {
                fprintf(stderr, "malloc failed\n");
                free(buffer);
                for (size_t i = 0; i < lineCount; i++)
                    free(lines[i]);
                free(lines);
                fclose(inputFile);
                if (outputName) fclose(outputFile);
                exit(1);
            }
            lines = newLines;
        }

        lines[lineCount] = malloc(len + 1);
        if (!lines[lineCount]) {
            fprintf(stderr, "malloc failed\n");
            free(buffer);
            for (size_t i = 0; i < lineCount; i++)
                free(lines[i]);
            free(lines);
            fclose(inputFile);
            if (outputName) fclose(outputFile);
            exit(1);
        }

        strcpy(lines[lineCount], buffer);
        lineCount++;
    }

    // Write lines in reverse order
    for (ssize_t i = lineCount - 1; i >= 0; i--) {
        fprintf(outputFile, "%s", lines[i]);
        free(lines[i]);
    }

    // Cleanup
    free(buffer);
    free(lines);
    fclose(inputFile);
    if (outputName) fclose(outputFile);

    return 0;
}
