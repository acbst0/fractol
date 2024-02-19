/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:35 by abostano          #+#    #+#             */
/*   Updated: 2024/02/08 14:07:40 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_mandelbrot(t_fractal *fractal)
{
	int			y;
	t_complex	c;
	t_complex	z;

	y = 0;
	while (y < fractal->height)
	{
		draw_mandelbrot_two(fractal, &c, &z, y);
		y++;
	}
}

void	draw_mandelbrot_two(t_fractal *fractal, t_complex *c,
t_complex *z, int y)
{
	int			x;
	int			iter;
	int			color;

	x = 0;
	while (x < fractal->width)
	{
		c->real = fractal->min_real + x * (fractal->max_real
				- fractal->min_real) / (fractal->width - 1);
		c->imag = fractal->min_imag + y * (fractal->max_imag
				- fractal->min_imag) / (fractal->height - 1);
		z->real = 0;
		z->imag = 0;
		iter = 0;
		while (iter < fractal->max_iter && complex_abs(*z) <= 4)
		{
			*z = complex_add(complex_square(*z), *c);
			iter++;
		}
		set_color(fractal, iter, &color);
		*(unsigned int *)(fractal->addr + (y * fractal->line_len + x
					* (fractal->bpp / 8))) = color;
		x++;
	}
}

void	draw_julia(t_fractal *fractal, t_complex c)
{
	int			y;

	y = 0;
	while (y < fractal->height)
	{
		draw_julia_two(fractal, &c, y);
		y++;
	}
}

void	draw_julia_two(t_fractal *fractal, t_complex *c, int y)
{
	int			x;
	int			iter;
	int			color;
	t_complex	z;

	x = 0;
	while (x < fractal->width)
	{
		z.real = fractal->min_real + x * (fractal->max_real
				- fractal->min_real) / (fractal->width - 1);
		z.imag = fractal->min_imag + y * (fractal->max_imag
				- fractal->min_imag) / (fractal->height - 1);
		iter = 0;
		while (iter < fractal->max_iter && complex_abs(z) <= 4)
		{
			z = complex_add(complex_square(z), *c);
			iter++;
		}
		set_color(fractal, iter, &color);
		*(unsigned int *)(fractal->addr + (y * fractal->line_len + x
					* (fractal->bpp / 8))) = color;
		x++;
	}
}

void	define_set(char **argv, t_fractal *f, t_complex c)
{
	if (ft_strcmp(argv[1], "Mandelbrot") == 0)
	{
		f->id = 0;
		draw_mandelbrot(f);
	}
	else if (ft_strcmp(argv[1], "Julia") == 0)
	{
		f->id = 1;
		draw_julia(f, c);
	}
	else
	{
		ft_printf("Usage: ./fractol [Mandelbrot/Julia]\n");
		exit(1);
	}
}
