#include "main.h"



/**
 * handle_terminal - handles the input from echo
 * @name: name of the file
 * @env: list of envs
 */

void handle_terminal(char *name, node **env)
{
	char *s = NULL, ***args = NULL, **ali = NULL, seq[10], **envs = NULL;
	pid_t pid;
	int status, len, size, i, count = 0;

	while (++count)
	{
		write(STDOUT_FILENO, "$ ", 2);
		len = _getline(&s, &size, STDIN_FILENO);
		if (len == 0)
		{
			free_arg(args);
			free_env(*env);
			free_arr(ali);
			free(envs);
			return;
		}
		if (len == EOF || isempty(s))
			continue;
		free_arg(args);
		args = _strtok(s, seq);
		for (i = 0; args[i]; i++)
		{
			if (args[i][0] == NULL)
				break;
			if (built_in(env, args[i], &ali, count))
				continue;
			args[i][0] = get_path(env_val(*env, "PATH"), args[i][0]);
			if (list_arr(*env, &envs) && args[i][0] == NULL)
			{
				print_err(name, count, args[i][0]);
				args[i][0] = malloc(1);
				continue;
			}
			pid = fork();
			if (pid == 0 && execve(args[i][0], args[i], envs) == -1)
			{
				perror(name);
				free_arg(args);
				free_env(*env);
				free_arr(ali);
				free(s);
				free(envs);
				exit(1);
			}
			wait(&status);
			if (!status && seq[i] == '|')
				break;
			else if (status && seq[i] == '&')
				break;
		}
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
	int i;
	struct stat st;

	if (stat(s, &st) == 0)
		return (s);

	path = _strdup(PATH);

	tmp1 = str_concat("/", s);
	free(s);
	s = tmp1;
	token = strtok(path, ":\n");
	while (token)
	{
		if (token[len(token) - 2] == '/')
			tmp = str_concat(token, &s[1]);
		else
			tmp = str_concat(token, s);
		if (stat(tmp, &st) == 0)
		{
			free(path);
			free(s);
			return (tmp);
		}
		token = strtok(NULL, ":\n");
		free(tmp);
	}
	free(path);
	free(s);
	return (NULL);
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
		write(STDOUT_FILENO, "VARIABLE contains =\n",
				len("VARIABLE contains =\n"));
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
