#include "main.h"


/**
 * len_num - Calculate the number of digits in an integer.
 *
 * @n: The integer for which to calculate the number of digits.
 *
 * Return: The number of digits in the integer.
 */
int len_num(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		len++;
		n1 /= 10;
	}

	return (len);
}

/**
 * fun_itoa - Convert an integer to a string.
 *
 * @number: The integer to be converted.
 *
 * Return: A string representation of the integer.
 */
char *fun_itoa(int number)
{
	char *buff;
	int len = len_num(number);
	unsigned int n;

	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);

	buff[len] = '\0';

	if (number < 0)
	{
		n = number * -1;
		buff[0] = '-';
	}
	else
	{
		n = number;
	}

	len--;
	do {
		buff[len] = (n % 10) + '0';
		n /= 10;
		len--;
	} while (n > 0);

	return (buff);
}

/**
 * err_create - Create and print an error message based on the error code.
 *
 * @args: The command arguments.
 * @error: The error code.
 *
 * Return: The error code.
 */
int err_create(char **args, int error)
{
	char *err;

	switch (error)
	{
	case -1:
		err = env_err(args);
		break;
	case 1:
		err = one_err(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			err = exit_err(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			err = syntax_err(args);
		else
			err = cd_err(args);
		break;
	case 126:
		err = num1_err(args);
		break;
	case 127:
		err = num2_err(args);
		break;
	}
	write(STDERR_FILENO, err, str_len(err));

	if (err)
		free(err);
	return (error);
}