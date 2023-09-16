#include "main.h"

/**
 * cd - changes dir
 *
 * @env: env list header
 * @dir: directory to move to
 *
 * Return: 1 on success 0 otehr wise
 */
int cd(node **env, char *dir)
{
	int stat;
	char *path, *buff = NULL;
	node *pwd = get_node(*env, "PWD");
	node *opwd = get_node(*env, "OLDPWD");

	if (!dir)
		stat = chdir(env_val(*env, "HOME"));
	else if (_strcmp(dir, "-") == 0)
		stat = chdir(env_val(*env, "OLDPWD"));
	else
		stat = chdir(dir);
	if (stat)
	{
		perror("cd failled");
		return (1);
	}
	path = getcwd(buff, 0);
	if (!path)
	{
		free(buff);
		perror("path failled");
		return (1);
	}
	set_env(opwd, env_val(*env, "PWD"), "OLDPWD=");
	set_env(pwd, path, "PWD=");
	free(buff);
	free(path);
	return (1);
}

