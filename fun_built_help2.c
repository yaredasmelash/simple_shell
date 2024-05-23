#include "main.h"
/**
 * alias_help - Display help information for the 'alias' command.
 *
 * This function prints help information for the 'alias' shell command.
 */
void alias_help(void)
{
	char *ms = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "\talias: Print a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "the format NAME='VALUE'.\n\talias name [name2 ...]: Print";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "the aliases name, name2, etc., one per line, in the ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, ms, str_len(ms));
}
/**
 * env_help - Display help information for the 'env' command.
 *
 * This function prints help information for the 'env' shell command.
 */
void env_help(void)
{
	char *ms = "env: env\n\tDisplay the current environment.\n";

	write(STDOUT_FILENO, ms, str_len(ms));
}
/**
 * exit_help - Display help information for the 'exit' command.
 *
 * This function prints help information for the 'exit' shell command.
 */
void exit_help(void)
{
	char *ms = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "STATUS is an optional integer argument used to specify ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "the exit status. If provided, the shell will exit with ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "that status; otherwise, it defaults to exit 0.\n";
	write(STDOUT_FILENO, ms, str_len(ms));
}
/**
 * unsetenv_help - Display help information for the 'unsetenv' command.
 *
 * This function prints help information for the 'unsetenv' shell command.
 */
void unsetenv_help(void)
{
	char *ms = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "message to stderr.\n";
	write(STDOUT_FILENO, ms, str_len(ms));
}