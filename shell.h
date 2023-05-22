#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

#define MAX_CAPACITY 10
#define DELIMITER " "

extern char **environ;
extern int errno;
typedef enum interactive
{false,
 true
} check;

/**
 * struct selectfunction - a struct array of functions
 * @command: a pointer to the caharacter of the command string
 * @funcptr: a pointer to a function
 */

typedef struct selectfunc
{
char *command;
int (*funcptr)(char **line);
} selecte;

int builtincom(char **line);
int strleng(char *s);
char _getchar(void);
int _getline(char **line, size_t *len);
int echoer(char *line[]);
int exitor(char *line[]);
int cater(char *line[]);
int lister(char **line);
int builtincom(char **line);
int changedire(char **line);
int pwder(char *line[]);
int envir(char *line[]);
int maker(char *line[]);
int strcomp(char *str, char *equ);
int echorr(char *line[]);
void _execute(char **args, char **env, char **command);
char** _strtok(char *string);
int (*getfunc(char *str))(char **line);
int proc(char **line, char **argv);

void sigintHandler(int sig_num __attribute__((unused)));
void printprompt(int i);


int getstr(char *str);
int shellprocessor(char **line, char **argv);
char **strbrk(char *line, char c);

void farewell(void);
void description(void);
void strcopy(char *src, char *dest);
int strcomp(char *str, char *equ);

#endif 
