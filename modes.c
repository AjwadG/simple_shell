#include "main.h"


/**
 * interactive_mode - handles the input from terminal
 *
 * @a: struct conatins all var needed to pass
 *
 */

void interactive_mode(all_t *a)
{
	int len, size = 0;

	for (a->count = 1; a->count; a->count++, size = 0)
	{
		if (a->s)
			free(a->s);
		a->s = NULL;
		write(STDOUT_FILENO, "$ ", 2);
		len = _getline(&a->s, &size, a->fd);
		if (len == 0 || len == EOF)
		{
			if (len == 0)
				write(a->fd, "\n", 1);
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
 * non_interactive_mode - handles files and echo, cat
 *
 * @a: struct conatins all var needed to pass
 */
void non_interactive_mode(all_t *a)
{
	int len, size = 0, i;

	for (a->count = 1; a->count; a->count++)
	{
		if (a->input)
			free(a->input);
		a->input = NULL;
		size = 0;
		len = _getline(&a->input, &size, a->fd);
		if (len == 0 || len == EOF)
		{
			free_all(a);
			exit(a->status);
		}
		if (isempty(a->input))
			continue;
		i = 0;
		while (a->input[i])
		{
			if (a->s)
				free(a->s);
			a->s = _strtok1(a->input, &i, '\n');
			if (a->args)
				free_arg(a->args);
			a->args = NULL;
			a->args = _strtok(a->s, a->seq);
			args_loop(a);
		}
	}
}


/**
 * args_loop - just to make betty good
 *
 * @a: pointer to all_t
 */
void args_loop(all_t *a)
{
	pid_t pid;
	int i;
	char *path;

	for (i = 0; a->args[i]; i++)
	{
		if (a->args[i][0] == NULL)
			break;
		if (built_in(a->args[i], a))
			continue;
		path = env_val(a->env, "PATH");
		if (a->com)
			free(a->com);
		a->com = _strdup(a->args[i][0]);
		a->args[i][0] = get_path(path, a->args[i][0]);
		if (list_arr(a->env, &a->envs) && a->args[i][0] == NULL)
		{
			comand_err(a->name, a->count, a->com);
			a->args[i][0] = malloc(1), a->status = 127;
			continue;
		}
		pid = fork();
		if (pid == 0 && execve(a->args[i][0], a->args[i], a->envs) == -1)
		{
			free_all(a);
			exit(2);
		}
		wait(&a->status);
		a->status = a->status == 0 ? 0 : 2;
		if (!a->status && a->seq[i] == '|')
			break;
		if (a->status && a->seq[i] == '&')
			break;
	}

}



/**
 * get_path - checks if the command is in path
 *
 * @PATH: path from env
 * @s: command as string
 *
 * Return: the full path of command or NULL
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
		token = _strtok1(path, &k, ':');
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
 * _getline - read from stream
 *
 * @s: pointer to string
 * @l: pointer to int to store the allocated memory
 * @stream: fd of reading source
 *
 * Return: Number of read chars or -1
 */
int _getline(char **s, int *l, int stream)
{
	static int size = 120;
	int stat;

	*s = malloc(size);
	*l = size;
	while (1)
	{
		stat = read(stream, &(*s)[*l - size], size);
		if (stat == size)
		{
			*l += size;
			*s = _realloc(*s, *l - size, *l);
		}
		else if (stat == -1 || stat == 0)
		{
			return (stat);
		}
		else
		{
			(*s)[stat + *l - size - 1] = '\0';
			return (*l - size + stat);
		}
	}
}
