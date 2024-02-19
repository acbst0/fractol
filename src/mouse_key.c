/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:16:22 by abostano          #+#    #+#             */
/*   Updated: 2024/02/19 14:19:00 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_scroll(int button, int x, int y, t_fractal *fractal)
{
	double	zoom_factor;

	if (button == 4)
		zoom_factor = 1.1;
	else
		zoom_factor = 0.9;
	mouse_scroll_two(zoom_factor, x, y, fractal);
	mlx_clear_window(fractal->mlx, fractal->win);
	if (fractal->id == 1)
		draw_julia(fractal, fractal->c);
	else if (fractal->id == 0)
		draw_mandelbrot(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

void	mouse_scroll_two(double zoom_factor, int x, int y, t_fractal *fractal)
{
	double	center_real;
	double	center_imag;

	center_real = fractal->min_real + x * (fractal->max_real
			- fractal->min_real) / fractal->width;
	center_imag = fractal->min_imag + y * (fractal->max_imag
			- fractal->min_imag) / fractal->height;
	fractal->min_real = center_real - (center_real
			- fractal->min_real) / zoom_factor;
	fractal->max_real = center_real + (fractal->max_real
			- center_real) / zoom_factor;
	fractal->min_imag = center_imag - (center_imag
			- fractal->min_imag) / zoom_factor;
	fractal->max_imag = center_imag + (fractal->max_imag
			- center_imag) / zoom_factor;
}

int	key_hook(int keycode, t_fractal *data)
{
	ft_printf("Keycode: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int	close_window(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->win);
	exit(EXIT_SUCCESS);
	return (0);
}
