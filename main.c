#include "ft_printf.h"
#include "fractol.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	//argv -> file name / fractal name / param1 / param2
	if (argc != 4)
		ft_error("wrong arguments! plz enter 4 arguments.\n", 2);
	(void)argv;
	//check_fractal_type();


//TODO :: 프랙탈 x, y 계산하고 화면이랑 비율 조정 어떻게 했는지?
//  	  예쁘게 어떻게 꾸미는지?
// 		  MinilibX의 images를 사용하라는데 어디다 쓰라는건지?
//		  pixel 다 색칠해서 화면을 덮으려면 엄청 많이 반복해야되는건지?


	return 0;
}



void	ft_error(const char *err_msg, int fd)
{
	write(fd, err_msg, ft_strlen(err_msg));
	write(fd, "\n", 1);
	exit(0);
}

