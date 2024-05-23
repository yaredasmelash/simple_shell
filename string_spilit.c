#include "main.h"

/**
 * token_count - Counts the number of tokens in a string based on a delimiter.
 * @ptr: Pointer to the string to be tokenized.
 * @del: Delimiter character.
 *
 * Return: Returns the number of tokens in the string.
 *
 * Description: This function counts the number of tokens in a string by
 * iterating through the characters and identifying token boundaries using the
 * specified delimiter. It returns the total count of tokens in the string.
 */
int token_count(char *ptr, char *del)
{
	int ind, tok = 0, len = 0;

	for (ind = 0; *(ptr + ind); ind++)
		len++;

	for (ind = 0; ind < len; ind++)
	{
		if (*(ptr + ind) != *del)
		{
			tok++;
			ind += length_token(ptr + ind, del);
		}
	}

	return (tok);
}
/**
 * length_token - Calculates the length of a token until a delimiter is found.
 * @ptr: Pointer to the start of the token.
 * @del: Delimiter character.
 *
 * Return: Returns the length of the token until the delimiter is encountered.
 *
 * Description: This function iterates through the characters starting from
 * the given pointer until it reaches the delimiter or the end of the string.
 * It returns the length of the token.
 */
int length_token(char *ptr, char *del)
{
	int ind = 0, len = 0;

	while (*(ptr + ind) && *(ptr + ind) != *del)
	{
		len++;
		ind++;
	}

	return (len);
}

/**
 * string_toke - Tokenizes a string into an array of strings
 * based on a delimiter.
 * @str_line: String to be tokenized.
 * @del: Delimiter character.
 *
 * Return: Returns an array of strings containing the tokens.
 *
 * Description: This function tokenizes a given string into an array of strings
 * based the specified delimiter character. It returns a dynamically allocated
 * array of strings, where each element is a token from the original string.
 * The array is terminated by a NULL pointer.
 */
char **string_toke(char *str_line, char *del)
{
	char **ptr;
	int ind = 0, tok, t, let, l;

	tok = token_count(str_line, del);
	if (tok == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tok + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tok; t++)
	{
		while (str_line[ind] == *del)
			ind++;

		let = length_token(str_line + ind, del);

		ptr[t] = malloc(sizeof(char) * (let + 1));
		if (!ptr[t])
		{
			for (ind -= 1; ind >= 0; ind--)
				free(ptr[ind]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < let; l++)
		{
			ptr[t][l] = str_line[ind];
			ind++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}