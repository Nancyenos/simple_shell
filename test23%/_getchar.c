#include "shell.h"

/**
 * __getchar - this is a function that reads a
 *		character from the standard input
 * Return: returns the read character
 */

char __getchar(void)
{
char *buff;
char c;
int i = 0;

buff = malloc(2);

if (!buff)
return (-1);

fflush(stdout);

i = read(1, buff, 1);
if (i == -1)
{
perror("Reading Char");
return (-1);
}
else if (i == 0)
{
write(1, "\n", 2);
fflush(stdout);
exit(1);
}

c = *buff;

return (c);
}

/**
 * __getline - a function to read a line from the standard input
 * @line: a pointer to a pointer of location to save the string
 * @lent: the size of the characters read
 *
 * Return: returns the size of the read string
 */

int __getline(char **line, size_t *lent)
{
size_t limit = 25;
char *tmp;

line[0] = malloc(25);
if (!line[0])
return (-1);
*lent = 0;

while (line[0][*lent - 1] != '\n')
{
line[0][*lent] = __getchar();
*lent += 1;

if (*lent > (limit - 3))
{
tmp = realloc(line[0], limit + 10);
if (tmp)
line[0] = tmp;
else
perror("Reallocation");
limit += 10;
}
}

return (*lent);
}

/**
 * echor - a function to echo any text input
 * @line: an array of command and arguments
 *
 * Return: returns 1 in success and -1 if it fails
 */

int echor(char *line[])
{
int i = 1;

if (line[i] == NULL)
{
write(1, "\n", 2);
return (1);
}

while (line[i] != NULL)
{
write(1, line[i], strleng(line[i]));
i++;
if (line[i] != NULL)
{
write(1, " ", 2);
}
}
write(1, "\n", 2);

return (1);
}
