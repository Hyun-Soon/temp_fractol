#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

# define WIDTH 1920
# define HEIGHT 1280
# define MIN_I -2
# define MAX_I 2
# define MIN_R -3
# define MAX_R 3


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

int main()
{
	// void	*mlx_ptr;
	// void	*win_ptr;

	t_vars	vars;
	t_data	image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, 1920, 1080); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

	int color = 0x000000FF;
	int n = 1;
	double	c_r, c_i;
	int temp = -1;
	//MANDELBROT
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			c_r = MIN_R + x * (MAX_R - MIN_R) / WIDTH;
			c_i = MAX_I - y * (MAX_I - MIN_I) / HEIGHT;
			n = check_mandelbrot_set(c_r, c_i);
			if (y >= 500 && y <= 600 && x >= 500 && x <= 600)
				printf("%d\n", n);
			if (n == 100)
				my_mlx_pixel_put(&image, x, y, 0x00000000);
			else
				my_mlx_pixel_put(&image, x, y, color / n);

		}
	}




	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
