#include "main.h"

/**
 * nto_string - converts n to string
 *
 * @n: number to convert
 * @s: string to store in
 */
void nto_string(int n, char *s)
{
	int i, tmp = n, l = 0;

	while (tmp / 10 != 0)
	{
		tmp /= 10;
		l++;
	}

	s[l + 1] = '\0';

	for (i = l ; i >= 0; i--)
	{
		s[i] = n % 10 + '0';
		n /= 10;
	}
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
		{
			free(ptr);
			return (newptr);
		}
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
 * free_all - free all slocated var
 * @a: pointer to all struct
 */
void free_all(all_t *a)
{
	if (a->args)
		free_arg(a->args);
	if (a->env)
		free_env(a->env);
	if (a->ali)
		free_arr(a->ali);
	if (a->envs)
		free(a->envs);
	if (a->s)
		free(a->s);
	if (a->com)
		free(a->com);
	if (a->input)
		free(a->input);
	if (a->fd)
		close(a->fd);
}
