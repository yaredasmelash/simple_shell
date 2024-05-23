#ifndef main_h
#define main_h
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define FILE_END -2
#define FILE_EXIT -3

extern char **environ;
char *glo_name;
int glo_hist;

/**
 * struct node - Represents a node in a linked list.
 * @directory: The directory string associated with the node.
 * @next: A pointer to the next node in the linked list.
 *
 * Description: This structure defines a node in a linked list used to
 * store directory information.
 */
typedef struct node
{
	char *directory;
	struct node *next;
} node_t;

/**
 * struct fun_builtin - Represents a built-in function.
 * @b_name: The name of the built-in function.
 * @fun: A pointer to the function implementing the built-in.
 *
 * Description: This structure defines a built-in function, including
 * its name and a pointer to the function that implements it.
 */
typedef struct fun_builtin
{
	char *b_name;
	int (*fun)(char **argv, char **front);
} fun_builtin_t;

/**
 * struct struct_alias - Represents an alias in the shell.
 * @a_name: The name of the alias.
 * @a_value: The value associated with the alias.
 * @next: A pointer to the next alias in the linked list.
 *
 * Description: This structure defines an alias in the shell, including
 * its name, value, and a pointer to the next alias in the linked list.
 */
typedef struct struct_alias
{
	char *a_name;
	char *a_value;
	struct struct_alias *next;
} struct_alias_t;

struct_alias_t *ali;

ssize_t get_line(char **line_pointer, size_t *num, FILE *stream);
void *re_alloc(void *pointer, unsigned int o_size, unsigned int n_size);
char **string_toke(char *str_line, char *del);
char *location_get(char *cmd);
node_t *get_dir_path(char *dir_path);
int fun_execute(char **args, char **front_exec);
void list_free(node_t *head_ptr);
char *fun_itoa(int number);

void line_handler(char **line_ptr, ssize_t read_num);
void rep_var(char **args, int *exeret);
char *args_get(char *line_ptr, int *exeret);
int args_call(char **args, char **fron, int *exeret);
int args_run(char **args, char **fron, int *exeret);
int args_handle(int *exeret);
int args_check(char **args);
void args_free(char **args, char **fron);
char **rep_alia(char **args);

int str_len(const char *str);
char *str_cat(char *dest, const char *src);
char *str_ncat(char *dest, const char *src, size_t num);
char *str_cpy(char *dest, const char *src);
char *str_chr(char *str, char ch);
int str_spn(char *str, char *accept);
int str_cmp(char *str1, char *str2);
int str_ncmp(const char *str1, const char *str2, size_t num);

int (*getfun_built(char *cmd))(char **args, char **fron);
int exit_shell(char **args, char **fron);
int env_shell(char **args, char __attribute__((__unused__)) **fron);
int set_env(char **args, char __attribute__((__unused__)) **front);
int unset_env(char **args, char __attribute__((__unused__)) **fron);
int my_cd(char **args, char __attribute__((__unused__)) **fron);
int my_alias(char **args, char __attribute__((__unused__)) **fron);
int help_shell(char **args, char __attribute__((__unused__)) **fron);

char **env_copy(void);
void env_free(void);
char **env_get(const char *variable);

int err_create(char **args, int error);
char *env_err(char **args);
char *one_err(char **args);
char *exit_err(char **args);
char *cd_err(char **args);
char *syntax_err(char **args);
char *num1_err(char **args);
char *num2_err(char **args);

struct_alias_t *alias_end_add(struct_alias_t **head, char *name, char *value);
void free_list_alias(struct_alias_t *head);
node_t *add_end_node(node_t **head, char *dir);
void list_free(node_t *head);

void all_help(void);
void alias_help(void);
void cd_help(void);
void exit_help(void);
void _help(void);
void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
int len_num(int n);
void alias_print(struct_alias_t *alias);
void lineptr_assign(char **l_ptr, size_t *num, char *buff, size_t i);
char *env_value_get(char *beg, int l);
char *pid_get(void);
void logicalop(char *lineptr, ssize_t *n_len);
ssize_t getnewlen(char *lineptr);
char *dir_path_fill(char *path);
int not_open(char *file_path);
int length_token(char *ptr, char *del);
int token_count(char *ptr, char *del);
void hand_sign(int sgn);
void alias_set(char *varname, char *val);



int file_commands(char *file_path, int *exe_ret);
#endif