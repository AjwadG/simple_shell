#include "main.h"


/**
 * isempty - cheks if string is empty
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
