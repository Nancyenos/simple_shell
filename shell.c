#include "shell.h"
/**
 * main -runs our own  simpleshell program
 * @ac: argument count
 * @av: argument vector ,pointer to arry of arguments
 * @env: settings and environment
 * Return: 0 on success
 */

int main(int ac, char **env)
{
	char* args[] = {NULL, NULL};
	char *buf = NULL;
	size_t count;
	ssize_t read;
	int i;
	pid_t pid;

	while(1)
	{
		i = isatty(STDIN_FILENO);
		if (i == 1 || i == 0)
		{
			write(STDOUT_FILENO, "#CisFun$", 9);
		}
		read = getline(&buf, &count, stdin);
		if (read == -1)
		{
			perror("Error in Reading input");
			free(buf);
			exit(EXIT_FAILURE);
		}
		if (buf[read - 1] == '\n')
		buf[read -1] = '\0';
		if (ac < 1)
		{
			write(2, "Type command", 10);
		}
		args[0] = buf;
		pid = fork();
		if (pid == -1)
		{
			perror("Error in forking");
			exit(EXIT_FAILURE);
			return (1);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, env) == -1)
				perror("error in execve");
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	free (buf);
	return (0);
}
