#!/bin/bash

# Compile the main.c file with the specified flags
gcc -o main src/main.c -Wall -Werror -Wextra -pedantic -g

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled program
    ./main
else
    echo "Compilation failed."
fi
