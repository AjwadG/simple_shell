#include "main.h"

/**
 * main - entry point
 *
 * @ac: number of arguments
 * @av: pointer to array of args
 * @env: pointer to array of envs
 *
 * Return: 0 on success 1 or more other wise
 */

int main(int ac, char **av, char **env)
{

	all_t a = {NULL, NULL, NULL, 0, NULL, 0, {0, 0, 0,
		0, 0, 0, 0, 0, 0, 0}, NULL, NULL, NULL, 0};

	signal(SIGINT, SIG_IGN);

	a.env = build_env(env);
	a.name = av[0];
	if (ac == 2)
	{
		access(av[1], F_OK);
		perror(av[1]);

		a.fd = open(av[1], O_RDONLY);
		if (a.fd == -1)
		{
			perror(av[1]);
			return (-1);
		}
		handle_file(&a);
	}
	else if (isatty(STDIN_FILENO))
	{
		handle_terminal(&a);
	}
	else
	{
		handle_echo(&a);
	}
	return (EXIT_SUCCESS);
}
