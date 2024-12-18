/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-09 16:46:25 by ysuliman          #+#    #+#             */
/*   Updated: 2024-07-09 16:46:25 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	init_map(t_renderer *renderer);
static int	handle_keys(int keycode, t_renderer *renderer);
static void	set_random_color(t_renderer *renderer);
void		display_string(char *str, int start, t_renderer *renderer);
void		destroy_window(t_renderer *renderer);

int	main(int ac, char **av)
{
	t_renderer	*renderer;
	int			x;

	x = 0;
	renderer = (t_renderer *)malloc(sizeof(t_renderer));
	if (!renderer)
		manage_error("Malloc failed", NULL);
	if (ac != 2 || ft_strlen(av[1]) < 5)
		manage_error("Usage invalid: ./fdf ./maps/...", renderer);
	if (!ft_strnstr(av[1], ".fdf", ft_strlen(av[1])))
		manage_error("Wrong file Input", renderer);
	process_file(av[1], renderer, x);
	init_map(renderer);
	renderer->mlx.init = mlx_init();
	renderer->mlx.win = mlx_new_window(renderer->mlx.init, WIN_WIDTH,
			WIN_HEIGHT, "42_FDF");
	mlx_hook(renderer->mlx.win, 17, 0, close_program, renderer);
	mlx_hook(renderer->mlx.win, 2, 3, handle_keys, renderer);
	mlx_loop_hook(renderer->mlx.init, render, renderer);
	mlx_loop(renderer->mlx.init);
	free(renderer);
	return (0);
}

static void	init_map(t_renderer *renderer)
{
	renderer->map.coordinate_z = 0;
	renderer->map.coordinate_y = 0;
	renderer->map.x_value = 1.00;
	renderer->map.angle_y = cos(M_PI / 3);
	renderer->map.angle_z = renderer->map.angle_y * sin(M_PI / 6);
	if (renderer->map.width > renderer->map.height)
		renderer->map.zoom = ceil((WIN_WIDTH / renderer->map.width)
				+ MAGIC_ZOOM);
	else
		renderer->map.zoom = ceil((WIN_HEIGHT / renderer->map.height)
				+ MAGIC_ZOOM);
	renderer->map.isometric = 1;
	renderer->color.red = 0x4F;
	renderer->color.green = 0x4F;
	renderer->color.blue = 0x4F;
}

static int	handle_keys(int keycode, t_renderer *renderer)
{
	if (keycode == KEY_EXIT)
		close_program(renderer);
	else if (keycode == KEY_RESET)
		init_map(renderer);
	else if (keycode == KEY_COLOR)
		set_random_color(renderer);
	else if (keycode == KEY_UP)
		renderer->map.coordinate_z -= 1;
	else if (keycode == KEY_DOWN)
		renderer->map.coordinate_z += 1;
	else if (keycode == KEY_RIGHT)
		renderer->map.coordinate_y += 1;
	else if (keycode == KEY_LEFT)
		renderer->map.coordinate_y -= 1;
	else if (keycode == KEY_ZOOM_IN)
		renderer->map.zoom += 1;
	else if ((keycode == KEY_ZOOM_OUT) && (renderer->map.zoom > MAX_ZOOM))
		renderer->map.zoom -= 1;
	else if ((keycode == KEY_HEIGHT_UP) && (renderer->map.x_value < MAX_X))
		renderer->map.x_value += 0.25;
	else if ((keycode == KEY_HEIGHT_DOWN) && (renderer->map.x_value > -MAX_X))
		renderer->map.x_value -= 0.25;
	else if (keycode == KEY_PROJECTION)
		toggle_view(renderer);
	return (0);
}

static void	set_random_color(t_renderer *renderer)
{
	renderer->color.red = (rand() % 0x7F);
	renderer->color.green = (rand() % 0x7F);
	renderer->color.blue = (rand() % 0x7F);
}

void	display_string(char *str, int start, t_renderer *renderer)
{
	static int	height;

	if (!height || start)
		height = T_OFFSET;
	height += T_HEIGHT;
	mlx_string_put(renderer->mlx.init, renderer->mlx.win, T_OFFSET, height,
		T_COLOR, str);
}
