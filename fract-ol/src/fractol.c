/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:01:15 by abostano          #+#    #+#             */
/*   Updated: 2024/02/06 20:10:45 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void clean_f(t_fractal *f)
{
    f->id = -1;
	f->mlx = NULL;
	f->win = NULL;
	f->width = 800;
    f->height = 600;
    f->min_real = -2.0;
    f->max_real = 2.0;
    f->min_imag = -1.5;
    f->max_imag = 1.5;
    f->max_iter = 100;
}

void init_f(t_fractal *f)
{
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->width, f->height, "Fractol");
    f->img = mlx_new_image(f->mlx, f->width, f->height);
    f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_len, &f->endian);
}

int main(int argc, char **argv)
{
	t_fractal f;
    t_complex c;

    c.real = -0.7;
    c.imag = 0.27015;

    if (argc != 2)
    {
        ft_printf("Usage: ./fractol [mandelbrot/julia]\n");
        return (1);
    }
	clean_f(&f);
	init_f(&f);
    mlx_mouse_hook(f.win, mouse_scroll, &f); // Mouse tekerleği hareketini yakalama
    define_set(argv, f, c);
	mlx_key_hook(f.win, key_hook, &f);// key_hook fonksiyonu atanıyor
    mlx_put_image_to_window(f.mlx, f.win, f.img, 0, 0);
	mlx_loop(f.mlx);
    return (0);
}