#include "shell.h"

/**
<<<<<<< HEAD
 * main - Entry point to the shell program
 * Return: Always returns 0 on success
 */
int main(void)
{
  char *input_buffer, *input_line;
  list_t *env_list_head;
  int return_value;

   /** Allocate memory for the input buffer*/
  input_buffer = malloc(sizeof(char) * buffer_size);
  if (input_buffer == NULL) {
  /* If the allocation failed, return 1 to indicate an error */
    return 1;
  }

  /* Initialize variables */
  input_line = NULL;
  env_list_head = array_to_list(environ);

  /* Call the main loop of the shell program */
  return_value = cmd_line_loop(input_buffer, input_line, &env_list_head);

  /* Free memory allocated for the environment list and input buffer */
  free_list(env_list_head);
  free(input_buffer);

  /* Return the return value of the main loop */
  return return_value;
=======
 * main - program entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
>>>>>>> refs/remotes/origin/master
}
