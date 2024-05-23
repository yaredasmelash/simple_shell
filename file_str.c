#include "main.h"
/**
 * str_spn - Calculates the length of the initial segment of a string
 * consisting of only characters in a specified set.
 * @str: Pointer to the string to be checked.
 * @accept: Pointer to the set of characters to be searched for.
 *
 * Return: The number of bytes in the initial segment of 'str' consisting only
 * of characters found in 'accept'.
 *
 * Description: This function calculates the length (in bytes) of the initial
 * segment of the string 'str' consisting only of characters that are present
 * in the set specified by 'accept'. The search stops when a character not
 * found in 'accept' is encountered.
 */
int str_spn(char *str, char *accept)
{
	int byt = 0;
	int ind;

	while (*str)
	{
		for (ind = 0; accept[ind]; ind++)
		{
			if (*str == accept[ind])
			{
				byt++;
				break;
			}
		}
		str++;
	}
	return (byt);
}
/**
 * str_len - Calculates the length of a string.
 * @str: Pointer to the input string.
 *
 * Return: Length of the string (excluding the null terminator).
 *
 * Description: This function calculates the length of a string by iterating
 * through the characters until the null terminator is encountered.If the input
 * string is NULL, it returns 0.
 */
int str_len(const char *str)
{
	int len = 0;

	if (!str)
		return (len);
	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * str_cmp - Compares two strings.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 *
 * Return: An integer less than, equal to, or greater than zero if
 * 'str1' is found, respectively, to be less than, to match, or be greater
 * than 'str2'.
 *
 * Description: This function compares the strings 'str1' and 'str2'
 * character by character until a difference is found or the end of both
 * strings is reached.
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * str_ncat - Concatenates n characters from the source string to the end
 *            of the destination string.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 * @num: Maximum number of characters to concatenate.
 *
 * Return: Pointer to the destination buffer.
 *
 * Description: This function concatenates up to 'num' characters from the
 * source string to the end of the destination string. It assumes that the
 * destination buffer has sufficient space to accommodate the concatenation.
 */
char *str_ncat(char *dest, const char *src, size_t num)
{
	size_t d_len = str_len(dest);
	size_t i;

	for (i = 0; i < num && src[i] != '\0'; i++)
		dest[d_len + i] = src[i];
	dest[d_len + i] = '\0';

	return (dest);
}