#include "shell.h"

/**
 * input_buf -chaincommand buffer
 * @info: struct parameter
 * @buf: buffer address
 * @len: addresses of length var
 * Return: bytes read
 */

ssize_t input_buf(info_s *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);

#else
		r = _getline(info, buf, &len_p);
#endif 
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->lc_flag = 1;
			handle_comments(*buf);
			update_history(info, *buf, info->hist_lines++);
			{
				*len = r;
				info->sep_buff = buf;
			}
		}
	}
	return (r);
}

/**
 *get_input - gets a line
 *@info: struct parameter
 *Return: bytes read
 */
ssize_t get_input(info_s *info)
{
	static char *buf;
	static size_t i,j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(NEG_ONE);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->sep_buff_kind = REG_FLAG;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/***
 * read_buf - reads a buffer
 * @info: struct parameter
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(info_s *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r =read(info->fd_read, buf, BUFFER_SIZE_READ);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - next line of input from stdin
 * @info: struct parameter
 * @ptr: address of pointer to buffer, allocated NULL
 * @length: size of the buffer
 * Return: size
 */
int _getline(info_s *info, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE_READ];
	static size_t i, len;
	size-t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf):len;
	new_= = realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - 1 +1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * handle_sight - blocks control copy
 * @sig_num: sign. no.
 * Return: void
 */
void handle_sigint(_attribute_((used)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(NEG_ONE);
}
