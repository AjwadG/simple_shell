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
	node *env_head;

	env_head = build_env(env);
	if (ac == 2)
	{
		handle_file(av, &env_head);
	}
	else if (isatty(STDIN_FILENO))
	{
		handle_terminal(av[0], &env_head);
	}
	else
	{
		handle_echo(av[0], &env_head);
	}
	return (EXIT_SUCCESS);
}
