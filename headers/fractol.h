/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/07 17:29:08 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1920
# define HEIGHT 1280
# define ZOOMIN 0.000001
# define ZOOMOUT 1.000001

# include <unistd.h>
# include "mlx.h"
# include <math.h>
# include "../libft/libft.h"


typedef struct	s_fractal
{
	int	type;
	double	c_r;
	double	c_i;
}				t_fractal;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	double		r_per_WIDTH;
	double		i_per_HEIGHT;
	t_img		img;
	t_fractal	fractal;
}				t_mlx;

void	ft_error(const char *err_msg, int fd);
int		check_input(int argc, char *argv[], t_mlx *mlx);
int		init_mlx(t_mlx *mlx);
void	draw_fractal(t_mlx *mlx);
void	draw_mandelbrot(t_mlx *mlx, int x, int y);
int		check_julia_set(double z_r, double z_i, t_mlx *mlx);
void	draw_julia(t_mlx *mlx, int x, int y);
void	draw_burning_ship(t_mlx *mlx, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		check_mandelbrot_set(double c_r, double c_i);
int		check_burning_ship_set(double c_r, double c_i);
int		key_hook(int keycode, t_mlx *mlx);
int		zoom(int button, int x, int y, t_mlx *mlx);
void	zoomin(t_mlx *mlx, int x, int y);
void	zoomout(t_mlx *mlx, int x, int y);


#endif