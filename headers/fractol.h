/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/31 20:38:25 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# ifndef INITIOAL_COND_X
#  define INITIOAL_COND_X 1.1
# endif

#include "ft_printf.h"
#include <unistd.h>

void	ft_error(const char *err_msg, int fd);

#endif
