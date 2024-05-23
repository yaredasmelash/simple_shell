#include "main.h"
/**
 * str_cpy - Copies a string from source to destination.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer.
 *
 * Description: This function copies the string from source to the destination,
 * including the null terminator. It assumes that the destination buffer has
 * sufficient space to accommodate the entire source string.
 */
char *str_cpy(char *dest, const char *src)
{
	size_t size;

	for (size = 0; src[size] != '\0'; size++)
		dest[size] = src[size];
	dest[size] = '\0';
	return (dest);
}

/**
 * str_chr - Locates the first occurrence of a character in a string.
 * @str: Pointer to the string to be searched.
 * @ch: The character to search for.
 *
 * Return: Pointer the first occurrence of 'ch' in 'str', or NULL if not found.
 *
 * Description:This function searches for the first occurrence of the character
 * 'ch' in the string 'str'. If the character is found, it returns a pointer to
 * its location in the string; otherwise, it returns NULL.
 */
char *str_chr(char *str, char ch)
{
	int ind;

	for (ind = 0; str[ind]; ind++)
	{
		if (str[ind] == ch)
			return (str + ind);
	}

	return (NULL);
}
/**
 * str_cat - Concatenates two strings.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer.
 *
 * Description: This function concatenates the source string to the end of the
 * destination string. It assumes that the destination buffer has sufficient
 * space to accommodate the concatenation.
 */
char *str_cat(char *dest, const char *src)
{
	char *d_temp;
	const char *s_temp;

	d_temp = dest;
	s_temp =  src;

	while (*d_temp != '\0')
		d_temp++;

	while (*s_temp != '\0')
		*d_temp++ = *s_temp++;
	*d_temp = '\0';
	return (dest);
}

/**
 * str_ncmp - Compares two strings up to a specified number of characters.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 * @num: Number of characters to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if
 * the substring of 'str1' is found, respectively, to be less than, to match,
 * or be greater than the substring of 'str2'.
 *
 * Description: This function compares up to 'num' characters of the strings
 * 'str1' and 'str2'. If a difference is found or'num' characters are compared,
 * the comparison stops.
 */
int str_ncmp(const char *str1, const char *str2, size_t num)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < num; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == num)
		return (0);
	else
		return (-15);
}