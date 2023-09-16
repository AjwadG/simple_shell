#include "main.h"


/**
 * var - switches the args to var if any
 * @arg: list of args
 * @env: head of env list
 * @ali: alias array
 * @n: the number of comands till now
 */
void var(char **arg, node *env, char **ali, int n)
{
	int i, j;
	char *tmp, *s;

	if (!arg[0])
		return;
	tmp = ali_val(ali, arg[0]);
	if (tmp)
	{
		tmp = _strdup(tmp);
		free(arg[0]);
		arg[0] = tmp;
	}
	else if (arg[0][0] == '$')
	{
		if (handle_env_rep(&arg[0], env, 0) <= 0)
		{
			free(arg[0]);
			arg[0] = arg[1], arg[1] = NULL;
		}
	}
	for (i = 1; arg[i]; i++)
	{
		for (j = 0; arg[i][j]; j++)
		{
			s = &arg[i][j];
			if (*s == '$' && s[1] && s[1] != '\n' && s[1] != ' ')
			{
				if (arg[i][j + 1] == '$')
					j += handle_pid_rep(&arg[i], j);
				else if (arg[i][j + 1] == '?')
					j += handle_exit_rep(&arg[i], n, j);
				else
					j += handle_env_rep(&arg[i], env, j);
			}
		}
	}
}

/**
 * handle_pid_rep - replaces var with pid value
 * @arg: pointer to argument
 * @index: index of $
 * Return: the number of replaced chars
 */
int handle_pid_rep(char **arg, int index)
{
	int i, count;
	char *s = *arg, *num, *tmp;
	pid_t pid = getpid();

	num = malloc(pid / 10 + 2);
	tmp = malloc(len(s) + pid / 10);
	nto_string(pid, num);

	for (i = 0; i < index; i++)
	{
		tmp[i] = s[i];
	}
	for (count = 0; num[count]; count++)
	{
		tmp[i + count] = num[count];
	}
	index += 2;
	for (i = i + count; s[index]; i++, index++)
	{
		tmp[i] = s[index];
	}
	tmp[i] = '\0';
	*arg = tmp;
	free(num);
	free(s);

	return (count - 2);
}



/**
 * handle_exit_rep - replaces var with exit value
 * @arg: pointer to argument
 * @n: last exit value
 * @index: index of $
 * Return: the number of replaced chars
 */
int handle_exit_rep(char **arg, int n, int index)
{
	int i, count;
	char *s = *arg, *num, *tmp;

	num = malloc(n / 10 + 2);
	tmp = malloc(len(s) + n / 10);
	nto_string(n, num);

	for (i = 0; i < index; i++)
	{
		tmp[i] = s[i];
	}
	for (count = 0; num[count]; count++)
	{
		tmp[i + count] = num[count];
	}
	index += 2;
	for (i = i + count; s[index]; i++, index++)
	{
		tmp[i] = s[index];
	}
	tmp[i] = '\0';
	*arg = tmp;
	free(num);
	free(s);

	return (count - 2);
}



/**
 * handle_env_rep - replaces var with env val
 * @arg: pointer to argument
 * @env: env list header
 * @index: index of $
 * Return: the number of replaced chars
 */
int handle_env_rep(char **arg, node *env, int index)
{
	int i, count, l;
	char *s = *arg, *var, *tmp, *tmp1;

	for (i = index + 1; s[i] && s[i] != '\n' && s[i] != '$'; i++)
		;
	l = i - index;
	tmp1 = malloc(l + 1);
	for (i = index + 1; s[i] && s[i] != '\n' && s[i] != '$'; i++)
		tmp1[i - index - 1] = s[i];
	tmp1[l - 1] = '\0';
	var = env_val(env, tmp1);
	free(tmp1);
	if (!var)
		var = "";
	var = _strdup(var);
	tmp = malloc(len(s) + len(var));
	for (i = 0; i < index; i++)
	{
		tmp[i] = s[i];
	}
	for (count = 0; var[count]; count++)
	{
		tmp[i + count] = var[count];
	}
	index += l;
	for (i = i + count; s[index]; i++, index++)
	{
		tmp[i] = s[index];
	}
	tmp[i] = '\0';
	*arg = tmp;
	free(var);
	free(s);

	return (count - 1);
}
