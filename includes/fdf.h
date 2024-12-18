/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-14 16:27:14 by ysuliman          #+#    #+#             */
/*   Updated: 2024-11-14 16:27:14 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "struct.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# define BUFFER_SIZE 42
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define KEY_PROJECTION 0x20
# define KEY_EXIT 0xff1b
# define KEY_RESET 0x72
# define KEY_COLOR 0x74
# define KEY_LEFT 0x61
# define KEY_RIGHT 0x64
# define KEY_DOWN 0x73
# define KEY_UP 0x77
# define KEY_ZOOM_IN 0x6a
# define KEY_ZOOM_OUT 0x6b
# define KEY_HEIGHT_UP 0x75
# define KEY_HEIGHT_DOWN 0x69
# define MAX_X 10
# define MAX_ZOOM 5
# define MAGIC_ZOOM 2
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define T_OFFSET 50
# define T_COLOR 0x00ffff
# define T_HEIGHT 17

char	*get_next_line(int fd);
void	gnl_clean(void);
void	process_file(char *file, t_renderer *renderer, int x);
void	manage_error(char *message, t_renderer *renderer);
void	validate(int *cols, int *rows, int *len, t_renderer *renderer);
void	cleanup(void **str);
void	toggle_view(t_renderer *renderer);
int		initialize(int ac, char **av);
int		render(t_renderer *renderer);
void	display_text(t_renderer *renderer);
void	display_string(char *str, int start, t_renderer *renderer);
int		close_program(t_renderer *renderer);

#endif