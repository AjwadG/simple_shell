#include "main.h"


/**
 * _strtok - gets the tokens from string
 *
 * @str: pointer to string or NULL
 * @dilm: char to split the string on
 *
 * Return: pointer to the new token
 */
char *_strtok(char *str, char *dilm)
{
	static char *token;

	int last, next = 0, i, j, c_count = 0;

	if (str)
		token = str;
	if ((!token && !str) || !dilm)
		return (NULL);
	for (i = 0; token[i]; i++)
	{
		for (j = 0; dilm[j]; j++)
		{
			if (token[i] == dilm[j])
			{
				token[i] = '\0';
				c_count = 0;
			}
		}
	}
	last = next + c_count;
	next = last;
	return (NULL);
}
/**
 * count_w - counts the number of words
 *
 * @s: string
 *
 * Return: the number of words
 */
int count_w(char *s)
{
	int i, count = 0, start;

	start = s[0] == ' ' ? 1 : 0;

	for (i = 0; s[i] && s[i] != '\n'; i++)
	{
		if (start && s[i] != ' ')
		{
			count++;
			start = 0;
		}
		else if (s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\n'
			|| s[i + 1] == '\0'))
		{
			count++;
		}
	}

	return (count);
}

/**
 * _realloc -  reallocates ptr to the wanted new size
 * @ptr: first number
 * @old_size: the size of ptr
 * @new_size: the new wanted size
 *
 *
 * Return: a pointer to the array or Null if new_size = 0 and ptr != null
 * or failed to alocate memory or ptr if old = new size
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;
	unsigned int l = old_size < new_size ? old_size : new_size;

	if (old_size == new_size)
	{
		return (ptr);
	}
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
	{
		newptr = malloc(new_size);
		if (newptr)
			return (newptr);
		else
			return (NULL);
	}


	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	_memcpy(newptr, ptr, l);
	free(ptr);
	return (newptr);

}

/**
 * _memcpy - function
 *
 * @dest: a pointer to the destination string.
 * @src: a poniter to the source string.
 * @n: the number of bytes to copy as int.
 *
 * Description: copies n of memory area from src to dest;
 *
 * Return: a pointer to the memory area dest.
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * _getline - read from stream
 *
 * @s: pointer to string
 * @l: pointer to int to store the alocated memory
 * @stream: fd of reading source
 *
 * Return: Number of read chars or -1
 */
int _getline(char **s, int *l, int stream)
{
	int stat;
	char *tmp;

	if (*s)
		free(*s);
	*s = malloc(120);
	*l = 120;
	while (1)
	{
		stat = read(stream, &(*s)[*l - 120], 120);
		(*s)[stat + *l - 120] = '\0';
		if (stat == 120)
		{
			*l += 120;
			tmp = _realloc(*s, *l - 120, *l);
			free(*s);
			*s = tmp;
		}
		else if (stat == -1 || stat == 0)
		{
			free(*s);
			s = NULL;
			return (stat);
		}
		else
		{
			return (*l - 120 + stat);
		}
	}
}
