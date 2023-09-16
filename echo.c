#include "main.h"
/**
 * get_arg - get the args
 *
 * @s: sting
 * @dil: dilams
 * Return: pointer to pointer of strings
 */
char **get_arg(char *s, char *dil)
{
	char *token, **arg;
	int l = count_w(s), i;

	arg = malloc(sizeof(char *) * l);
	token = strtok(s, dil);
	for (i = 0; i < l; i++)
	{
		arg[i] = token;
		token = strtok(NULL, dil);
	}
	return (arg);
}
/**
 * handle_echo - handles the input from echo
 * @name: name of the file
 */

void handle_echo(char *name)
{
	char *s = malloc(1), **arg;
	pid_t pid;
	int status, len, size;

	while (1)
	{
		len = _getline(&s, &size, STDIN_FILENO);
		if (len == EOF || len == 0)
			return;
		else if (isempty(s))
			continue;
		arg = get_arg(s, " \n");
		if (_strcmp(arg[0], "exit") == 0)
			break;
		else if (_strcmp(arg[0], "env") == 0 && print_env())
			continue;
		arg[0] = get_path(s);
		if (arg[0] == NULL)
		{
			perror(s);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(arg[0], arg, environ) == -1)
			{
				perror(name);
				return;
			}
		}
		wait(&status);
		free(arg);
	}
}
