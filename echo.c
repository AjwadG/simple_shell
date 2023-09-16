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
	int l = count_w(s) + 1, i;

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
	char *s = NULL, **arg;
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
		{
			exit_with(arg[1]);
			continue;
		}
		else if (_strcmp(arg[0], "env") == 0 && print_env())
			continue;
		else if (_strcmp(arg[0], "setenv") == 0 && _setenv(arg[1], arg[2]))
			continue;
		else if (_strcmp(arg[0], "unsetenv") == 0 && _unsetenv(arg[1]))
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

/**
 * exit_with - exits with code
 *
 * @code: exit value (NULL = 0)
 *
 */
void exit_with(char *code)
{
	int sum = 0, i;
	char s[1024], *exi = "exit: Illegal number: ";

	if (code == NULL)
		exit(0);

	for (i = 0; code[i]; i++)
	{
		if (code[i] < '0' || code[i] > '9')
		{
			_memcpy(s, exi, len(exi) - 1);
			_memcpy(&s[len(exi) - 1], code, len(code) - 1);
			_memcpy(&s[len(exi) + len(code) - 2], "\n", 2);

			write(STDERR_FILENO, s, len(s));
			return;
		}
		sum = sum * 10 + code[0] - '0';
	}
	exit(sum);
}

/**
 */
int _unsetenv(char *env_name)
{
	return (1);
}
