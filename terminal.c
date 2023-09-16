#include "main.h"



/**
 * handle_terminal - handles the input from echo
 *
 * @a: struct conatins all var needed to pass
 *
 */

void handle_terminal(all_t *a)
{
	size_t len, size = 0;

	for (a->count = 1; a->count; a->count++, size = 0)
	{
		if (a->s)
			free(a->s);
		a->s = NULL;
		write(STDOUT_FILENO, "$ ", 2);
		len = getline(&a->s, &size, stdin);
		if (len == 0 || len == (size_t) EOF)
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
 * get_path - cheks if the comand is in path
 *
 * @PATH: path from env
 * @s: comand as string
 *
 * Return: the full path of comand or NULL
 */
char *get_path(char *PATH, char *s)
{
	char *path, *tmp, *token, *tmp1;
	struct stat st;
	int k = 0;

	if (stat(s, &st) == 0 && (s[0] == '.' || s[0] == '/'))
		return (s);

	if (!PATH)
	{
		free(s);
		return (NULL);
	}
	path = _strdup(PATH);
	tmp1 = str_concat("/", s);
	free(s);
	s = tmp1;
	while (path[k] && path[k] != '\n')
	{
		token = _strtok1(path, &k);
		if (token[len(token) - 2] == '/')
			tmp = str_concat(token, &s[1]);
		else
			tmp = str_concat(token, s);
		if (stat(tmp, &st) == 0)
		{
			free(path);
			free(s);
			free(token);
			return (tmp);
		}
		free(tmp);
		free(token);
	}
	free(path);
	free(s);
	return (NULL);
}

/**
 * free_all - free all slocated var
 * @a: pointer to all struct
 */
void free_all(all_t *a)
{
	if (a->args)
		free_arg(a->args);
	if (a->env)
		free_env(a->env);
	if (a->ali)
		free_arr(a->ali);
	if (a->envs)
		free(a->envs);
	if (a->s)
		free(a->s);
	if (a->com)
		free(a->com);
	if (a->fd)
		close(a->fd);
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
