/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-09 16:46:25 by ysuliman          #+#    #+#             */
/*   Updated: 2024-07-09 16:46:25 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	plot_row(t_renderer *renderer, int x, int y);
static void	plot_col(t_renderer *renderer, int x, int y);
static void	plot_line(t_renderer *renderer);
static void	set_pixel(t_renderer *renderer, int x, int y, double vector);

int	render(t_renderer *render)
{
	int	x;
	int	y;

	x = -1;
	render->mlx.img = mlx_new_image(render->mlx.init, WIN_WIDTH, WIN_HEIGHT);
	render->image.data = mlx_get_data_addr(render->mlx.img, &render->image.bpp,
			&render->image.size, &render->image.endian);
	while (++x < render->map.height)
	{
		y = -1;
		while (++y < render->map.width)
		{
			render->map.y0 = y;
			render->map.z0 = x;
			if (y + 1 < render->map.width)
				plot_row(render, y, x);
			if (x + 1 < render->map.height)
				plot_col(render, y, x);
		}
	}
	mlx_put_image_to_window(render->mlx.init, render->mlx.win, render->mlx.img,
		0, 0);
	display_text(render);
	mlx_destroy_image(render->mlx.init, render->mlx.img);
	return (0);
}

static void	plot_row(t_renderer *renderer, int x, int y)
{
	int	xt;
	int	yt;

	xt = x - renderer->map.width / 2;
	yt = y - renderer->map.height / 2;
	renderer->map.y0 = renderer->map.angle_y * (xt - yt) * renderer->map.zoom;
	renderer->map.z0 = renderer->map.angle_z * (xt + yt) * renderer->map.zoom;
	renderer->map.z0 -= renderer->map.values[y][x] * renderer->map.x_value;
	renderer->map.y1 = renderer->map.angle_y * ((xt + 1) - yt)
		* renderer->map.zoom;
	renderer->map.z1 = renderer->map.angle_z * ((xt + 1) + yt)
		* renderer->map.zoom;
	renderer->map.z1 -= renderer->map.values[y][x + 1] * renderer->map.x_value;
	renderer->map.y0 += (WIN_WIDTH / 2) + renderer->map.coordinate_y;
	renderer->map.y1 += (WIN_WIDTH / 2) + renderer->map.coordinate_y;
	renderer->map.z0 += (WIN_HEIGHT / 2) + renderer->map.coordinate_z;
	renderer->map.z1 += (WIN_HEIGHT / 2) + renderer->map.coordinate_z;
	plot_line(renderer);
}

static void	plot_col(t_renderer *renderer, int x, int y)
{
	int	xt;
	int	yt;

	xt = x - renderer->map.width / 2;
	yt = y - renderer->map.height / 2;
	renderer->map.y0 = renderer->map.angle_y * (xt - yt) * renderer->map.zoom;
	renderer->map.z0 = renderer->map.angle_z * (xt + yt) * renderer->map.zoom;
	renderer->map.z0 -= renderer->map.values[y][x] * renderer->map.x_value;
	renderer->map.y1 = renderer->map.angle_y * (xt - (yt + 1))
		* renderer->map.zoom;
	renderer->map.z1 = renderer->map.angle_z * (xt + (yt + 1))
		* renderer->map.zoom;
	renderer->map.z1 -= renderer->map.values[y + 1][x] * renderer->map.x_value;
	renderer->map.y0 += (WIN_WIDTH / 2) + renderer->map.coordinate_y;
	renderer->map.y1 += (WIN_WIDTH / 2) + renderer->map.coordinate_y;
	renderer->map.z0 += (WIN_HEIGHT / 2) + renderer->map.coordinate_z;
	renderer->map.z1 += (WIN_HEIGHT / 2) + renderer->map.coordinate_z;
	plot_line(renderer);
}

static void	plot_line(t_renderer *renderer)
{
	double	y;
	double	z;
	double	delta_y;
	double	delta_z;
	double	vector;

	y = renderer->map.y0;
	z = renderer->map.z0;
	delta_y = renderer->map.y1 - renderer->map.y0;
	delta_z = renderer->map.z1 - renderer->map.z0;
	vector = sqrt((pow(delta_y, 2)) + (pow(delta_z, 2)));
	delta_y /= vector;
	delta_z /= vector;
	while (vector > 0)
	{
		set_pixel(renderer, y, z, vector);
		y += delta_y;
		z += delta_z;
		vector -= 1;
	}
}

static void	set_pixel(t_renderer *renderer, int y, int z, double vector)
{
	int	pos;

	if ((y > 0 && z > 0) && (y < WIN_WIDTH && z < WIN_HEIGHT))
	{
		pos = (y * 4) + (z * WIN_WIDTH * 4);
		renderer->image.data[pos] = renderer->color.red + vector;
		renderer->image.data[pos + 1] = renderer->color.green + vector;
		renderer->image.data[pos + 2] = renderer->color.blue + vector;
		renderer->image.data[pos + 3] = 0x7F + vector;
	}
}
