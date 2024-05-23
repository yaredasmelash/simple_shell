#include "main.h"
/**
 * args_call - Execute a series of commands based on logical operators.
 * @args: Array of command-line arguments.
 * @fron: Array of front variables.
 * @exeret: Pointer to the exit status variable.
 *
 * Return: The exit status of the last executed command.
 */
int args_call(char **args, char **fron, int *exeret)
{
	int ret, ind;

	if (!args[0])
		return (*exeret);
	for (ind = 0; args[ind]; ind++)
	{
		if (str_ncmp(args[ind], "||", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = rep_alia(args);
			ret = args_run(args, fron, exeret);
			if (*exeret != 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (ret);
			}
		}
		else if (str_ncmp(args[ind], "&&", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = rep_alia(args);
			ret = args_run(args, fron, exeret);
			if (*exeret == 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (ret);
			}
		}
	}
	args = rep_alia(args);
	ret = args_run(args, fron, exeret);
	return (ret);
}
/**
 * args_get - Read and process user input from the standard input.
 * @line_ptr: Pointer to the input line buffer.
 * @exeret: Pointer to the exit status variable.
 *
 * Return: A pointer to the processed input line.
 */
char *args_get(char *line_ptr, int *exeret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "shell$ ";

	if (line_ptr)
		free(line_ptr);

	read = get_line(&line_ptr, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		glo_hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (args_get(line_ptr, exeret));
	}

	line_ptr[read - 1] = '\0';
	rep_var(&line_ptr, exeret);
	line_handler(&line_ptr, read);

	return (line_ptr);
}

/**
 * args_run - Execute a command with arguments.
 * @args: Array of command-line arguments.
 * @fron: Array of front variables.
 * @exeret: Pointer to the exit status variable.
 *
 * Return: The exit status of the executed command.
 */
int args_run(char **args, char **fron, int *exeret)
{
	int ret, i;
	int (*builtin)(char **args, char **fron);

	builtin = getfun_built(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, fron);
		if (ret != FILE_EXIT)
			*exeret = ret;
	}
	else
	{
		*exeret = fun_execute(args, fron);
		ret = *exeret;
	}

	glo_hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * args_handle - Handle the execution of commands and arguments.
 * @exeret: Pointer to the exit status variable.
 *
 * Return: The exit status of the last executed command.
 */
int args_handle(int *exeret)
{
	int ret = 0, ind;
	char **args, *lineptr = NULL, **fron;

	lineptr = args_get(lineptr, exeret);
	if (!lineptr)
		return (FILE_END);

	args = string_toke(lineptr, " ");
	free(lineptr);
	if (!args)
		return (ret);
	if (args_check(args) != 0)
	{
		*exeret = 2;
		args_free(args, args);
		return (*exeret);
	}
	fron = args;

	for (ind = 0; args[ind]; ind++)
	{
		if (str_ncmp(args[ind], ";", 1) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			ret = args_call(args, fron, exeret);
			args = &args[++ind];
			ind = 0;
		}
	}
	if (args)
		ret = args_call(args, fron, exeret);

	free(fron);
	return (ret);
}

/**
 * args_check - Check for syntax errors in the arguments.
 * @args: Array of strings representing the command and its arguments.
 *
 * Return: 0 if no syntax errors, otherwise returns the error code.
 */
int args_check(char **args)
{
	size_t i;
	char *current, *next;

	for (i = 0; args[i]; i++)
	{
		current = args[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
				return (err_create(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (err_create(&args[i + 1], 2));
		}
	}
	return (0);
}