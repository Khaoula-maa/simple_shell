
#define shell_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

/**======== Read/Write buffers ========**/
#define buffer_size    1024
#define read_buf_size  1024
#define write_buf_size 1024
#define BUF_FLUSH       -1

/**======== convert_number() ========**/
#define convert_lowercase	1
#define convert_unsigned	2

/**======== error messages ========**/
#define error "Error"
#define wrong "Something went wrong"
#define einval "Invalid argument"
#define enomem "Out of memory"
#define end "exit"

/**======== command chaining  ========**/
#define cmd_norm	0
#define cmd_and		2
#define cmd_or		1
#define cmd_chain	3

/**======= if using system getline()  ========**/
#define use_getline  0
#define use_strtok   0

/**======= history  ========**/
#define hist_file	".simple_shell_history"
#define hit_max    	4096

extern char **environ;

/**======= the initializer  ========**/
#define info_init \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct built_in - list of builtins
 * @bi: The specifier
 * @f: The function associated with printing
 */
typedef struct built_in
{
	char *bi;
	int (*f)();
} builtin_t;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@fname: the program filename
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@environ: custom modified copy of environ from LL env
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 *@linecount_flag: if on count this line of input
 *@env: linked list local copy of environ
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	char *fname;
	char **environ;
	char **cmd_buf;
	int argc;
	int err_num;
	int linecount_flag;
	int env_changed;
	int status;
	int cmd_buf_type;
	int readfd;
	int histcount;
	unsigned int line_count;
	list_t *env;
        list_t *history;
        list_t *alias;
} info_t;

/*====== run_command ======*/
char **path_dirs_array(list_t **env_head);
char *cmd_in_path(char *str, list_t **env_head);
int run_command(char **line, list_t **env_head);

/*====== cmd_line_loop.c ======*/
int cmd_line_loop(char *buffer, char *line, list_t **env_head);

/*====== array_list.c ======*/
int arr_size(char **arr);
list_t *array_to_list(char **array);
char **list_to_array(list_t **head);
void free_array(char **array);

/*======  _getline.c ====== */
int _getline(char *input, int size);
int exit_shell(char **line_tok);
char *mem_cpy(char *dest, char *src, int n);
void clear_buffer(char *buffer);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*======  lists.c ====== */
size_t list_len(list_t *h);
list_t *get_node(list_t **head, char *str);
list_t *add_node(list_t **head, char *str);
list_t *add_node_end(list_t **head, char *str);
void free_list(list_t *head);

/*======  strings.c ====== */
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

/*====== more_strings ======*/
int _atoi(char *s);
int _strcmp(char *s1, char *s2);
int len_to_char(char *str, char c);
char *_strchr(char *str, char c);

/*====== new_env ======*/
char *var_str(char *name, char *value);
char *_getenv(char *name, list_t **env_head);
int _setenv(char *name, char *value, list_t **env_head);
int _unsetenv(char *name, list_t **env_head);
int delete_node(list_t **head, char *string);

/*====== _strtok.c ======*/
char **strtow(char *str, char delim);
int count_words(char *str, char delim);
int _wrdlen(char *s, char delim);

/*====== _getline.c ======*/
int _getline(char *input, int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int exit_shell(char **line_tok);
void clear_buffer(char *buffer);
char *mem_cpy(char *dest, char *src, int n);

/*===== built_in.c ======*/
int print_env(char **line, list_t **env_head);
int set_env(char **line, list_t **env_head);
int unset_env(char **line, list_t **env_head);
int built_ins(char **input, list_t **env_head);
int exit_bi(char **line);
