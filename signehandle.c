#include "main.h"
/**
 * hand_sign - Handles the signal for the shell.
 * @sgn: The signal value (unused in this function).
 *
 * This function is a signal handler for the shell.
 */

void hand_sign(int sgn)
{
	char *prompt = "\nshell$ ";

	(void)sgn;
	signal(SIGINT, hand_sign);
	write(STDIN_FILENO, prompt, 8);
}

/**
 * fun_execute - Execute a command with arguments.
 * @args: Array of command arguments.
 * @front_exec: Front of the execution list.
 *
 * This function executes a command with arguments and handles errors.
 *
 * Return: The exit status of the command.
 */
int fun_execute(char **args, char **front_exec)
{
	pid_t c_pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = location_get(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (err_create(args, 126));
		else
			ret = (err_create(args, 127));
	}
	else
	{
		c_pid = fork();
		if (c_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (c_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (err_create(args, 126));
			env_free();
			args_free(args, front_exec);
			free_list_alias(ali);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}