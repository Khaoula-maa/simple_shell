#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *string)
	int length = 0;

	if (string == NULL)
		return (0);
	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory, which
 *   contains a copy of the string given as a parameter
 * @string: String to be copied
 *
 * Return: pointer to the array
 */
char *_strdup(char *string)
	{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);
	length = str_len(string) + 1;
	result = malloc(sizeof(char) * length);
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = string[i];
	}
	return (result);
}

/**
 * _strncmp - compares two strings for n amount of chars
 * @string1: String one, or the shorter
 * @string2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 *
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int _strncmp(char *string1, char *string2, int number)
{
	int i;

	if (string1 == NULL && string2 == NULL)
		return (1);
	if (string1 == NULL || string2 == NULL)
		return (0);
	if (number == 0) /* infinite longitud */
	{
		if (str_len(string1) != str_len(string2))
			return (0);
		for (i = 0; string1[i]; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (i = 0; i < number ; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
}

/**
 * str_reverse - reverses a string.
 * @string: pointer to string.
 *
 * Return: void.
 */

void str_reverse(char *string)
{
	int i = 0, length = str_len(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}
/**
 * _strcat -concatenates two strings.
 * @string1: String to be concatenated
 * @string2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *_strcat(char*string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_len(string1);
	if (string2 == NULL)
		string2 = "";
	length2 = str_len(string2);
	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	/* copy of string1 */
	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);
	/* copy of string2 */
	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}
	result[length1] = '\0';
	return (result);
}
