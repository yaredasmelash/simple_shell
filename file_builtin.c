#include "main.h"
/**
 * env_shell - Display the current environment.
 *
 * @args: An array of arguments passed to the command.
 * @fron: An array representing the front of the arguments.
 *
 * Return: Always returns 0.
 */
int env_shell(char **args, char __attribute__((__unused__)) **fron)
{

	int ind;
	char ch = '\n';

	if (!environ)
		return (-1);

	for (ind = 0; environ[ind]; ind++)
	{
		write(STDOUT_FILENO, environ[ind], str_len(environ[ind]));
		write(STDOUT_FILENO, &ch, 1);
	}

	(void)args;
	return (0);
}

/**
 * exit_shell - Exit the Shellby shell.
 *
 * @args: An array of arguments passed to the command.
 * @fron: An array representing the front of the arguments.
 *
 * Return: The exit status.
 */
int exit_shell(char **args, char **fron)
{
	int i, len = 10;
	unsigned int n = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len++;
		}
		for (; args[0][i]; i++)
		{
			if (i <=  len && args[0][i] >= '0' && args[0][i] <= '9')
				n = (n * 10) + (args[0][i] - '0');
			else
				return (err_create(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (n > max - 1)
		return (err_create(--args, 2));
	args -= 1;
	args_free(args, fron);
	env_free();
	free_list_alias(ali);
	exit(n);
}

/**
 * help_shell - Display help information for Shellby shell commands.
 *
 * @args: An array of arguments passed to the command.
 * @fron: An array representing the front of the arguments.
 *
 * Return: Always returns 0.
 */
int help_shell(char **args, char __attribute__((__unused__)) **fron)
{
	if (!args[0])
		all_help();
	else if (str_cmp(args[0], "alias") == 0)
		alias_help();
	else if (str_cmp(args[0], "cd") == 0)
		cd_help();
	else if (str_cmp(args[0], "exit") == 0)
		exit_help();
	else if (str_cmp(args[0], "env") == 0)
		env_help();
	else if (str_cmp(args[0], "setenv") == 0)
		setenv_help();
	else if (str_cmp(args[0], "unsetenv") == 0)
		unsetenv_help();
	else if (str_cmp(args[0], "help") == 0)
		_help();
	else
		write(STDERR_FILENO, glo_name, str_len(glo_name));

	return (0);
}