#include "main.h"

/**
 * cd - changes dir
 *
 * @dir: directory to move to
 * @a: pointer to all struct
 *
 * Return: 1 on success 0 otehr wise
 */
int cd(char *dir, all_t *a)
{
	int stat = 0;
	char *path = NULL, *buff = NULL;
	node *pwd = get_node(a->env, "PWD");
	node *opwd = get_node(a->env, "OLDPWD");

	if (!dir)
	{
		path = env_val(a->env, "HOME");
		if (path != NULL)
			stat = chdir(path);
	}
	else if (_strcmp(dir, "-") == 0)
	{
		path = env_val(a->env, "OLDPWD");
		if (path != NULL)
			stat = chdir(path);
		else
			path = env_val(a->env, "PWD");
		write(STDOUT_FILENO, path, len(path) - 1);
		write(STDOUT_FILENO, "\n", 1);
	}
	else
		stat = chdir(dir);
	if (stat)
	{
		cd_error(dir, a);
		return (1);
	}
	path = getcwd(buff, 0);
	if (!path)
	{
		free(buff);
		return (1);
	}
	set_env(opwd, env_val(a->env, "PWD"), "OLDPWD=");
	set_env(pwd, path, "PWD=");
	free(buff);
	free(path);
	return (1);
}


/**
 * cd_error - prints cd errors
 *
 * @dir: name od directory
 * @a: pointer to all struct
 */
void cd_error(char *dir, all_t *a)
{
	char s[1024], *num, *err = "cd: can't cd to ";
	int l;

	_memcpy(s, a->name, len(a->name) - 1);
	_memcpy(&s[len(a->name) - 1], ": ", 2);
	num = malloc(10);
	nto_string(a->count, num);
	_memcpy(&s[len(a->name) + 1], num, len(num) - 1);
	l = len(a->name) + 1 + len(num) + 2;
	_memcpy(&s[l - 3], ": ", 2);
	_memcpy(&s[l - 1], err, len(err) - 1);
	_memcpy(&s[l + len(err) - 2], dir, len(dir) - 1);
	_memcpy(&s[l + len(err) + len(dir) - 3], "\n", 2);
	write(STDERR_FILENO, s, len(s) - 1);
	fflush(stderr);
	free(num);
	a->status = 0;

}
