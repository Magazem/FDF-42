/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:34:21 by ysuliman          #+#    #+#             */
/*   Updated: 2024/07/03 16:14:12 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	safe_free(int *byte, char **buffer)
{
	if (*byte == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (*byte);
}

static int	line_process(int *i, char **line, int *remaining, int fd)
{
	int			n;
	int			byte;
	static char	*buffer;

	if (!buffer)
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	n = 0;
	if (*remaining == 0 && fd > 0)
		byte = read(fd, buffer, BUFFER_SIZE);
	else
		byte = *remaining;
	while (n < byte)
	{
		if (buffer[n] == '\n')
		{
			(*line)[(*i)++] = '\n';
			*remaining = byte - n - 1;
			ft_memmove(buffer, buffer + n + 1, *remaining);
			buffer[*remaining] = '\0';
			break ;
		}
		(*line)[(*i)++] = buffer[n++];
		*remaining = 0;
	}
	return (safe_free(&byte, &buffer));
}

char	*get_next_line(int fd)
{
	int			i;
	char		*line;
	static int	remaining = 0;
	int			byte;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(10000000);
	if (!line)
		return (NULL);
	i = 0;
	byte = 1;
	while (byte > 0 && (i == 0 || line[i - 1] != '\n'))
		byte = line_process(&i, &line, &remaining, fd);
	if (i != 0)
	{
		line[i] = '\0';
		result = ft_strdup(line);
		free(line);
		return (result);
	}
	if (line)
		free(line);
	return (NULL);
}

void	gnl_clean(void)
{
	int	remaining;
	int	i;

	i = 0;
	remaining = 0;
	line_process(&i, NULL, &remaining, 0);
}
