#include "shell.h"
/**
 * main -runs our own  simpleshell program
 * @ac: argument count
 * @av: argument vector ,pointer to arry of arguments
 * @env: settings and environment
 * Return: 0 on success
 */

int main(int ac, char** av, char **env)
{
	char** args = malloc(MAX_CAPACITY * sizeof(char*));
	char *buf = NULL;
	size_t count;
	ssize_t read;
	check file = false;

	while(1 && !file)
	{
		if (isatty(STDIN_FILENO == 0))
				file = true;
		{
			write(STDOUT_FILENO, "#CisFun$ ", 10);
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
		args = _strtok(buf);
		_execute(args, env, av);
		free(args);
	}
	free (buf);
        return (0);
}
/**
 * _execute -executes binary files commands
 * @args: pointer to command string
 * @env: pointer to envronment string
 * Return: void
 */
void _execute(char **args, char **env, char **command)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error in forking");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
			perror(*command);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
