#include "main.h"



/**
 * handle_file - handles the input from file arg[1]
 * @arg: list of args
 * @env: list of envs
 */

void handle_file(char **av, node **env)
{
	char *s = malloc(1), **arg;
	pid_t pid;
	int status, len, size, fd = open(av[1], O_RDONLY);

	if (fd == -1)
	{
		perror(av[1]);
		exit(-1);
	}

	while (1)
	{
		len = _getline(&s, &size, fd);
		if (len == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			return;
		}
		if (len == EOF)
			return;
		else if (isempty(s))
			continue;
		arg = get_arg(s, " \n");
		if (_strcmp(arg[0], "exit") == 0)
		{
			exit_with(arg[1]);
			continue;
		}
		else if (_strcmp(arg[0], "env") == 0 && print_env(*env))
			continue;
		else if (_strcmp(arg[0], "cd") == 0 && cd(env, arg[1]))
			continue;
		else if (_strcmp(arg[0], "setenv") == 0)
		{
			if (arg[1] && arg[2])
				_setenv(env, arg[1], arg[2]);
			else
				write(STDOUT_FILENO, "wrong usage\n", 12);
			continue;
		}
		else if (_strcmp(arg[0], "unsetenv") == 0 && _unsetenv(arg[1], env))
			continue;
		arg[0] = get_path(s);
		if (arg[0] == NULL)
		{
			perror(s);
			continue;
		}
		pid = fork();
		if (pid == 0 && execve(arg[0], arg, environ) == -1)
		{
			perror(av[0]);
			return;
		}
		wait(&status);
	}
}
