#include "main.h"


/**
 * handle_echo - handles the input from echo
 * @name: name of the file
 * @env: list of envs
 */
void handle_echo(char *name, node **env)
{
	char *s = malloc(1), ***args = NULL, **ali = NULL, seq[10], **envs = NULL;
	pid_t pid;
	int status = 0, i, count = 0;
	size_t len, size = 0;

	while (++count)
	{
		free(s);
		s = NULL;
		size = 0;
		len = getline(&s, &size, stdin);
		if (len == 0 || len == EOF)
		{
			free_arg(args);
			free_env(*env);
			free_arr(ali);
			free(envs);
			free(s);
			exit (status != 0 ? 2 : 0);
		}
		if ( isempty(s))
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
				exit(2);
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
		write(STDERR_FILENO, "unset wrong usage\n", 18);
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
