#include "main.h"


/**
 * handle_echo - handles the input from echo
 *
 * @a: struct conatins all var needed to pass
 */
void handle_echo(all_t *a)
{
	size_t len, size = 0;

	for (a->count = 1; a->count; a->count++)
	{
		if (a->s)
			free(a->s);
		a->s = NULL;
		size = 0;
		len = getline(&a->s, &size, stdin);
		if (len == 0 || len == (size_t) EOF)
		{
			free_all(a);
			exit(a->status);
		}
		if (isempty(a->s))
			continue;
		if (a->args)
			free_arg(a->args);
		a->args = NULL;
		a->args = _strtok(a->s, a->seq);
		args_loop(a);
	}
}


/**
 * args_loop - just to make bettey good
 *
 * @a: pointer too all_t
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
			print_err(a->name, a->count, a->com);
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
