/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-14 18:33:03 by ysuliman          #+#    #+#             */
/*   Updated: 2024-11-14 18:33:03 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}			t_mlx;

typedef struct s_image
{
	char	*data;
	int		size;
	int		endian;
	int		bpp;
}			t_image;

typedef struct s_map
{
	int		width;
	int		height;
	int		**values;
	int		coordinate_y;
	int		coordinate_z;
	int		y0;
	int		y1;
	int		z0;
	int		z1;
	int		zoom;
	int		isometric;
	double	x_value;
	double	angle_y;
	double	angle_z;
}			t_map;

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}			t_color;

typedef struct s_renderer
{
	t_mlx	mlx;
	t_map	map;
	t_image	image;
	t_color	color;
}			t_renderer;

#endif