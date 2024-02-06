/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:35 by abostano          #+#    #+#             */
/*   Updated: 2024/02/06 20:06:37 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void draw_mandelbrot(t_fractal *fractal)
{
    int         x;
    int         y;
    t_complex   c;
    t_complex   z;
    int         iter;

    y = 0;
    while (y < fractal->height)
    {
        x = 0;
        while (x < fractal->width)
        {
            c.real = fractal->min_real + x * (fractal->max_real - fractal->min_real) / (fractal->width - 1);
            c.imag = fractal->min_imag + y * (fractal->max_imag - fractal->min_imag) / (fractal->height - 1);
            z.real = 0;
            z.imag = 0;
            iter = 0;
            while (iter < fractal->max_iter && complex_abs(z) <= 4)
            {
                z = complex_add(complex_square(z), c);
                iter++;
            }
            int color = (iter == fractal->max_iter) ? 0x000000 : iter * 0x123456; // Renk hesaplama (iterasyona bağlı olarak renklendirme)
            *(unsigned int *)(fractal->addr + (y * fractal->line_len + x * (fractal->bpp / 8))) = color;
            x++;
        }
        y++;
    }
}

void draw_julia(t_fractal *fractal, t_complex c)
{
    int         x;
    int         y;
    t_complex   z;
    int         iter;

    y = 0;
    while (y < fractal->height)
    {
        x = 0;
        while (x < fractal->width)
        {
            z.real = fractal->min_real + x * (fractal->max_real - fractal->min_real) / (fractal->width - 1);
            z.imag = fractal->min_imag + y * (fractal->max_imag - fractal->min_imag) / (fractal->height - 1);
            iter = 0;
            while (iter < fractal->max_iter && complex_abs(z) <= 4)
            {
                z = complex_add(complex_square(z), c);
                iter++;
            }
            int color = (iter == fractal->max_iter) ? 0x000000 : iter * 0x123456;
            *(unsigned int *)(fractal->addr + (y * fractal->line_len + x * (fractal->bpp / 8))) = color;
            x++;
        }
        y++;
    }
}

void    define_set(char **argv, t_fractal f, t_complex c)
{
    if (ft_strcmp(argv[1], "Mandelbrot") == 0)
    {
        f.id = 0;
        draw_mandelbrot(&f);
    }
    else if (ft_strcmp(argv[1], "Julia") == 0)
    {
        f.id = 1;
        draw_julia(&f, c);
    }
    else
    {
        ft_printf("Usage: ./fractol [Mandelbrot/Julia]\n");
        exit(1);
    }
}

int	ft_strcmp(char *s1, char *s2)
{
    char *p1;
    char *p2;
	int i;

    p1 = s1;
    p2 = s2;
	i = 0;
	while (p1[i] == p2[i] && p1[i] != '\0' && p2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}