#include "shell.h"

/**
 * get_environ- returns an array of string
 * @info: structure that maintains function
 * Return: environment variables as string arrays
 */
char **get_environ(info_s *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_vector(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/** _setenv - changes var
 * @info: structure that contains
 * @var: name of var
 * Return: 0 on success otherwise 1
 */

int _setenv(info_s *info, char *var, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
/**
 * _unsetenv - a function that cancels environment variable
 * @info: structural variables are stored here
 * @var: var to be removed
 * Return: 1 on success and 0 on failure
 */
int _unsetenv(info_s *info, char *var)
{
	list_s *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var)return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env),index);

			index = 0;
			node = info->env;
			;
		}

		node = node->next;
		index++;
	}
	return (info->env_changed);
}
