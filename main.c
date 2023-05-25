#include "shell.h"

/**
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
}
