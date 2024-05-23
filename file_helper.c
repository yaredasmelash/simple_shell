#include "main.h"
/**
 * getnewlen - Calculate the length of a new line after processing.
 * @lineptr: Pointer to the input line.
 *
 * Return: The length of the new line.
 */

ssize_t getnewlen(char *lineptr)
{
	size_t i;
	ssize_t n_len = 0;
	char cur, next;

	for (i = 0; lineptr[i]; i++)
	{
		cur = lineptr[i];
		next = lineptr[i + 1];
		if (cur == '#')
		{
			if (i == 0 || lineptr[i - 1] == ' ')
			{
				lineptr[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (cur == ';')
			{
				if (next == ';' && lineptr[i - 1] != ' ' && lineptr[i - 1] != ';')
				{
					n_len += 2;
					continue;
				}
				else if (lineptr[i - 1] == ';' && next != ' ')
				{
					n_len += 2;
					continue;
				}
				if (lineptr[i - 1] != ' ')
					n_len++;
				if (next != ' ')
					n_len++;
			}
			else
				logicalop(&lineptr[i], &n_len);
		}
		else if (cur == ';')
		{
			if (i != 0 && lineptr[i - 1] != ' ')
				n_len++;
			if (next != ' ' && next != ';')
				n_len++;
		}
		n_len++;
	}
	return (n_len);
}
/**
 * args_free - Free memory allocated for argument
 * array and front part array.
 *
 * @args: The argument array.
 * @fron: The front part array.
 */
void args_free(char **args, char **fron)
{
	size_t size;

	for (size = 0; args[size] || args[size + 1]; size++)
		free(args[size]);

	free(fron);
}

/**
 * env_value_get - Get the value of an environment variable.
 * @beg: Pointer to the beginning of the variable name.
 * @l: Length of the variable name.
 *
 * Return: A string representing the value of the environment variable,
 *         or NULL if the variable is not found.
 */
char *env_value_get(char *beg, int l)
{
	char **v_addr;
	char *rep = NULL, *temp, *var;

	var = malloc(l + 1);
	if (!l)
		return (NULL);
	var[0] = '\0';
	str_ncat(var, beg, l);

	v_addr = env_get(var);
	free(var);
	if (v_addr)
	{
		temp = *v_addr;
		while (*temp != '=')
			temp++;
		temp++;
		rep = malloc(str_len(temp) + 1);
		if (rep)
			str_cpy(rep, temp);
	}

	return (rep);
}

/**
 * rep_var - Replace variables in a line with their values.
 * @line: Pointer to the input line.
 * @exeret: Pointer to the exit status variable.
 */
void rep_var(char **line, int *exeret)
{
	int j, k = 0, len;
	char *rep = NULL, *o_line = NULL, *n_line;

	o_line = *line;
	for (j = 0; o_line[j]; j++)
	{
		if (o_line[j] == '$' && o_line[j + 1] &&
				o_line[j + 1] != ' ')
		{
			if (o_line[j + 1] == '$')
			{
				rep = pid_get();
				k = j + 2;
			}
			else if (o_line[j + 1] == '?')
			{
				rep = fun_itoa(*exeret);
				k = j + 2;
			}
			else if (o_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; o_line[k] &&
						o_line[k] != '$' &&
						o_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				rep = env_value_get(&o_line[j + 1], len);
			}
			n_line = malloc(j + str_len(rep)
					  + str_len(&o_line[k]) + 1);
			if (!line)
				return;
			n_line[0] = '\0';
			str_ncat(n_line, o_line, j);
			if (rep)
			{
				str_cat(n_line, rep);
				free(rep);
				rep = NULL;
			}
			str_cat(n_line, &o_line[k]);
			free(o_line);
			*line = n_line;
			o_line = n_line;
			j = -1;
		}
	}
}