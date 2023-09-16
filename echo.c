#include "main.h"


/**
 * handle_echo - handles the input from echo
 * @name: name of the file
 */

void handle_echo(char *name)
{
	size_t size;
	char *s = NULL, *token, *arg[2] = {NULL, NULL};
	pid_t pid;
	int status, len;

	while (1)
	{
		len = getline(&s, &size, stdin);
		if (len == EOF)
			return;
		else if (isempty(s))
			continue;
		token = strtok(s, " \n");
		arg[0] = token;
		while (token)
		{
			token = strtok(NULL, " \n");
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
	}
}
