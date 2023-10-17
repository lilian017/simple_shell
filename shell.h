#ifndef SHELL_H
#define SHELL_H

#include <fct1.h>
#include <limits.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define MAX_WORD_COUNT 100
#define NEG_ONE -1
#define REG_FLAG 0
#define OR_FLAG 1
#define AND_FLAG 2
#define CHAIN_FLAG 3
#define SET_INFO
	{	
		NULL, NULL, NULL, 0,0,0,0,
		NULL, NULL, NULL, NULL,
		0, 0, NULL, 0,0,0
	}
extern char **environ;

/**struct ListNode - singly linked list
 * @n: numbers in the field
 * @str: string
 * @next: points to the node that follows
 */
typedef struct LIstNode
{
	int n;
	char *str;
	struct ListNode *next;
}list_s;

/**
 * struct InfoNode - has simulated arguments
 * @arg: argument is held here
 * @argv: array of strings from th eargument
 * @path: path for the current command
 * @arg: arguments
 * @sep_buff: address of pointer for chain
 * @sep_buff_kind: command buffer
 * @status: shows status of last command
 * @fd_read: file descriptitor that reads input
 * @lc_flag: flag for line input
 * @env: environment vars. in a linked list
 * @environ: environ
 * @lines: errors
 * @error_code: exits the error
 * @prog_name: file name
 * @alias: command alias node
 * @hist_lines: lines contructed in history
 * @history: command history node
 */

typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char **sep_buff;
	int sep_buff_kind;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_s *env;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;
	list_s *history;
	int fd_read;
	int hist_lines;

}info_s;

/**
 * struct builtin - has built in strings and such like fncts
 * @type: builtin command flag
 * @func: function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_s *);
} builtin_commands;

int shell_prgm(info_s *info, char **av);
int write char(char c, int fd);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _putchar(char);
char *starts_with(const char *, const char *);
char *check_fip(info_s, *info, char *pathstr, char *cmd);
char *dupli_chars(char *pathstr, int start, int stop);
bool exec_command(info_s *info, char *path);
bool chain_del(infor_s *info, char *buf, size_t *p);
void chain_check(infor_s *info,char *buf, size_t *p, size_t i, size_t len);
int change_var(info_s *info);
int replc_string(char **old, char *new);
void create_process(info_s *info);
int handle_builtin(info_s * info);
void check_command(info_s *info);
int main(int argc, char **argv);
int write_chars(char *str, int fd);
int _isalpha(int);
int _atoi(char *);
int err_num(char *);
int handle_exit(info_s *);
int handle_cd(info_s *);
int handle_help(info_s *);
int handle_history(info_s *);
int handle_alias(info_s *);
int _getline(info_s *, char **, size_t *);
int _printenv(info_s *);
int check_setenv(info_s *);
int check_unsetenv(info_s *);
int _unsetenv(info_s *,char *);
void puts_err(char *);
char *strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_memset(char *, char, unsigned int);
list_s *add_node_start(list_s **head, const char *str, int num);
list_s *node_str_start(list_s *,char *, char);
list_s *node_str_start(list_s *,char *, char);
size_t print_list_str(const list_s*);
size_t listlen(const list_s *);
ssize_t get_input(info_s *);
ssize_t get _node_index(list_s *, list_s *);

#endif



