#include "main.h"
/**
 * pid_get - Get the process ID of the calling process.
 *
 * Return: A string representing the process ID, or NULL on failure.
 */
char *pid_get(void)
{
	size_t size = 0;
	char *buff;
	ssize_t n;

	n = open("/proc/self/stat", O_RDONLY);
	if (n == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(n);
		return (NULL);
	}
	read(n, buff, 120);
	while (buff[size] != ' ')
		size++;
	buff[size] = '\0';

	close(n);
	return (buff);
}
/**
 * line_handler - Process the input line for improved formatting.
 * @line_ptr: Pointer to the input line.
 * @read_num: Number of characters read.
 */
void line_handler(char **line_ptr, ssize_t read_num)
{
	char *o_line, *n_line;
	char pre, cur, next;
	size_t i, j;
	ssize_t n_len;

	n_len = getnewlen(*line_ptr);
	if (n_len == read_num - 1)
		return;
	n_line = malloc(n_len + 1);
	if (!n_line)
		return;
	j = 0;
	o_line = *line_ptr;
	for (i = 0; o_line[i]; i++)
	{
		cur = o_line[i];
		next = o_line[i + 1];
		if (i != 0)
		{
			pre = o_line[i - 1];
			if (cur == ';')
			{
				if (next == ';' && pre != ' ' && pre != ';')
				{
					n_line[j++] = ' ';
					n_line[j++] = ';';
					continue;
				}
				else if (pre == ';' && next != ' ')
				{
					n_line[j++] = ';';
					n_line[j++] = ' ';
					continue;
				}
				if (pre != ' ')
					n_line[j++] = ' ';
				n_line[j++] = ';';
				if (next != ' ')
					n_line[j++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (next == '&' && pre != ' ')
					n_line[j++] = ' ';
				else if (pre == '&' && next != ' ')
				{
					n_line[j++] = '&';
					n_line[j++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (next == '|' && pre != ' ')
					n_line[j++]  = ' ';
				else if (pre == '|' && next != ' ')
				{
					n_line[j++] = '|';
					n_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (i != 0 && o_line[i - 1] != ' ')
				n_line[j++] = ' ';
			n_line[j++] = ';';
			if (next != ' ' && next != ';')
				n_line[j++] = ' ';
			continue;
		}
		n_line[j++] = o_line[i];
	}
	n_line[j] = '\0';

	free(*line_ptr);
	*line_ptr = n_line;
}

/**
 * logicalop - Handle logical operators and update the length accordingly.
 * @lineptr: Pointer to the character in the input line.
 * @n_len: Pointer to the length variable to be updated.
 */
void logicalop(char *lineptr, ssize_t *n_len)
{
	char pre, cur, next;

	pre = *(lineptr - 1);
	cur = *lineptr;
	next = *(lineptr + 1);

	if (cur == '&')
	{
		if (next == '&' && pre != ' ')
			(*n_len)++;
		else if (pre == '&' && next != ' ')
			(*n_len)++;
	}
	else if (cur == '|')
	{
		if (next == '|' && pre != ' ')
			(*n_len)++;
		else if (pre == '|' && next != ' ')
			(*n_len)++;
	}
}