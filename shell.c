#include "main.h"


/**
 * main - entry point
 *
 * @ac: number of arguments
 * @av: pointer to array of args
 *
 * Return: 0 on success 1 or more other wise
 */

int main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("%s %s\n", av[0], av[1]);
	}
	else if (isatty(STDIN_FILENO))
	{
		handle_terminal(av[0]);
	}
	else
	{
		handle_echo(av[0]);
	}
	return (EXIT_SUCCESS);
}
