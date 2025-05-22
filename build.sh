#!/bin/bash

# Compile the shell program
cc -Wall -Werror -Wextra \
  ./src/commands.c \
  ./src/inputs.c \
  ./src/main.c \
  ./src/utils.c \
  ./src/lib/ft_strdup.c \
  ./src/lib/ft_strtok.c \
  -lreadline -o my_shell

# Print status
if [ $? -eq 0 ]; then
  echo "✅ Build successful: ./my_shell"
else
  echo "❌ Build failed"
fi

