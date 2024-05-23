#include "main.h"

/**
 * env_err - Create an error message related to environment operations.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *env_err(char **args)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (NULL);

	args--;
	len = str_len(glo_name) + str_len(h_str) + str_len(args[0]) + 45;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	str_cpy(err, glo_name);
	str_cat(err, ": ");
	str_cat(err, h_str);
	str_cat(err, ": ");
	str_cat(err, args[0]);
	str_cat(err, ": Unable to add/remove from environment\n");

	free(h_str);
	return (err);
}


/**
 * exit_err - Create an error message for illegal exit number.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *exit_err(char **args)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (NULL);

	len = str_len(glo_name) + str_len(h_str) + str_len(args[0]) + 27;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	str_cpy(err, glo_name);
	str_cat(err, ": ");
	str_cat(err, h_str);
	str_cat(err, ": exit: Illegal number: ");
	str_cat(err, args[0]);
	str_cat(err, "\n");

	free(h_str);
	return (err);
}

/**
 * syntax_err - Create a syntax error message.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *syntax_err(char **args)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (NULL);

	len = str_len(glo_name) + str_len(h_str) + str_len(args[0]) + 33;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	str_cpy(err, glo_name);
	str_cat(err, ": ");
	str_cat(err, h_str);
	str_cat(err, ": Syntax error: \"");
	str_cat(err, args[0]);
	str_cat(err, "\" unexpected\n");

	free(h_str);
	return (err);
}