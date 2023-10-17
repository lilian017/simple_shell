#include "shell.h"

/**
 * chain_del - tests if the buffer is a chain del
 * @info: parameter
 * @buf: char buffeer
 * @p: address of buffer position
 * Return: 1 if chain del or 0 is not
 */
bool chain_del(infor_s *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = OR_FLAG;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind =AND_FLAG;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->sep_buff_kind = CHAIN_FLAG;
	}
	else
		return (false);
	*p = j;
	return (true);
}

/**
 * chain_check - checks if chaining should be acc. to last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: addresses current position
 * @i: the beginning point of buf
 * @len: length of buffer
 * Return:void
 */
void chain_check(infor_s *info,char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->sep_buff_kind == AND_FLAG)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;

		}
	}
	if (info->sep_buff_kind == OR_FLAG)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * change_var - tokeninzing string is replaced
 * @info: parameter struct
 * Return: 1 on success and 0 on failure
 */
int change_var(info_s *info)
{
	int i = 0;
	list_s *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			;
		if (!_strmcp(info->arv[i], "$?"))
		{
			change_string(&(info->argv[i]);

					_strdup(change_base(info->status, 10, 0)));
			;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),
					_strdup(change_base(getpid(), 10, 0)));
			;
		}
		node = node_str_start(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') +1));
			;
		}
		change_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replc_string - replaces string
 * @old: address of string to be replaced
 * @new: address of new string
 * Return: 1 on success
 */
int replc_string(char **old, char *new)
{
	free(*old);
	*old = new;

	return (1);
}
