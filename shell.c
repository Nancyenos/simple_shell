#include "shell.h"

int fork_exec(char **args, char **front);
int main(int argc, char *argv[]);

/**
 * sig_handlr - It Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handlr(int sig)
{
	char *nw_prompt = "#cisfun$ \n";

	(void)sig;
	signal(SIGINT, sig_handlr);
	write(STDIN_FILENO, nw_prompt, 3);
}

/**
 * fork_exec - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int fork_exec(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_location(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(args, 126));
		else
			ret = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *last_exe = &retn;
	char *prompt = "#cisfun$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handlr);

	*last_exe = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], last_exe);
		free_env();
		free_alias_list(aliases);
		return (*last_exe);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(last_exe);
		free_env();
		free_alias_list(aliases);
		return (*last_exe);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 9);
		ret = handle_args(last_exe);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*last_exe);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*last_exe);
}
