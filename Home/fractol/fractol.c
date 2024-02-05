#include "fractol.h"

void clean_f(t_fractal *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->width = 0;
	f->height = 0;
	f->min_real = 0;
	f->max_real = 0;
	f->min_imag = 0;
	f->max_imag = 0;
	f->max_iter = 0;
}

void init_f(t_fractal *f)
{
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->width, f->height, "Fractol");
}

int		key_hook(int keycode, t_fractal *data)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == 53) // 53: ESC tuşu
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int main()
{
	t_fractal f;

	clean_f(&f);
	init_f(&f);

	mlx_key_hook(f.win, key_hook, &f); // key_hook fonksiyonu atanıyor

	mlx_loop(f.mlx);
}