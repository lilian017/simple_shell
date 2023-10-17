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
 */
typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char **sep_buff;
	int sep_buff_kind;
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

#endif



