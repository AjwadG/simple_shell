#include "main.h"

/**
 * sig_handler - handles ctrl C signal
 * @n: signal number
 */
void sig_handler(int n)
{
	(void) n;
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}


/**
 * main - entry point
 *
 * @ac: number of arguments
 * @av: pointer to array of args
 * @env: pointer to array of envs
 *
 * Return: 0 on success 1 or more otherwise
 */

int main(int ac, char **av, char **env)
{

	all_t a = {NULL, NULL, NULL, 0, NULL, 0, {0, 0, 0,
		0, 0, 0, 0, 0, 0, 0}, NULL, NULL, NULL, NULL, 0};


	a.env = build_env(env);
	a.name = av[0];
	if (ac == 2)
	{
		a.fd = open(av[1], O_RDONLY);
		if (a.fd == -1)
		{
			file_err(&a, av[1]);
			return (127);
		}
		non_interactive_mode(&a);
	}
	else if (isatty(STDIN_FILENO))
	{
		signal(SIGINT, sig_handler);
		interactive_mode(&a);
	}
	else
	{
		non_interactive_mode(&a);
	}
	return (EXIT_SUCCESS);
}

