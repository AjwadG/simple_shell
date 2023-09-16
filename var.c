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

	for (i = 1; arg[i]; i++)
	{
		for (j = 0; arg[i][j]; j++)
		{
			s = &arg[i][j];
			if (*s == '$' && s[1] && s[1] != '\n' && s[1] != ' ')
			{
				if (arg[i][j + 1] == '$')
				{
					j += handle_pid_rep(&arg[i], j);
				}
				if (arg[i][j + 1] == '?')
				{
					j += handle_exit_rep(&arg[i], n, j);
				}
				else
				{
					j += handle_env_rep(&arg[i], env, j);
				}
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
	int i, count = 0;
	char *s = *arg;

	return (count);
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
	int i, count = 0;
	char *s = *arg;

	return (count);
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
	int i, count = 0;
	char *s = *arg;

	return (count);
}
