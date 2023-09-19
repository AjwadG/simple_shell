#include "main.h"


/**
 * file_err - prints files errors
 *
 * @a: pointer to all struct
 * @file: file name as string
 */
void file_err(all_t *a, char *file)
{
	char s[1024], *err = "Can't open ";
	int l;

	_memcpy(s, a->name, len(a->name) - 1);
	_memcpy(&s[len(a->name) - 1], ": ", 2);
	_memcpy(&s[len(a->name) + 1], "0", 1);
	l = len(a->name) + 2 + 3;
	_memcpy(&s[l - 3], ": ", 2);
	_memcpy(&s[l - 1], err, len(err) - 1);
	_memcpy(&s[l + len(err) - 2], file, len(file) - 1);
	l = l + len(err) + len(file) - 3;
	_memcpy(&s[l], "\n", 2);
	write(STDERR_FILENO, s, len(s) - 1);
	fflush(stderr);
	a->fd = 0;
	free_all(a);
}



/**
 * comand_err - prints commands errors
 *
 * @name: name of the file
 * @n: exe count
 * @com: name of the command
 */
void comand_err(char *name, int n, char *com)
{
	char *s, *tmp1 = malloc(10), *tmp2;


	s = str_concat(name, ": ");
	nto_string(n, tmp1);
	tmp2 = str_concat(s, tmp1);
	free(tmp1);
	free(s);
	tmp1 = str_concat(tmp2, ": ");
	free(tmp2);
	s = str_concat(tmp1, com);
	free(tmp1);

	if (len(com) > 255)
		tmp1 = str_concat(s, ": File name too long\n");
	else
		tmp1 = str_concat(s, ": not found\n");

	write(STDERR_FILENO, tmp1, len(tmp1) - 1);
	free(tmp1);
	free(s);
}
