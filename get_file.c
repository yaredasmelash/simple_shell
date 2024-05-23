#include "main.h"

/**
 * lineptr_assign - Assign a line pointer and update its size.
 *
 * @l_ptr: A pointer to the line pointer.
 * @num: A pointer to the size variable.
 * @buff: The buffer to assign to the line pointer.
 * @i: The size of the buffer.
 */
void lineptr_assign(char **l_ptr, size_t *num, char *buff, size_t i)
{
	if (*l_ptr == NULL)
	{
		if (i > 120)
			*num = i;
		else
			*num = 120;
		*l_ptr = buff;
	}
	else if (*num < i)
	{
		if (i > 120)
			*num = i;
		else
			*num = 120;
		*l_ptr = buff;
	}
	else
	{
		str_cpy(*l_ptr, buff);
		free(buff);
	}
}
/**
 * re_alloc - Reallocate memory for a given pointer.
 *
 * @pointer: The pointer to reallocate.
 * @o_size: The original size of the memory.
 * @n_size: The new size of the memory.
 *
 * Return: A pointer to the reallocated memory.
 */
void *re_alloc(void *pointer, unsigned int o_size, unsigned int n_size)
{
	void *mem;
	char *p_copy, *fill;
	unsigned int ind;

	if (n_size == o_size)
		return (pointer);

	if (pointer == NULL)
	{
		mem = malloc(n_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (n_size == 0 && pointer != NULL)
	{
		free(pointer);
		return (NULL);
	}

	p_copy = pointer;
	mem = malloc(sizeof(*p_copy) * n_size);
	if (mem == NULL)
	{
		free(pointer);
		return (NULL);
	}

	fill = mem;

	for (ind = 0; ind < o_size && ind < n_size; ind++)
		fill[ind] = *p_copy++;

	free(pointer);
	return (mem);
}

/**
 * get_line - Read a line from a stream and store it in a buffer.
 *
 * @line_pointer: A pointer to the line buffer.
 * @num: A pointer to the size variable.
 * @stream: The stream to read from.
 *
 * Return: The number of characters read (including newline),
 * or -1 on failure.
 */
ssize_t get_line(char **line_pointer, size_t *num, FILE *stream)
{
	static ssize_t inp;
	ssize_t ret;
	char ch = 'x', *buff;
	int r;

	if (inp == 0)
		fflush(stream);
	else
		return (-1);
	inp = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (ch != '\n')
	{
		r = read(STDIN_FILENO, &ch, 1);
		if (r == -1 || (r == 0 && inp == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && inp != 0)
		{
			inp++;
			break;
		}

		if (inp >= 120)
			buff = re_alloc(buff, inp, inp + 1);

		buff[inp] = ch;
		inp++;
	}
	buff[inp] = '\0';

	lineptr_assign(line_pointer, num, buff, inp);

	ret = inp;
	if (r != 0)
		inp = 0;
	return (ret);
}