#include "shell.h"
/**
 * _strtok -splits string into pieces
 * @string: string to be split
 * Return: pointer to pieces
 */

char **_strtok(char *string)
{
	int count = 0;
	int capacity = MAX_CAPACITY;
	char **tokens;
	char *delim = DELIMITER;
	char *token;

	tokens = malloc(capacity * sizeof(char *));
	if (tokens == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	token = strtok(string, delim);
	while (token != NULL)
	{
		tokens[count] = token;
		count++;
		token = strtok(NULL, delim);
	}
	tokens[count] = NULL;
	return (tokens);
}
