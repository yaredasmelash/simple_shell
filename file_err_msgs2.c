#include "main.h"
/**
 * one_err - Create an error message for alias not found.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *one_err(char **args)
{
	char *err;
	int len;

	len = str_len(glo_name) + str_len(args[0]) + 13;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
		return (NULL);

	str_cpy(err, "alias: ");
	str_cat(err, args[0]);
	str_cat(err, " not found\n");

	return (err);
}
/**
 * num1_err - Create an error message for a numeric argument.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *num1_err(char **args)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (NULL);

	len = str_len(glo_name) + str_len(h_str) + str_len(args[0]) + 24;
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
	str_cat(err, ": Permission denied\n");

	free(h_str);
	return (err);
}
/**
 * cd_err - Create an error message for cd command.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *cd_err(char **args)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = str_len(glo_name) + str_len(h_str) + str_len(args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	str_cpy(err, glo_name);
str_cat(err, ": ");
	str_cat(err, h_str);
	if (args[0][0] == '-')
		str_cat(err, ": cd: Illegal option ");
	else
		str_cat(err, ": cd: can't cd to ");
	str_cat(err, args[0]);
	str_cat(err, "\n");

	free(h_str);
	return (err);
}
/**
 * num2_err - Create an error message for a not found numeric argument.
 *
 * @args: An array of arguments containing information for the error message.
 *
 * Return: The error message on success, NULL on failure.
 */
char *num2_err(char **args)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (NULL);

	len = str_len(glo_name) + str_len(h_str) + str_len(args[0]) + 16;
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
	str_cat(err, ": not found\n");

	free(h_str);
	return (err);
}