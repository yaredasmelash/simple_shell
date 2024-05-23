#include "main.h"
/**
 * setenv_help - Display help information for the 'setenv' command.
 *
 * This function prints help information for the 'setenv' shell command.
 */
void setenv_help(void)
{
	char *ms = "setenv: setenv [VARIABLE] [VALUE]\n\tInitialize a new";

	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, ms, str_len(ms));
}
/**
 * all_help - Display help information for Shellby.
 *
 * This function prints help information for the Shellby shell commands.
 */
void all_help(void)
{
	char *mg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "Define or display aliases: alias [NAME[='VALUE'] ...]\n";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "  cd    \tChange the current directory: cd [DIRECTORY]\n";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "  exit    \tExit the shell: exit [STATUS]\n  env     \t";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "Display or set environment variables: env\n";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "  setenv  \tSet an environment variable: setenv [VARIABLE] [VALUE]\n";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "  unsetenv\tUnset an environment variable: unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, mg, str_len(mg));
}

/**
 * cd_help - Display help information for the 'cd' command.
 *
 * This function prints help information for the 'cd' shell command.
 */
void cd_help(void)
{
	char *mg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "process to DIRECTORY.\n\n\tIf no argument is provided, ";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "the command is interpreted as cd $HOME. If the argument '-' ";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "is given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "The environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, mg, str_len(mg));
	mg = "after a change of directory.\n";
	write(STDOUT_FILENO, mg, str_len(mg));
}

/**
 * _help - Display help information for the 'help' command.
 *
 * This function prints help information for the 'help' shell command.
 */
void _help(void)
{
	char *ms = "help: help\n\tDisplay infn about Shellby builtin commands.\n";

	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "\n\thelp [BUILTIN NAME]\n\tShow specific information for each ";
	write(STDOUT_FILENO, ms, str_len(ms));
	ms = "builtin command.\n";
	write(STDOUT_FILENO, ms, str_len(ms));
}