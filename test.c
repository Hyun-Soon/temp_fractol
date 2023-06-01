#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//TODO :: 프랙탈 x, y 계산하고 화면이랑 비율 조정 어떻게 했는지?
//  	  예쁘게 어떻게 꾸미는지?
// 		  MinilibX의 images를 사용하라는데 어디다 쓰라는건지?
//		  pixel 다 색칠해서 화면을 덮으려면 엄청 많이 반복해야되는건지?

//이미지의 정보를 나타내는 변수를 저장한 구조체
typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_complex_num
{
	double	r;
	double	i;
}				t_complex_num;

//원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	multi_cpn(t_complex_num *a, t_complex_num *b, t_complex_num *ret)
{
	ret->r = a->r * b->r + (-1) * (a->i * b->i);
	ret->i = a->r * b->i + a->i * b->r;
}

int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int mousecode, t_vars *vars)
{
	if (mousecode == 4)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}

	return (0);
}

int main()
{
	// void	*mlx_ptr;
	// void	*win_ptr;

	t_vars	vars;
	t_data	image;

	double	mid_x = 1920/2.0f;
	double	mid_y = 1080/2.0f;
	t_complex_num cpn;
	t_complex_num next_cpn;
	t_complex_num constant;
	constant.r = -0.8; //나중에 init()으로 묶자.
	constant.i = 0.1;
	cpn.r = 0;
	cpn.i = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, 1920, 1080); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당



	// for (int x = 0 ; x < 1920 ; x++)
	// {
	// 	for (int y = 0 ; y < 1080 ; y++)
	// 	{
	// 		//CIRCLE
	// 		// if (sqrt(pow(fabs(y - mid_y), 2) + pow(fabs(x - mid_x), 2)) <= 100)
	// 		// 	my_mlx_pixel_put(&image, x, y, 0x000FFF00);
	// 	}
	// }

	//MANDELBROT
	printf("mid_x : %f, mid_y : %f\n", mid_x, mid_y);
	int iteration = 0;
	int color = 0x000000FF;
	while (iteration < 50)
	{
		if (iteration == 16 || iteration == 32)
			color <<= 8;
		if (fabs(cpn.r) > 2 || fabs(cpn.i) > 2)
			break;
		my_mlx_pixel_put(&image, cpn.r * 1920 + mid_x, cpn.i * 1080 + mid_y, color); //아래랑 이거랑 왜 작은 집합부분이 위치가 다르지??
		//my_mlx_pixel_put(&image, cpn.r * 640 + mid_x, cpn.i * 360 + mid_y, 0x000FFF00);
		printf("%f : %f\n", cpn.r, cpn.i);
		multi_cpn(&cpn, &cpn, &next_cpn);
		cpn.r = next_cpn.r + constant.r;
		cpn.i = next_cpn.i + constant.i;
		iteration++;
	}




	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
