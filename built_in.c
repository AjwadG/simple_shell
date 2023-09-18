#include "main.h"


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
 * exit_with - exits with code
 *
 * @code: exit value (NULL = 0)
 * @a: pointer to all struct
 * Return: exit val or -1
 *
 */
int exit_with(char *code, all_t *a)
{
	int sum = 0, i, l;
	char s[1024], *exi = "exit: Illegal number: ", *num;

	if (code == NULL)
	{
		free_all(a);
		exit(a->status);
	}
	for (i = 0; code[i]; i++)
	{
		if (code[i] < '0' || code[i] > '9')
		{
			_memcpy(s, a->name, len(a->name) - 1);
			_memcpy(&s[len(a->name) - 1], ": ", 2);
			num = malloc(10);
			nto_string(a->count, num);
			_memcpy(&s[len(a->name) + 1], num, len(num) - 1);
			l = len(a->name) + 1 + len(num) + 2;
			_memcpy(&s[l - 3], ": ", 2);
			_memcpy(&s[l - 1], exi, len(exi) - 1);
			_memcpy(&s[l + len(exi) - 2], code, len(code) - 1);
			_memcpy(&s[l + len(exi) + len(code) - 3], "\n", 2);
			write(STDERR_FILENO, s, len(s) - 1);
			fflush(stderr);
			free(num);
			a->status = 2;
			return (-1);
		}
		sum = sum * 10 + code[i] - '0';
	}
	free_all(a);
	exit(sum % 256);
}


/**
 * _setenv - set a new env
 *
 * @env: pointer to ehad of struct
 * @name: name of env
 * @value: value of env
 *
 * Return: allways 1
 */
int _setenv(node **env, char *name, char *value)
{
	node *tmp = *env;
	char *s, *s1;

	if (!name || is_env(name) || !value)
	{
		return (0);
	}

	s = str_concat(name, "=");
	s1 = str_concat(s, value);
	free(s);
	while (tmp)
	{
		if (envcmp(tmp->env, name))
		{
			free(tmp->env);
			tmp->env = s1;
			return (1);
		}
		tmp = tmp->next;
	}
	add_node(env, s1);
	free(s1);
	return (1);
}

/**
 * _unsetenv - removes env
 *
 * @env_name: env name to remove
 * @env: head of env list
 *
 * Return: 1 on succes 0 other wise
 */
int _unsetenv(char *env_name, node **env)
{
	node *tmp = *env, *tmp1 = tmp;

	if (!env_name)
	{
		return (1);
	}

	if (envcmp(tmp->env, env_name))
	{
		*env = tmp->next;
		free(tmp->env);
		free(tmp);
		return (1);
	}

	while (tmp)
	{
		if (envcmp(tmp->env, env_name))
		{
			free(tmp->env);
			tmp1->next = tmp->next;
			free(tmp);
			return (1);
		}
		tmp1 = tmp;
		tmp = tmp->next;
	}
	return (1);
}
