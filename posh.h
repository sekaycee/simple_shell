#ifndef _POSH_H_
#define _POSH_H_

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

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
 * @next: point to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contain pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
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
 *struct builtin - contain a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;


/* shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int find_builtin(info_t *);
int posh(info_t *, char **);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* puts.c */
void _puts(char *);
void _eputs(char *);
int _eputchar(char);
int _putfd(char, int);
int _putsfd(char *, int);

/* 0-string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strdup(const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);

/* 1-string.c */
int _putchar(char);
char *starts_with(const char *, const char *);

/* 2-string.c */
char *_strchr(char *, char);
char **strtow2(char *, char);
char **strtow(char *, char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* memory.c */
int bfree(void **);
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* utils.c */
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

/* errors.c */
int _erratoi(char *);
int print_d(int, int);
void remove_comments(char *);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);

/* builtin.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);
int _myalias(info_t *);
int _myhistory(info_t *);

/* 2-getters.c */
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* 1-getters.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* environ.c */
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);

/* 0-getters.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
int read_history(info_t *);
int write_history(info_t *);
int renumber_history(info_t *);
char *get_history_file(info_t *);
int build_history_list(info_t *, char *, int);

/* 0-lists.c */
void free_list(list_t **);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node_end(list_t **, const char *, int);

/* 1-lists.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* checks.c */
int replace_vars(info_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif /* _POSH_H_ */
