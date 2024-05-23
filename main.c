#include "main.h"

/**
 * main - Entry point for the shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exeret = &retn;
	char *prompt = "shell$ ", *newline = "\n";

	glo_name = argv[0];
	glo_hist = 1;
	ali = NULL;
	signal(SIGINT, hand_sign);

	*exeret = 0;
	environ = env_copy();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = file_commands(argv[1], exeret);
		env_free();
		free_list_alias(ali);
		return (*exeret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != FILE_END && ret != FILE_EXIT)
			ret = args_handle(exeret);
		env_free();
		free_list_alias(ali);
		return (*exeret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 7);
		ret = args_handle(exeret);
		if (ret == FILE_END || ret == FILE_EXIT)
		{
			if (ret == FILE_END)
				write(STDOUT_FILENO, newline, 1);
			env_free();
			free_list_alias(ali);
			exit(*exeret);
		}
	}

	env_free();
	free_list_alias(ali);
	return (*exeret);
}