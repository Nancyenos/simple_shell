#include "shell.h"

/**
 * getfunc - a function which selects a function based on the commands
 * @str: a command string pointer
 *
 * Return: returns 1 in success and -1 if it fails.
 */

int (*getfunc(char *str))(char **line)
{
int i = 0;
selecte selector[] = {
{"ls", list},
{"l", list},
{"ll", list},
{"exit", exiter},
{"echo", echorr},
{"cd", changedir},
{"cat", concat},
{"pwd", pwds},
{"env", envir},
{"printenv", envir},
{"/bin/printenv", envir},
{"/bin/env", envir},
{"mkdir", maker},
{NULL, NULL}};

while (!strcomp(selector[i].command, str) && (selector[i].command != NULL))
{
i++;
}

if (selector[i].command == NULL)
{
return (NULL);
}

return (selector[i].funcptr);
}

/**
 * shellprocessor - a function which excutes the given commands
 * @line: a pointer to an array of strings
 * @argv: a pointer to the array of arguments
 *
 * Return: returns 1 in success and -1 if it fails
 */

int shellprocessor(char **line, char **argv)
{
int check;
int i = 0;

if (!line)
{
return (1); }
if (getfunc(line[0]) == NULL)
{
i = builtincom(line);
if (i != 0)
{
for (i = 0; line[0][i] != '\0'; i++)
{
if (line[0][i] == '/')
{
check = 1;
break; }}
if (check == 1)
{
write(1, argv[0], strleng(argv[0]));
write(1, ": ", 3);
write(1, line[0], strleng(line[0]));
write(1, ": No such file or directory\n", 28);
exit(EXIT_FAILURE); }
else
{
write(1, line[0], strleng(line[0]));
write(1, ": command not found\n", strleng(": command not found\n"));
exit(EXIT_FAILURE); }}
}
else
{
getfunc(line[0])(line); }
return (1);
}

/**
 * strcomp - a function to compare two strings
 * @str: the first string to compare
 * @equ: the secodn string to comapre too
 *
 * Return: returns an integer indicater of the boolean
 */

int strcomp(char *str, char *equ)
{
int i = 0;
int result = 0;

if (str == NULL || equ == NULL)
{
return (0);
}
while (equ[i] != '\0' || str[i] != '\0')
{

if (str[i] == equ[i])
{
result = 1;
}
else
{
result = 0;
}
i++;
}

return (result);
}
