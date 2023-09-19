#include "main.h"


/**
 * isempty - checks if string is empty
 *
 * @s: string
 *
 * Return: 1 if empty 0 if not
 */

int isempty(char *s)
{
	int i;

	for (i = 0; s[i] && s[i] != '\n'; i++)
	{
		if (s[i] != ' ')
			return (0);
	}
	return (1);
}


/**
 * str_concat -  Concatenates two strings
 * @s1: a pointer to a string
 * @s2: a pointer to a string
 *
 * Description: allocate space in memory, which
 * contains a copy of the string str.
 *
 * Return: a pointer to new string or Null if str = NULL
 * or failed to allocate memory
 */

char *str_concat(char *s1, char *s2)
{
	int i, l1 = len(s1), l2 = len(s2), l = l1 + l2 - 1;
	char *new = malloc(sizeof(char) * (l));

	if (!new)
		return (NULL);

	for (i = 0; i < l; i++)
	{
		if (i < l1 - 1 && l1 != 1)
			new[i] = s1[i];
		else if (i < l - 1)
			new[i] = s2[i - l1 + 1];
		else
			new[i] = '\0';
	}

	return (new);
}


/**
 * _strcmp - fucntion
 * @s1: a pointer to the first string
 * @s2: a pointer to the second string
 *
 * Description: compares two strings s1 and s2
 *
 * Return: 0 if they are the same more or less on the defraces
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (1)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			break;
		else if (s1[i] == '\0')
			return (1);
		else if (s2[i] == '\0')
			return (1);
		else if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}



/**
 * _strdup -  creates a copy
 * @str: a pointer to a string
 *
 * Description: allocate space in memory, which
 * contains a copy of the string str.
 *
 * Return: a pointer to new string or Null if str = NULL
 * or failed to allocate memory
 */

char *_strdup(char *str)
{
	int l = len(str);
	char *new = malloc(sizeof(char) * l);

	if (!l || new == NULL)
		return (NULL);

	while (l--)
	{
		new[l] = str[l];
	}

	return (new);
}



/**
 * len - calculates the length of s
 * @s: apointer to string
 *
 * Return: the string of s or 0 if s = NULL
 */
int len(char *s)
{
	if (!s)
		return (0);
	if (s[0])
		return (1 + len(&s[1]));
	else
		return (1);
}
