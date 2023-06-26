/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:36:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/26 14:31:45 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_mlx		mlx;

	if (!check_input(argc, argv, &mlx))
		ft_error("Wrong input error.\nFractal list [mandelbrot, julia, burning ship]", 2);
	if (!init_mlx(&mlx))
		ft_error("MLX init error\n", 2);
	draw_fractal(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_mouse_hook(mlx.win, zoom, &mlx);
	mlx_loop(mlx.mlx);
	//mouse zoom, keyboard view, color change
	return 0;
}

int	zoom(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4)
		zoomin(mlx, x, y);
	else if (button == 5)
		zoomout(mlx, x, y);
	// my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);	
	return (0);
}

void	zoomin(t_mlx *mlx, int x, int y)
{
	double	r;
	double	i;

	r = mlx->min_r + x * mlx->r_per_WIDTH;
	i = mlx->max_i - y * mlx->i_per_HEIGHT;
	mlx->max_r = r + mlx->max_r * ZOOMIN;
	mlx->min_r = r - mlx->min_r * ZOOMIN; //-> 이걸 그냥 ZOOMIN으로 줄여버리면 안되고, ZOOMIN 계수에 맞춰서 해당 픽셀의 좌표상 위치가 유지될 수 있도록 계산해서 min_r을 계산해줘야 한다.
	mlx->max_i = i + mlx->max_i * ZOOMIN;
	mlx->min_i = i - mlx->min_i * ZOOMIN;
	mlx->r_per_WIDTH = (mlx->max_r - mlx->min_r) / WIDTH;
	mlx->i_per_HEIGHT = (mlx->max_i - mlx->min_i) / HEIGHT;
	draw_fractal(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}

void	zoomout(t_mlx *mlx, int x, int y)
{
	double	r;
	double	i;

	//이이걸  계계속  계계i산하면서 부호가 바뀌게 되어서 줌인하다가 줌아웃처럼 보이고그런거 아닐까?
	//ex. r = -0.1, min_r = r - (-0.2) = 0.1, max_r = r + 0.1 = 0
	r = mlx->min_r + x * mlx->r_per_WIDTH;
	i = mlx->max_i - y * mlx->i_per_HEIGHT;
	mlx->max_r = r + mlx->max_r * ZOOMOUT;
	mlx->min_r = r - fabs(mlx->min_r) * ZOOMOUT;
	mlx->max_i = i + mlx->max_i * ZOOMOUT;
	mlx->min_i = i - fabs(mlx->min_i) * ZOOMOUT;
	mlx->r_per_WIDTH = (mlx->max_r - mlx->min_r) / WIDTH;
	mlx->i_per_HEIGHT = (mlx->max_i - mlx->min_i) / HEIGHT;
	draw_fractal(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if(keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
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
		c_i = mlx->max_i - (double)y * mlx->i_per_HEIGHT;
		while (x < WIDTH)
		{
			c_r = mlx->min_r + (double)x * mlx->r_per_WIDTH; 
			n = check_burning_ship_set(c_r, c_i);
			if (n == 100)
				my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			else
				my_mlx_pixel_put(&mlx->img, x, y, color / (n + 1));
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

void	draw_julia(t_mlx *mlx, int x, int y)
{
	int	n;
	int	color;
	double	z_r;
	double	z_i;
	
	color = 0x00123456;
	while (y < HEIGHT)
	{
		z_i = mlx->max_i - (double)y * mlx->i_per_HEIGHT;
		while (x < WIDTH)
		{
			z_r = mlx->min_r + (double)x * mlx->r_per_WIDTH;
			n = check_julia_set(z_r, z_i, mlx);
			if (n < 100)
				my_mlx_pixel_put(&mlx->img, x, y, color / (n + 1));
			x++;
		}
		x = 0;
		y++;
	}
}

int	check_julia_set(double z_r, double z_i, t_mlx *mlx)
{
	int		n;
	double	temp;

	n = 0;
	while (n < 100 && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r - z_i * z_i + mlx->fractal.c_r;
		z_i = 2 * temp * z_i + mlx->fractal.c_i;
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
		c_i = mlx->max_i - (double)y * mlx->i_per_HEIGHT;
		while (x < WIDTH)
		{
			c_r = mlx->min_r + (double)x * mlx->r_per_WIDTH; 
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

void	draw_fractal(t_mlx *mlx)
{
	if (mlx->fractal.type == 0)
		draw_mandelbrot(mlx, 0, 0);
	else if (mlx->fractal.type == 1)
		draw_julia(mlx, 0, 0);
	else if (mlx->fractal.type == 2)
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
	mlx->min_r = -2;
	mlx->max_r = 2;
	mlx->min_i = -2;
	mlx->max_i = 2;
	mlx->r_per_WIDTH = (mlx->max_r - mlx->min_r) / WIDTH;
	mlx->i_per_HEIGHT = (mlx->max_i - mlx->min_i) / HEIGHT;
	return(1);
}

int	check_input(int argc, char *argv[], t_mlx *mlx)
{
	char	*mandelbrot;
	char	*julia;
	char	*burning_ship;

	mandelbrot = "mandelbrot";
	julia = "julia";
	burning_ship = "burning ship";
	if (argc == 2 && !ft_strcmp(mandelbrot, argv[1]))
	{
		mlx->fractal.type = 0;
		return (1);
	}
	else if (argc == 4 && !ft_strcmp(julia, argv[1]))
	{
		mlx->fractal.type = 1;
		mlx->fractal.c_r = fractol_atodb(argv[2]);
		mlx->fractal.c_i = fractol_atodb(argv[3]);
		return (1);
	}
	else if (argc == 3 && !ft_strcmp("burning", argv[1]) && !ft_strcmp("ship", argv[2]))
	{
		mlx->fractal.type = 2;
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