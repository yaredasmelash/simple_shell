#include "main.h"

/**
 * alias_set - Set or update an alias with the given value.
 * @varname: Alias name.
 * @val: Alias value.
 *
 * This function sets or updates an alias with the given value.
 */
void alias_set(char *varname, char *val)
{
	struct_alias_t *temp = ali;
	int len, j, k;
	char *n_value;

	*val = '\0';
	val++;
	len = str_len(val) - str_spn(val, "'\"");
	n_value = malloc(sizeof(char) * (len + 1));
	if (!n_value)
		return;
	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')
			n_value[k++] = val[j];
	}
	n_value[k] = '\0';
	while (temp)
	{
		if (str_cmp(varname, temp->a_name) == 0)
		{
			free(temp->a_value);
			temp->a_value = n_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		alias_end_add(&ali, varname, n_value);
}
/**
 * my_alias - Handle alias commands.
 * @args: Array of command arguments.
 * @fron: Front of the execution list (unused in this function).
 *
 * This function manages alias commands, displaying alias values
 * or setting new aliases based on the provided arguments.
 *
 * Return: The exit status of the function.
 */
int my_alias(char **args, char __attribute__((__unused__)) **fron)
{
	struct_alias_t *temp = ali;
	int i, retn = 0;
	char *val;

	if (!args[0])
	{
		while (temp)
		{
			alias_print(temp);
			temp = temp->next;
		}
		return (retn);
	}
	for (i = 0; args[i]; i++)
	{
		temp = ali;
		val = str_chr(args[i], '=');
		if (!val)
		{
			while (temp)
			{
				if (str_cmp(args[i], temp->a_name) == 0)
				{
					alias_print(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				retn = err_create(args + i, 1);
		}
		else
			alias_set(args[i], val);
	}
	return (retn);
}

/**
 * alias_print - Print the given alias to the standard output.
 * @alias: Pointer to the alias structure.
 *
 * This function prints the name and value of the given
 * alias to the standard output.
 */
void alias_print(struct_alias_t *alias)
{
	char *al_string;
	int len = str_len(alias->a_name) + str_len(alias->a_value) + 4;

	al_string = malloc(sizeof(char) * (len + 1));
	if (!al_string)
		return;
	str_cpy(al_string, alias->a_name);
	str_cat(al_string, "='");
	str_cat(al_string, alias->a_value);
	str_cat(al_string, "'\n");

	write(STDOUT_FILENO, al_string, len);
	free(al_string);
}
/**
 * rep_alia - Replace aliases in the given command arguments.
 * @args: Array of command arguments.
 *
 * This function replaces aliases in the command arguments with their values.
 * Return: The modified array of arguments.
 */
char **rep_alia(char **args)
{
	struct_alias_t *temp;
	int i;
	char *n_value;

	if (str_cmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = ali;
		while (temp)
		{
			if (str_cmp(args[i], temp->a_name) == 0)
			{
				n_value = malloc(sizeof(char) * (str_len(temp->a_value) + 1));
				if (!n_value)
				{
					args_free(args, args);
					return (NULL);
				}
				str_cpy(n_value, temp->a_value);
				free(args[i]);
				args[i] = n_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}