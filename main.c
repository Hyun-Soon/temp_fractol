/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:36:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/02 17:37:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include "mlx.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	//argv -> file name / fractal name
	t_mlx		mlx;
	t_fractal	fractal;

	if (argc != 2)
		ft_error("Wrong arguments! Plz enter only fractal type.\n", 2);
	if (!check_type(argv[1], &fractal))
		ft_error("Wrong fractal type.\nFractal list {mandelbrot, julia, ???}", 2);
	if (!init_mlx(&mlx))
		ft_error("MLX init error\n", 2);
	init_fractal(&fractal);
	draw_fractal(&mlx, &fractal);
	// TODO :: draw_fractal, draw_mandelbrot, draw_julia
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);


	return 0;
}

int	check_mandelbrot_set(double c_r, double c_i)
{
	int		n;
	int		temp;
	double	z_r;
	double	z_i;

	n = 0;
	z_r = 0;
	z_i = 0;
	while (n < 100 && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r + (-1) * z_i * z_i + c_r;
		z_i = 2 * temp * temp + c_i;
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

void	draw_mandelbrot(t_mlx *mlx)
{
	int		n;
	int		color;
	double	c_r;
	double	c_i;
	
	color = 0x00123456;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			c_r = MIN_R + x * (MAX_R - MIN_R) / WIDTH;
			c_i = MAX_I - y * (MAX_I - MIN_I) / HEIGHT;
			n = check_mandelbrot_set(c_r, c_i);
			if (n == 100)
				my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			else
				my_mlx_pixel_put(&mlx->img, x, y, color / n);
			
		}
	}
}

void	draw_fractal(t_mlx *mlx, t_fractal *fractal)
{
	if (fractal->type == 0)
		draw_mandelbrot(mlx);
	// else if (fractal->type == 1)
	// 	draw_julia();
	// else if (fractal->type == 2)
	// 	draw_something();
	//여여기기서  type number가 잘못된 에러는 없을듯
	return ;
}

void	init_fractal(t_fractal *fractal)
{
	fractal->min_i = MIN_I;
	fractal->max_i = MAX_I;
	fractal->min_r = MIN_R;
	fractal->max_r = MAX_R;
}


int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1280, "Fractal");
	if (!mlx->win)
		return (0);
	mlx->img.img = mlx_new_image(mlx->mlx, 1920, 1280);
	if (!mlx->img.img)
		return (0);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
		&mlx->img.line_length, &mlx->img.endian);
	return(1);
}

int	check_type(char *type, t_fractal *fractal)
{
	char	*mandelbrot;
	char	*julia;
	int		inp_len;

	inp_len = ft_strlen(type);
	if (inp_len != 10 && inp_len != 5)
		return (0);
	mandelbrot = "mandelbrot";
	julia = "julia";
	if (!ft_strncmp(mandelbrot, type, 10) || !ft_strncmp(julia, type, 5))
	{
		if (inp_len == 10)
			fractal->type = 0;
		else if (inp_len == 5)
			fractal->type = 1;
		//else for new fractal
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

