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
	int i = 0;
	char *alis;

	(void) env;
	if (!arg[0])
	{
		if (!ali[0])
		{
			printf("NO ALIAS YET\n");
			return (1);
		}
		while (ali[0][i])
		{
			write(STDOUT_FILENO, ali[0][i], len(ali[0][i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}

	for (i = 0; arg[i]; i++)
	{
		if (is_env(arg[i]))
		{
			put_alias(arg[i], ali);
			printf("alias : %s was addid\n", ali[0][i]);
			break;
		}
		else
		{
			alis = get_alias(arg[i], ali[0]);
			if (!alis)
			{
				printf("a.out: alias: %s: not found\n", arg[i]);
				return (1);
			}
			write(STDOUT_FILENO, alis, len(alis));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (1);
}

/**
 * put_alias - adds a new ali
 * @new_ali: ali to add
 * @ali: array fo alias
 * Return: allways 1
 */
int put_alias(char *new_ali, char ***ali)
{
	int i = 0;
	unsigned int l = sizeof(char *);
	char **tmp = NULL;

	if (!(*ali))
	{
		*ali = malloc(l * 2);
		ali[0][0] = _strdup(new_ali);
		ali[0][1] = NULL;
	}
	else
	{
		while (ali[0][i])
		{
			if (envcmp(ali[0][i], new_ali))
			{
				free(ali[0][i]);
				ali[0][i] = _strdup(new_ali);
				return (1);
			}
			i++;
		}
		tmp = _realloc(ali[0], l * (i + 1), l * (i + 2));
		ali[0] = tmp;
		ali[0][i++] = _strdup(new_ali);
		ali[0][i] = NULL;
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
	}
	return (NULL);
}


/**
 * free_alias - free alias list
 * @ali: array fo alias
 * Return: always 1
 */
int free_alias(char **ali)
{
	int i = 0;

	if (!ali)
		return (1);
	while (ali[i])
	{
		free(ali[i]);
		i++;
	}
	free(ali);
	return (1);
}
