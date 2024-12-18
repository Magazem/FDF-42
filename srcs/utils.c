/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-09 14:10:07 by ysuliman          #+#    #+#             */
/*   Updated: 2024-07-09 14:10:07 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	manage_error(char *message, t_renderer *renderer)
{
	free(renderer);
	ft_putendl_fd(message, 1);
	exit(0);
}

void	validate(int *cols, int *rows, int *len, t_renderer *renderer)
{
	if (*len > *cols)
		*cols = *len;
	if (*cols == *len)
		*rows += 1;
	else
		manage_error("Not a valid file", renderer);
}

void	cleanup(void **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i]);
}

void	toggle_view(t_renderer *renderer)
{
	if (renderer->map.isometric++ % 2)
		renderer->map.angle_z *= 0.2;
	else
		renderer->map.angle_z *= 5;
}

void	display_text(t_renderer *renderer)
{
	display_string("Controls:", 1, renderer);
	display_string("W/A/S/D - Move", 0, renderer);
	display_string("J/K - Zoom", 0, renderer);
	display_string("U/I - Shift Heights", 0, renderer);
	display_string("Space - Change projection", 0, renderer);
	display_string("ESC - Exit", 0, renderer);
}
