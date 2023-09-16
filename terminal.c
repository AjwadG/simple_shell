#include "main.h"


/**
 * handle_terminal - handles the input from echo
 * @name: name of the file
 */

void handle_terminal(char *name)
{
	size_t size;
	char *s = NULL, *token, *arg[2] = {NULL, NULL};
	pid_t pid;
	int status, len;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		len = getline(&s, &size, stdin);
		if (len == -1)
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
