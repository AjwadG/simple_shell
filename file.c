#include "main.h"



/**
 * handle_file - handles the input from file arg[1]
 *
 * @a: struct conatins all var needed to pass
 */

void handle_file(all_t *a)
{
	size_t len, size = 0;

	for (a->count = 1; a->count; a->count++)
	{
		if (a->s)
			free(a->s);
		a->s = NULL;
		size = 0;
		len = getline(&a->s, &size, stdin);
		if (len <= 0)
		{
			free_all(a);
			exit(a->status);
		}
		if (isempty(a->s))
			continue;
		free_arg(a->args);
		a->args = _strtok(a->s, a->seq);
		args_loop(a);
	}
}

/**
 * built_in - ex built in fun
 *
 * @arg: comands and thir args
 * @a: pointer to all struct
 *
 * Return: 1 if built in 0 otehr wise
 */
int built_in(char **arg, all_t *a)
{
	var(arg, a->env, a->ali, a->status);
	if (!arg[0])
		return (1);
	if (_strcmp(arg[0], "exit") == 0)
	{
		exit_with(arg[1], a);
		return (1);
	}
	if (_strcmp(arg[0], "env") == 0 && print_env(a->env))
		return (1);
	if (_strcmp(arg[0], "cd") == 0 && cd(arg[1], a))
		return (1);
	if (_strcmp(arg[0], "alias") == 0 && alias(&a->env, &arg[1], &a->ali))
		return (1);
	if (_strcmp(arg[0], "setenv") == 0)
	{
		if (arg[1] && arg[2])
			_setenv(&a->env, arg[1], arg[2]);
		return (1);
	}
	else if (_strcmp(arg[0], "unsetenv") == 0 && _unsetenv(arg[1], &a->env))
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

	write(STDERR_FILENO, tmp1, len(tmp1) - 1);
	free(tmp1);
	free(s);
}


/**
 * nto_string - converts n to string
 *
 * @n: number to convert
 * @s: string to store in
 */
void nto_string(int n, char *s)
{
	int i, tmp = n, l = 0;

	while (tmp / 10 != 0)
	{
		tmp /= 10;
		l++;
	}

	s[l + 1] = '\0';

	for (i = l ; i >= 0; i--)
	{
		s[i] = n % 10 + '0';
		n /= 10;
	}
}
