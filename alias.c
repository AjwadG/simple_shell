#include "main.h"

/**
 * alias - sets or prints alias
 *
 * @env: env list header
 * @arg: directory to move to
 * @ali: list of allias
 *
 * Return: 1 on success 0 otehr wise
 */
int alias(node **env, char **arg, char ***ali)
{
	int i;
	char *alis;

	if (!arg[0] && *env)
	{
		if (!ali[0])
		{
			printf("NO ALIAS YET\n");
			return (1);
		}
		for (i = 0; ali[0][i]; i++)
		{
			print_alias(ali[0][i]);
		}
	}
	for (i = 0; arg[i]; i++)
	{
		if (is_env(arg[i]))
		{
			put_alias(arg[i], ali);
		}
		else
		{
			alis = get_alias(arg[i], ali[0]);
			if (!alis)
				return (1);
			print_alias(alis);
		}
	}
	return (1);
}


/**
 * ali_val - gets the ali of env
 * @ali: env list head
 * @name: name of the env
 * Return: pointer to the value
 */
char *ali_val(char **ali, char *name)
{
	int i, j;

	if (!ali)
		return (NULL);
	for (j = 0; name[j] != '=' && name[j]; j++)
		;
	if (!name[j])
	{
		for (i = 0; ali[i]; i++)
		{
			if (envcmp(ali[i], name))
			{
				for (j = 0; ali[i][j] != '='; j++)
					;
				return (&ali[i][j + 1]);
			}
		}
		return (NULL);
	}
	for (i = 0; ali[i]; i++)
	{
		if (envcmp(ali[i], &name[j + 1]))
		{
			return (&name[j + 1]);
		}
	}
	return (NULL);
}


/**
 * put_alias - adds a new ali
 * @new_ali: ali to add
 * @ali: array fo alias
 * Return: allways 1
 */
int put_alias(char *new_ali, char ***ali)
{
	int i, k, l = sizeof(char *);
	char *tmp, *s;

	if (!(*ali))
	{
		*ali = malloc(l * 2);
		ali[0][0] = _strdup(new_ali);
		ali[0][1] = NULL;
	}
	else
	{
		for (i = 0; ali[0][i]; i++)
		{
			if (envcmp(ali[0][i], new_ali))
			{
				free(ali[0][i]);
				ali[0][i] = _strdup(new_ali);
				return (1);
			}
		}
		ali[0] = _realloc(ali[0], l * (i + 1), l * (i + 2));
		ali[0][i] = _strdup(new_ali);
		ali[0][i + 1] = NULL;
		tmp = ali_val(*ali, new_ali);
		if (tmp == NULL)
			return (1);
		for (k = 0; ali[0][k]; k++)
		{
			if (i != k && envcmp(ali[0][k], tmp))
			{
				for (l = 0; ali[0][k][l] != '='; l++)
					;
				tmp = &ali[0][k][l + 1];
				s = build_ali(ali[0][i], tmp);
				free(ali[0][i]);
				ali[0][i] = s;
			}
		}
	}
	return (1);
}


/**
 * get_alias - get the alias
 * @name: name of alias
 * @ali: array fo alias
 * Return: pointer to ali or NULL
 */
char *get_alias(char *name, char **ali)
{
	int i = 0;

	if (!ali)
		return (NULL);
	while (ali[i])
	{
		if (envcmp(ali[i], name))
			return (ali[i]);
		i++;
	}
	return (NULL);
}


/**
 * free_arr - frees array
 * @ar: pointer to array
 * Return: allways 1
 */
int free_arr(char **ar)
{
	int i;

	if (!ar)
		return (1);
	for (i = 0; ar[i]; i++)
	{
		free(ar[i]);
	}
	free(ar);
	return (1);
}
