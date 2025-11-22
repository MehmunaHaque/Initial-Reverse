text
# File Reverse Program

## Overview

This program reads a text file line by line and writes the lines in reverse order to an output file. It is written in C and demonstrates dynamic memory management, robust error handling, and efficient use of standard file I/O operations. The application is helpful for tasks like reversing log file entries or learning core systems programming concepts in C.

## Features

- Reads lines from a file (or standard input)
- Stores all lines in dynamic memory
- Writes lines to a file (or standard output) in reverse order
- Handles arbitrary line lengths and file sizes using dynamic arrays and buffers
- Comprehensive error checking for file I/O and memory allocation
- Input and output file names must differ to prevent accidental data loss

## Compilation

To compile the program, use a C compiler such as gcc:

gcc -o reverse Initial_Reverse.c

text

## Usage

Basic usage from the command line:

./reverse input.txt output.txt

text

- `input.txt`: The source text file whose lines will be reversed.
- `output.txt`: The destination file where reversed lines are written.
- If only the input file is specified, the output will be written to the terminal (stdout).
- If no files are specified, the program reads from standard input and writes to standard output.

### Examples

Reverse a file and write to another file:

./reverse input.txt output.txt

text

Reverse a file and display output on the terminal:

./reverse input.txt

text

Reverse lines interactively (Ctrl-D to end input):

./reverse

text

## Error Handling

- If the input and output file names are the same, the program prints an error and exits.
- If a file cannot be opened or a memory allocation fails, a meaningful error message is printed to stderr and the program exits gracefully.
- If invalid arguments are provided, usage instructions are printed.

## Memory Management

- Lines are collected into a dynamically resizable array using `malloc` and `realloc`.
- Each line is read into a dynamically allocated buffer, also resized as needed.
- After use, all memory allocations are properly freed to avoid memory leaks.
- The program is robust for both very long files and lines of arbitrary length due to this dynamic allocation strategy.

## License

This code is inspired by the OSTEP projects and is intended for educational use.
