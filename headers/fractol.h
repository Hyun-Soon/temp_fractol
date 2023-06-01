/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/01 20:39:29 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>

typedef struct	s_fractal
{
    int	type;
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

#endif
