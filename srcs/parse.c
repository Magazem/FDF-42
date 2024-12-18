/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-09 14:10:07 by ysuliman          #+#    #+#             */
/*   Updated: 2024-07-09 14:10:07 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	configure_map(t_renderer *renderer, int x, int y, char *line);
static void	get_map_data(t_renderer *renderer, char *file);
static int	count_values(char *line, t_renderer *renderer);
int			close_program(t_renderer *renderer);

void	process_file(char *file, t_renderer *renderer, int x)
{
	char	*line;
	int		fd;
	int		y;

	get_map_data(renderer, file);
	fd = open(file, O_RDONLY);
	if (!fd)
		manage_error("Open error", renderer);
	renderer->map.values = (int **)malloc(sizeof(int *) * renderer->map.height);
	y = -1;
	line = get_next_line(fd);
	while (line && ++y != renderer->map.height)
	{
		renderer->map.values[y] = (int *)malloc(sizeof(int *)
				* renderer->map.width);
		if (!renderer->map.values[y])
			manage_error("Malloc error", renderer);
		configure_map(renderer, x, y, line);
		x = 0;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		manage_error("Close error", renderer);
}

static void	configure_map(t_renderer *renderer, int x, int y, char *line)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if (split)
	{
		i = 0;
		while (split[i] && (x != renderer->map.width))
		{
			renderer->map.values[y][x] = ft_atoi(split[i++]);
			x++;
		}
	}
	x = 0;
	split_free(split);
}

static void	get_map_data(t_renderer *renderer, char *file)
{
	char	*line;
	int		fd;
	int		len;
	int		cols;
	int		rows;

	rows = 0;
	cols = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		manage_error("Open error", renderer);
	line = get_next_line(fd);
	if (!line)
		manage_error("empty file", renderer);
	while (line && *line != '\0')
	{
		len = count_values(line, renderer);
		validate(&cols, &rows, &len, renderer);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		manage_error("Close error", renderer);
	renderer->map.width = cols;
	renderer->map.height = rows;
}

static int	count_values(char *line, t_renderer *renderer)
{
	int		len;
	char	*start_line;

	len = 0;
	start_line = line;
	while (*line)
	{
		if (ft_isdigit(*line))
		{
			len += 1;
			while (ft_isdigit(*line))
				line += 1;
		}
		else if (*line == ' ' || *line == '-')
			line += 1;
		else if (*line == '\n' || *line == EOF)
			break ;
		else
		{
			gnl_clean();
			free(start_line);
			manage_error("Invalid characters or read error", renderer);
		}
	}
	return (len);
}

int	close_program(t_renderer *renderer)
{
	int	i;

	if (renderer->map.values)
	{
		i = 0;
		while (i < renderer->map.height)
		{
			if (renderer->map.values[i])
				free(renderer->map.values[i]);
			i++;
		}
		free(renderer->map.values);
	}
	if (renderer->mlx.win)
		mlx_destroy_window(renderer->mlx.init, renderer->mlx.win);
	if (renderer->mlx.init)
		mlx_destroy_display(renderer->mlx.init);
	if (renderer->mlx.init)
		free(renderer->mlx.init);
	free(renderer);
	exit(0);
}
