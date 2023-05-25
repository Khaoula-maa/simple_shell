#include "shell.h"
/**
 * _strtok - counts separate words in string
 * @str: pointer to s
 * @delim: delimiter
 * Return: number of words
 */
int _strtok(char *str, char delim)
{
	int i, count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != delim && (str[i + 1] == delim || str[i + 1]  ==
					'\t' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}
