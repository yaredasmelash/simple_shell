#include "main.h"
/**
 * dir_path_fill - Fills in missing directories in the PATH
 * with the current working directory.
 * @path: The original PATH string.
 *
 * Return: A dynamically allocated string with the modified PATH.
 */
char *dir_path_fill(char *path)
{
	int i, len = 0;
	char *p_copy, *pwd;

	pwd = *(env_get("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += str_len(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	p_copy = malloc(sizeof(char) * (len + 1));
	if (!p_copy)
		return (NULL);
	p_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				str_cat(p_copy, pwd);
				str_cat(p_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				str_cat(p_copy, ":");
				str_cat(p_copy, pwd);
			}
			else
				str_cat(p_copy, ":");
		}
		else
		{
			str_ncat(p_copy, &path[i], 1);
		}
	}
	return (p_copy);
}
/**
 * location_get - Finds the location of a command in the PATH directories.
 * @cmd: The command to search for.
 *
 * Return: A dynamically allocated string containing the full path
 * of the command, or NULL if not found.
 */
char *location_get(char *cmd)
{
	char **path, *temp;
	node_t *dirs, *head;
	struct stat st;

	path = env_get("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_dir_path(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(str_len(dirs->directory) + str_len(cmd) + 2);
		if (!temp)
			return (NULL);

		str_cpy(temp, dirs->directory);
		str_cat(temp, "/");
		str_cat(temp, cmd);

		if (stat(temp, &st) == 0)
		{
			list_free(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	list_free(head);

	return (NULL);
}

/**
 * get_dir_path - Creates a linked list of directories from the PATH variable.
 * @dir_path: The PATH variable string.
 *
 * Return: A pointer to the head of the linked list.
 */
node_t *get_dir_path(char *dir_path)
{
	int ind;
	char **dirs, *p_copy;
	node_t *head = NULL;

	p_copy = dir_path_fill(dir_path);
	if (!p_copy)
		return (NULL);
	dirs = string_toke(p_copy, ":");
	free(p_copy);
	if (!dirs)
		return (NULL);

	for (ind = 0; dirs[ind]; ind++)
	{
		if (add_end_node(&head, dirs[ind]) == NULL)
		{
			list_free(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}