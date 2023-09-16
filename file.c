#include "main.h"



/**
 * handle_file - handles the input from file arg[1]
 * @av: list of args
 * @env: list of envs
 */

void handle_file(char **av, node **env)
{
	char *s = malloc(1), **arg, **ali = NULL;
	pid_t pid;
	int status, len, size, fd = open(av[1], O_RDONLY);

	if (fd == -1)
	{
		perror(av[1]);
		exit(-1);
	}

	while (1)
	{
		len = _getline(&s, &size, fd);
		if (len == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			return;
		}
		if (len == EOF)
			return;
		else if (isempty(s))
			continue;
		arg = get_arg(s, " \n");
		if (_strcmp(arg[0], "exit") == 0)
		{
			exit_with(arg[1]);
			continue;
		}
		else if (_strcmp(arg[0], "env") == 0 && print_env(*env))
			continue;
		else if (_strcmp(arg[0], "cd") == 0 && cd(env, arg[1]))
			continue;
		else if (_strcmp(arg[0], "alias") == 0 && alias(env, &arg[1], &ali))
			continue;
		else if (_strcmp(arg[0], "setenv") == 0)
		{
			if (arg[1] && arg[2])
				_setenv(env, arg[1], arg[2]);
			else
				write(STDOUT_FILENO, "wrong usage\n", 12);
			continue;
		}
		else if (_strcmp(arg[0], "unsetenv") == 0 && _unsetenv(arg[1], env))
			continue;
		arg[0] = get_path(env_val(*env, "PATH"), arg[0]);
		if (arg[0] == NULL)
		{
			perror(s);
			continue;
		}
		pid = fork();
		if (pid == 0 && execve(arg[0], arg, environ) == -1)
		{
			perror(av[0]);
			return;
		}
		wait(&status);
	}
}

/**
 * built_in - ex built in fun
 *
 * @env: env linked list
 * @arg: comands and thir args
 * @ali: alias list
 * @n: last exit value
 *
 * Return: 1 if built in 0 otehr wise
 */
int built_in(node **env, char **arg, char ***ali, int n)
{
	var(arg, *env, *ali, n);
	if (_strcmp(arg[0], "exit") == 0)
	{
		exit_with(arg[1]);
		return (1);
	}
	if (_strcmp(arg[0], "env") == 0 && print_env(*env))
		return (1);
	if (_strcmp(arg[0], "cd") == 0 && cd(env, arg[1]))
		return (1);
	if (_strcmp(arg[0], "alias") == 0 && alias(env, &arg[1], ali))
		return (1);
	if (_strcmp(arg[0], "setenv") == 0)
	{
		if (arg[1] && arg[2])
			_setenv(env, arg[1], arg[2]);
		else
			write(STDOUT_FILENO, "wrong usage\n", 12);
		return (1);
	}
	else if (_strcmp(arg[0], "unsetenv") == 0 && _unsetenv(arg[1], env))
		return (1);

	return (0);
}

/**
 * print_err - prints the error
 *
 * @name: name of the file
 * @n: exe count
 * @com: name of the comand
 */
void print_err(char *name, int n, char *com)
{
	char *s, *tmp1 = malloc(n / 10 + 3), *tmp2;


	if (!com)
		com = _strdup("water");
	s = str_concat(name, ": ");
	nto_string(n, tmp1);
	tmp2 = str_concat(s, tmp1);
	free(tmp1);
	free(s);
	tmp1 = str_concat(tmp2, ": ");
	free(tmp2);
	s = str_concat(tmp1, com);
	free(tmp1);

	if (len(com) > 255)
		tmp1 = str_concat(s, ": File name too long\n");
	else
		tmp1 = str_concat(s, ": not found\n");

	write(STDERR_FILENO, tmp1, len(tmp1));
	free(tmp1);
	free(s);
	free(com);
}


/**
 * nto_string - converts n to string
 *
 * @n: number to convert
 * @s: string to store in
 */
void nto_string(int n, char *s)
{
	int i, l = 1;
	if (n < 10)
	{
		s[0] = n + '0';
		s[1] = '\0';
	}
	else
	{
		for (i = 0; n / l >= 10; i++)
		{
			l *= 10;
		}
		s[0] = n / l  + '0';
		if (n / 100 != 0 && n % 100 < 10)
		{
			s[1] = '0';
			nto_string(n % l, &s[2]);
		}
		else
		{
			nto_string(n % l, &s[1]);
		}
	}
}
