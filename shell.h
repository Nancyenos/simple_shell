#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_CAPACITY 10
#define DELIMITER " "

extern char** environ;
typedef enum interactive
{false,
 true
} check;
void _execute(char **args, char **env, char **command);
char** _strtok(char *string);
#endif 
