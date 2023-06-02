/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/02 17:25:05 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1920
# define HEIGHT 1280
# define MIN_I -2
# define MAX_I 2
# define MIN_R -3
# define MAX_R 3

# include <unistd.h>

typedef struct	s_fractal
{
    int	type;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
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
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;



void	ft_error(const char *err_msg, int fd);
int		check_type(char *type, t_fractal *fractal);
int		init_mlx(t_mlx *mlx);
void	init_fractal(t_fractal *fractal);
void	draw_fractal(t_mlx *mlx, t_fractal *fractal);
void	draw_mandelbrot(t_mlx *mlx);

#endif
