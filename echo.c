#include "main.h"


/**
 * handle_echo - handles the input from echo
 * @name: name of the file
 * @env: list of envs
 */
void handle_echo(char *name, node **env)
{
	char *s = NULL, **arg = NULL, ***args = NULL, **ali = NULL, seq[10];
	pid_t pid;
	int status, len, size, i;

	while (1)
	{
		len = _getline(&s, &size, STDIN_FILENO);
		printf("%s \n", s);
		if (len == 0)
		{
			free_arg(args);
			free_env(*env);
			free_arr(ali);
			return;
		}
		if (len == EOF)
			continue;
		else if (isempty(s))
			continue;
		free_arg(args);
		args = _strtok(s, seq);
		for (i = 0; args[i]; i++)
		{
			arg = args[i];
			if (arg[0] == NULL)
				break;
			if (built_in(env, arg, &ali))
				continue;
			arg[0] = get_path(arg[0]);
			if (arg[0] == NULL)
			{
				perror(arg[0]);
				arg[0] = malloc(1);
				continue;
			}
			pid = fork();
			if (pid == 0 && execve(arg[0], arg, environ) == -1)
			{
				perror(name);
				free_arg(args);
				free_env(*env);
				free_arr(ali);
				free(s);
				return;
			}
			wait(&status);
		}
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
		sum = sum * 10 + code[i] - '0';
	}
	exit(sum % 256);
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
		write(STDOUT_FILENO, "unset wrong usage\n", 18);
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
