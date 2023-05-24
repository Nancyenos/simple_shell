/**
* changedire - a function to change a directory
* @line: an array of commands and arguments
*
* Return: returns 0 in success and -1 if it fails
*/

int changedire(char **line)
{
if (line[1] == NULL)
{
chdir(getenv("HOME"));
}
else if (chdir(line[1]) == -1)
{
write(1, line[0], strleng(line[0]));
write(1, ": ", 3);
write(1, ": cd", strleng(": cd"));
write(1, ": can't cd to ", strleng(": can't cd to "));
write(1, line[1], strleng(line[1]));
write(1, "\n", 2);
return (-1);
}

free(line);
return (1);
}



