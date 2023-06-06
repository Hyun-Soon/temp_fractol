/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:36:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/06 20:51:50 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	//argv -> file name / fractal name
	t_mlx		mlx;
	t_fractal	fractal;

	if (!check_input(argc, argv, &fractal))
		ft_error("Wrong input error.\nFractal list [mandelbrot, julia, ???]", 2);
	if (!init_mlx(&mlx))
		ft_error("MLX init error\n", 2);
	draw_fractal(&mlx, &fractal);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return 0;
}

void	draw_burning_ship(t_mlx *mlx, int x, int y)
{
	int		n;
	int		color;
	double	c_r;
	double	c_i;

	color = 0x00123456;
	while (y < HEIGHT)
	{
		c_i = MAX_I - (double)y * (MAX_I - MIN_I) / HEIGHT;
		while (x < WIDTH)
		{
			c_r = MIN_R + (double)x * (MAX_R - MIN_R) / WIDTH; 
			n = check_burning_ship_set(c_r, c_i);
			if (n == 100)
				my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			else
				my_mlx_pixel_put(&mlx->img, x, y, color / n);
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}

int	check_burning_ship_set(double c_r, double c_i)
{
	int		n;
	double	z_r;
	double	z_i;
	double	temp;

	n = 0;
	z_r = 0;
	z_i = 0;
	while (n < 100 && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * fabs(temp * z_i) + c_i;
		n++;
	}
	return (n);
}


int	check_mandelbrot_set(double c_r, double c_i)
{
	int		n;
	double	temp;
	double	z_r;
	double	z_i;

	n = 0;
	z_r = 0;
	z_i = 0;
	while (n < 100 && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2.0 * temp * z_i + c_i;
		n++;
	}
	return (n);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_julia(t_mlx *mlx, t_fractal *fractal, int x, int y)
{
	int	n;
	int	color;
	double	z_r;
	double	z_i;
	
	color = 0x00123456;
	while (y < HEIGHT)
	{
		z_i = MAX_I - (double)y * (MAX_I - MIN_I) / HEIGHT;
		while (x < WIDTH)
		{
			z_r = MIN_R + (double)x * (MAX_R - MIN_R) / WIDTH;
			n = check_julia_set(z_r, z_i, fractal);
			if (n < 100)
				my_mlx_pixel_put(&mlx->img, x, y, color / (n + 1));
			x++;
		}
		x = 0;
		y++;
	}
}

int	check_julia_set(double z_r, double z_i, t_fractal *fractal)
{
	int		n;
	double	temp;

	n = 0;
	while (n < 100 && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r - z_i * z_i + fractal->c_r;
		z_i = 2 * temp * z_i + fractal->c_i;
		n++;
	}
	return (n);
}

void	draw_mandelbrot(t_mlx *mlx, int x, int y)
{
	int		n;
	int		color;
	double	c_r;
	double	c_i;

	color = 0x00123456;
	while (y < HEIGHT)
	{
		c_i = MAX_I - (double)y * (MAX_I - MIN_I) / HEIGHT;
		while (x < WIDTH)
		{
			c_r = MIN_R + (double)x * (MAX_R - MIN_R) / WIDTH; 
			n = check_mandelbrot_set(c_r, c_i);
			if (n == 100)
				my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			else
				my_mlx_pixel_put(&mlx->img, x, y, color / n);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_fractal(t_mlx *mlx, t_fractal *fractal)
{
	if (fractal->type == 0)
		draw_mandelbrot(mlx, 0, 0);
	else if (fractal->type == 1)
		draw_julia(mlx, fractal, 0, 0);
	else if (fractal->type == 2)
		draw_burning_ship(mlx, 0, 0);
	return ;
}



int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Fractal");
	if (!mlx->win)
		return (0);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (0);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
		&mlx->img.line_length, &mlx->img.endian);
	return(1);
}

int	check_input(int argc, char *argv[], t_fractal *fractal)
{
	char	*mandelbrot;
	char	*julia;
	char	*burning_ship;

	mandelbrot = "mandelbrot";
	julia = "julia";
	burning_ship = "burning ship";
	if (argc == 2 && !ft_strcmp(mandelbrot, argv[1]))
	{
		fractal->type = 0;
		return (1);
	}
	else if (argc == 4 && !ft_strcmp(julia, argv[1]))
	{
		fractal->type = 1;
		fractal->c_r = fractol_atodb(argv[2]);
		fractal->c_i = fractol_atodb(argv[3]);
		return (1);
	}
	else if (argc == 3 && !ft_strcmp("burning", argv[1]) && !ft_strcmp("ship", argv[2]))
	{
		fractal->type = 2;
		return (1);
	}
	return (0);
}


void	ft_error(const char *err_msg, int fd)
{
	write(fd, err_msg, ft_strlen(err_msg));
	write(fd, "\n", 1);
	exit(1);
}