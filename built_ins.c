#include "shell.h"
/**
 * built_ins - checks if command is a built-in
 * @input: tokenized line from the command line
 * @env_head: pointer to environ list
 * @return 0 if the command was executed successfully,
 * 1 if there was an error, or -1 if the command was not found.
 */
int built_ins(char **input, list_t **env_head)
{
	char *name;
	int (*function)(char **input, list_t **env_head);
	builtins[] = {
		{"exit", exit_bi},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};
	int i = 0, result = -1;
	list_t *tmp = *env_head;
	
	if (input == NULL) {
		perror("built_ins");
		return 1;
	}
    i = 0;
    while ((builtins + i)->bi != NULL)
    {
	    if (_strcmp(input[0], (builtins + i)->bi) == 0)
	    {
		    if (_strcmp(input[0], END) == 0)
		    {
			    result =(builtins + i)->function(input);
		    } else {
                result =(builtins + i)->function(input, &tmp);
		}
            break;
        }
        i++;
    }
    return result;
}
/**
 * exit_bi - exits shell with given status
 * @line: tokenized line from command line
 * Return: 0 on success, 1 on error
 */
int exit_bi(char **line)
{
	int argc = arr_size(line);
    if (argc > 2) {
        _strprint("Failed: Command syntax: exit statusn");
        return 1;
    } else if (argc == 2) {
        int status = _atoi(line[1]);
        return status;
    } else {
        return 0;
    }
}
/**
 * print_env - prints current environ
 * @line: tokenized line from command line
 * @env_head: pointer to environ list
 * Return: 0 on success, 1 on error
 */
int print_env(char **line, list_t **env_head)
{
	int size;
	list_t *tmp;
	tmp = *env_head;
	size = arr_size(line);
	if (size > 1)
	{
		_strprint("Failed: Command syntax: env\n");
		return (1);
	}
	print_list(tmp);
	return (0);
}
/**
 * set_env - initializes a new environment variable, or modify an existing one
 * @line: tokenized line from command line
 * @env_head: pointer to environ list
 * Return: 0 on success, 1 on error
 */
int set_env(char **line, list_t **env_head)
{
    int size = arr_size(line);
    int retval;
    list_t *tmp = *env_head;
    if (size != 3) {
        _strprint("Failed: Command syntax: setenv VARIABLE VALUE\n");
        return 1;
    }
    variable.
    result = _setenv(line[1], line[2], &tmp);
    return result;
}
