#include "main.h"


/**
 * build_ali - builds ali
 * @ali: ali full value
 * @ali: only the val after =
 * Return: pointer to the value
 */
char *build_ali(char *ali, char *val)
{
	int i;
	char *str;

	for (i = 0; ali[i] != '='; i++)
	{
	}
	ali[i + 1] = '\0';

	str = str_concat(ali, val);

	return (str);
}

/**
 * print_alias - prints lias format
 * @ali: string alias
 */
void print_alias(char *ali)
{
	int i;
	char *tmp = malloc(len(ali) + 2);
	for (i = 0; ali[i] != '='; i++)
	{
		tmp[i] = ali[i];
	}
	tmp[i++] = '=';
	tmp[i] = '\'';
	while (ali[i])
	{
		tmp[i + 1] = ali[i];
		i++;
	}
	tmp[++i] = '\'';
	tmp[++i] = '\n';
	write(STDOUT_FILENO, tmp, i + 1);
	free(tmp);
}
