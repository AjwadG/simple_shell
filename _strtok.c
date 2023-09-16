#include "main.h"

/**
 * _strtok - crates array of arrays
 * @s: string of the source
 * @seq: comands flow
 * Return: array of arrays of args
 */
char ***_strtok(char *s, char seq[10])
{
	int i, j, k = 0, *n;
	char ***args;

	n = arg_num(s, seq);
	args = malloc(sizeof(char **) * (n[0] + 1));
	args[n[0]] = NULL;

	for (i = 0; i < n[0]; i++)
	{
		args[i] = malloc(sizeof(char *) * (n[i + 1] + 1));
		args[i][n[i + 1]] = NULL;
		for (j = 0; j < n[i + 1]; j++)
		{
			args[i][j] = get_next_arg(s, &k);
		}
	}
	free(n);
	return (args);
}


/**
 * get_next_arg - get next string
 *
 * @s: source string
 * @k:starting index
 * Return: pointer to new memort of string
 */
char *get_next_arg(char *s, int *k)
{
	int i, j, h, l;
	char *str;

	for (i = *k; s[i] && s[i] != '\n'; i++)
	{
		if (s[i] == ' ' || s[i] == ';' || s[i] == '&' || s[i] == '|')
			continue;
		for (j = i; s[j]; j++)
		{
			if (s[j] == ' ' || s[j] == ';' || s[j] == '&')
				break;
			if (s[j] == '#' || s[j] == '|' || s[j] == '\n')
				break;
		}
		l = j - i;
		str = malloc(l + 1);
		for (h = 0; h < l; h++)
		{
			str[h] = s[i + h];
		}
		str[l] = '\0';
		*k = i + l;
		break;
	}
	return (str);

}

/**
 * arg_num - gets number of comands
 * @s: string
 * @seq: comand flow
 * Return: array of ints
 */
int *arg_num(char *s, char seq[10])
{
	int *n = malloc(sizeof(int) * 10), i = 0, start = 0;

	n[0] = 1;
	while (++i < 10)
		n[i] = 0;
	if (s[0] == ' ')
		start = 1;

	for (i = 0; s[i] && s[i] != '\n'; i++)
	{
		if (s[i] == ';' && s[i + 1] != ';' && s[i - 1] != ';')
		{
			seq[n[0] - 1] = ';';
			n[0]++;
		}
		else if (s[i] == '&' && s[i + 1] == '&' && s[i - 1] != '&')
		{
			seq[n[0] - 1] = '&';
			n[0]++;
		}
		else if (s[i] == '|' && s[i + 1] == '|' && s[i - 1] != '|')
		{
			seq[n[0] - 1] = '|';
			n[0]++;
		}
		else if (s[i] == '#')
			break;
		else if ((s[i] == '&' || s[i] == '|') && s[i + 1] == ' ')
			continue;
		else
		{
			if (start && s[i] != ' ')
				start = 0;
			if (start)
				continue;
			else if (s[i] != ' ' && (s[i + 1] == ' '
				|| s[i + 1] == '\n' || s[i + 1] == '\0'
				|| s[i + 1] == ';' || s[i + 1] == '&'
				|| s[i + 1] == '|'))
				n[n[0]]++;
		}
	}
	seq[n[0] - 1] = '\0';
	return (n);

}


/**
 * free_arg - frees array of arrays
 * @ar: pointer to array of arrays
 * Return: allways 1
 */
int free_arg(char ***ar)
{
	int i;

	if (!ar)
		return (1);

	for (i = 0; ar[i]; i++)
	{
		free_arr(ar[i]);
	}
	free(ar);
	return (1);
}
