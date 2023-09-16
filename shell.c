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

	if (ac == 2)
	{
		env_head = build_env(env);
		print_env(env_head);
		free_env(env_head);
		return (0);
	}
	else if (isatty(STDIN_FILENO))
	{
		env_head = build_env(env);
		handle_terminal(av[0], &env_head);
	}
	else
	{
		env_head = build_env(env);
		handle_echo(av[0], &env_head);
	}
	return (EXIT_SUCCESS);
}
