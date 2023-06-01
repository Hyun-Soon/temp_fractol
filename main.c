/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:36:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/01 21:07:05 by hyuim            ###   ########.fr       */
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
	draw_fractal(&fractal);
	// TODO :: draw_fractal, draw_mandelbrot, draw_julia
	mlx_loop(mlx.mlx);

// 		  MinilibX의 images를 사용하라는데 어디다 쓰라는건지?
//		  pixel 다 색칠해서 화면을 덮으려면 엄청 많이 반복해야되는건지?


	return 0;
}

void	draw_fractal(t_fractal *fractal)
{
	if (fractal->type == 0)
		draw_mandelbrot();
	else if (fractal->type == 1)
		draw_julia();
	// else if (fractal->type == 2)
	// 	draw_something();
	return ;
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

