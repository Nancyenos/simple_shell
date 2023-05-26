#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

extern char **environ;
extern int errno;

/**
 * struct selectfunction - a struct arr of functions
 * @command: a pointer to the caharacter of the command string
 * @funcptr: a pointer to a function
 */

typedef struct selectfunction
{
char *command;
int (*funcptr)(char **line);
} selecte;

void intHandler(int sig_num __attribute__((unused)));
void prompt(int i);
int exiter(char *line[]);
int concat(char *line[]);
int getstr(char *str);
int shellprocessor(char **line, char **argv);
char **strbrk(char *line, char c);
int __getline(char **line, size_t *lent);
void farewell(void);
int strleng(char *s);
void strcopy(char *src, char *dest);
int strcomp(char *str, char *equ);
void strmix(char *src, char *dest);
int list(char **line);
int (*getfunc(char *str))(char **line);
int echorr(char *line[]);
int builtincom(char **line);
int changedir(char **line);
int pwds(char *line[]);
int envir(char *line[]);
int maker(char *line[]);
char __getchar(void);
char *stringer(char *line, int i, char *str, char c);

#endif
