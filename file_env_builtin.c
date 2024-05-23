#include "main.h"

/**
 * getfun_built - Get the function corresponding to
 * a built-in command.
 *
 * @cmd: The built-in command.
 *
 * Return: Pointer to the corresponding function,
 * or NULL if not found.
 */
int (*getfun_built(char *cmd))(char **args, char **fron)
{
	fun_builtin_t funcs[] = {
		{ "exit", exit_shell },
		{ "env", env_shell },
		{ "setenv", set_env },
		{ "unsetenv", unset_env },
		{ "cd", my_cd },
		{ "alias", my_alias },
		{ "help", help_shell },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].b_name; i++)
	{
		if (str_cmp(funcs[i].b_name, cmd) == 0)
			break;
	}
	return (funcs[i].fun);
}
/**
 * set_env - Set or update an environment variable.
 *
 * @args: An array of arguments containing the variable name and value.
 * @fron: An array representing the front of the arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_env(char **args, char __attribute__((__unused__)) **fron)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (err_create(args, -1));

	new_value = malloc(str_len(args[0]) + 1 + str_len(args[1]) + 1);
	if (!new_value)
		return (err_create(args, -1));
	str_cpy(new_value, args[0]);
	str_cat(new_value, "=");
	str_cat(new_value, args[1]);

	env_var = env_get(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (err_create(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * my_cd - Change the current working directory.
 *
 * @args: An array of arguments passed to the command.
 * @fron: An array representing the front of the arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_cd(char **args, char __attribute__((__unused__)) **fron)
{
	char **dirinf, *nline = "\n";
	char *o_pwd = NULL, *pwd = NULL;
	struct stat dir;

	o_pwd = getcwd(o_pwd, 0);
	if (!o_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || str_cmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (env_get("OLDPWD") != NULL)
					(chdir(*env_get("OLDPWD") + 7));
			}
			else
			{
				free(o_pwd);
				return (err_create(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(o_pwd);
				return (err_create(args, 2));
			}
		}
	}
	else
	{
		if (env_get("HOME") != NULL)
			chdir(*(env_get("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dirinf = malloc(sizeof(char *) * 2);
	if (!dirinf)
		return (-1);

	dirinf[0] = "OLDPWD";
	dirinf[1] = o_pwd;
	if (set_env(dirinf, dirinf) == -1)
		return (-1);

	dirinf[0] = "PWD";
	dirinf[1] = pwd;
	if (set_env(dirinf, dirinf) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, str_len(pwd));
		write(STDOUT_FILENO, nline, 1);
	}
	free(o_pwd);
	free(pwd);
	free(dirinf);
	return (0);
}

/**
 * unset_env - Unset an environment variable.
 *
 * @args: An array of arguments containing the variable name.
 * @fron: An array representing the front of the arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int unset_env(char **args, char __attribute__((__unused__)) **fron)
{
	char **envar, **n_environ;
	size_t size;
	int ind1, ind2;

	if (!args[0])
		return (err_create(args, -1));
	envar = env_get(args[0]);
	if (!envar)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	n_environ = malloc(sizeof(char *) * size);
	if (!n_environ)
		return (err_create(args, -1));

	for (ind1 = 0, ind2 = 0; environ[ind1]; ind1++)
	{
		if (*envar == environ[ind1])
		{
			free(*envar);
			continue;
		}
		n_environ[ind2] = environ[ind1];
		ind2++;
	}
	free(environ);
	environ = n_environ;
	environ[size - 1] = NULL;

	return (0);
}