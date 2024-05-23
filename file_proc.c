#include "main.h"
/**
 * not_open - Handles the case when a file cannot be opened.
 * @f_path: The path to the file that could not be opened.
 *
 * Return: Returns the exit status indicating file open failure.
 *
 * Description: This function generates an error message and returns the exit
 * status (127) when a file cannot be opened. It prints an error message to
 * STDERR including the program name, history number, and the file path.
 */
int not_open(char *f_path)
{
	char *err, *h_str;
	int len;

	h_str = fun_itoa(glo_hist);
	if (!h_str)
		return (127);

	len = str_len(glo_name) + str_len(h_str) + str_len(f_path) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(h_str);
		return (1);
	}

	str_cpy(err, glo_name);
	str_cat(err, ": ");
	str_cat(err, h_str);
	str_cat(err, ": Cannot open ");
	str_cat(err, f_path);
	str_cat(err, "\n");

	free(h_str);
	write(STDERR_FILENO, err, len);
	free(err);
	return (1);
}
/**
 * file_commands - Reads and executes commands from a file.
 * @path_file: Path to the file containing commands.
 * @ret_exe: Pointer to the exit status variable.
 *
 * Return: Returns the exit status after executing the commands.
 *
 * Description: This function reads and executes commands from a file. It
 * processes the file, replacing newline characters with semicolons and
 * handling variable substitution. The commands are then executed, and the
 * exit status is returned.
 */
int file_commands(char *path_file, int *ret_exe)
{
	ssize_t file, b_read, i;
	unsigned int l_size = 0;
	unsigned int o_size = 120;
	char *line, **args, **front;
	char buff[120];
	int ret;

	glo_hist = 0;
	file = open(path_file, O_RDONLY);
	if (file == -1)
	{
		*ret_exe = not_open(path_file);
		return (*ret_exe);
	}
	line = malloc(sizeof(char) * o_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buff, 119);
		if (b_read == 0 && l_size == 0)
			return (*ret_exe);
		buff[b_read] = '\0';
		l_size += b_read;
		line = re_alloc(line, o_size, l_size);
		str_cat(line, buff);
		o_size = l_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < l_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < l_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	rep_var(&line, ret_exe);
	line_handler(&line, l_size);
	args = string_toke(line, " ");
	free(line);
	if (!args)
		return (0);
	if (args_check(args) != 0)
	{
		*ret_exe = 2;
		args_free(args, args);
		return (*ret_exe);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (str_ncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = args_call(args, front, ret_exe);
			args = &args[++i];
			i = 0;
		}
	}

	ret = args_call(args, front, ret_exe);

	free(front);
	return (ret);
}