#include "main.h"

/**
 * env_copy - Create a copy of the current environment.
 *
 * Return: A copy of the environment on success, NULL on failure.
 */
char **env_copy(void)
{
	char **n_environ;
	size_t size;
	int ind;

	for (size = 0; environ[size]; size++)
		;

	n_environ = malloc(sizeof(char *) * (size + 1));
	if (!n_environ)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		n_environ[ind] = malloc(str_len(environ[ind]) + 1);

		if (!n_environ[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(n_environ[ind]);
			free(n_environ);
			return (NULL);
		}
		str_cpy(n_environ[ind], environ[ind]);
	}
	n_environ[ind] = NULL;

	return (n_environ);
}

/**
 * env_free - Free the memory allocated for the environment.
 */
void env_free(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}

/**
 * env_get - Get the address of an environment variable.
 *
 * @variable: The name of the environment variable to find.
 *
 * Return: The address of the environment variable on success, NULL on failure.
 */
char **env_get(const char *variable)
{
	int ind, len;

	len = str_len(variable);
	for (ind = 0; environ[ind]; ind++)
	{
		if (str_ncmp(variable, environ[ind], len) == 0)
			return (&environ[ind]);
	}

	return (NULL);
}