#include "shell.h"

/**
 * exec_command - checks if a file is executable
 * @info: info struct
 * @path: path to the file
 * Return: 1 for true and 0 for false
 */
bool exec_command(info_s *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (true);
	}
	return (false);
}

/** dupli_chars - function that duplicates characters
 * @pathstr: path string
 * @start: index that starts
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dupli_chars(char *pathstr, int start, int stop)
{
	static char buf [1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/** checks_fip - fucntion that finds the comaand in path string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: the command to be found
 * Return: full cmd path
 */
char *check_fip(info_s *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if(!pathstr)
		return (NULL);
	if ((strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (exec_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupli_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if(exec_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = 1;
		}
		i++;
	}
	return (NULL);
}
