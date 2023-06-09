#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
char *get_location(char *cmd);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);
int fork_exec(char **args, char **front);
void free_list(list_t *head);
char *get_pid(void);
void free_args(char **args, char **front);
char *get_env_value(char *beginning, int len);

char *_itoa(int num);
void sig_handlr(int sig);

/* Input Helpers */
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *last_exe);
char *gt_arg(char *line, int *last_exe);
int call_args(char **args, char **front, int *last_exe);
int run_args(char **args, char **front, int *last_exe);
int handle_args(int *last_exe);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *cmd))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_hlp(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);
int num_len(int num);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void hlp_all(void);
void hlp_alias(void);
void hlp_cd(void);
void hlp_exit(void);
void hlp_hlp(void);
void hlp_env(void);
void hlp_setenv(void);
void hlp_unsetenv(void);
void hlp_history(void);

void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);

int proc_file_commands(char *file_path, int *last_exe);
int cant_open(char *file_path);

#endif /* _SHELL_H_ */
