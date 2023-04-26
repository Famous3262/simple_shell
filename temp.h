#ifndef TEMP_H
#define TEMP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

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
#define USE_STRING_TOKEN 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* Pointer to an array of pointers to strings called the environment */
extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: a string
 * @next: pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @filename: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from linked list environment
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last executed command
 * @cmd_buf: address of pointer to command buffer
 * @cmd_buf_type: command type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: history line number count
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
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;

/* shell_loop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int loophsh(char **);

/* errors.c */
void put_string(char *);
int eput_char(char);
int put_file_desc(char c, int fd);
int str_fd(char *str, int fd);
int erratoi(char *);
void print_error(info_t *, char *);
int print_dec(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *buf);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, size_t);
char *_strncat(char *, char *, size_t);
char *_strchr(char *, char);

/* string_tok.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* temp_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* mem_free.c */
int bfree(void **);

/* atoi.c */
int inter_mode(info_t *);
int check_delim(char, char *);
int check_alphabet(int);
int s_atoi(char *);

/* help_builtin.c */
int shell_exit(info_t *);
int change_dir(info_t *);
int help(info_t *);
int hist_list(info_t *);
int alias(info_t *);
int print_alias(list_t *);
int set_alias(info_t *, char *);
int onset_alias(info_t *, char *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *get_env(info_t *, const char *);
int print_env(info_t *);
int new_env(info_t *);
int rem_env(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* get_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* free_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists_len.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* replace_vars.c */
int chain_delim(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_vars(info_t *);
int rep_string(char **, char *);
int rep_alias(info_t *);

#endif
