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
=======
#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
>>>>>>> refs/remotes/origin/master
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
=======
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c (FILE DELETED AND FUNCTION NOT USED)*/
/* int loophsh(char **); */

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
