/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:35 by abostano          #+#    #+#             */
/*   Updated: 2024/01/10 13:40:59 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void draw_mandelbrot(void *mlx_ptr, void *win_ptr)
{
    int x, y;
    double c_re, c_im, z_re, z_im, tmp;

    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            c_re = fractal.min_re + (x / (double)WIDTH) * (fractal.max_re - fractal.min_re);
            c_im = fractal.min_im + (y / (double)HEIGHT) * (fractal.max_im - fractal.min_im);

            z_re = 0;
            z_im = 0;

            int iteration = 0;
            while (z_re * z_re + z_im * z_im < 4 && iteration < 1000)
            {
                tmp = z_re;
                z_re = z_re * z_re - z_im * z_im + c_re;
                z_im = 2 * tmp * z_im + c_im;
                iteration++;
            }

            // Draw pixel based on iteration count
            if (iteration == 1000)
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x000000);
            else
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, iteration * 0x001122);
        }
    }
}

void draw_julia(void *mlx_ptr, void *win_ptr)
{
	double minRe = -2.0;
	double maxRe = 1.0;
	double minIm = -1.5;
	double maxIm = 1.5;

	double cRe = -0.7;
	double cIm = 0.27015;

	int x = 0;
	while (x < WIDTH)
	{
		int y = 0;
		while (y < HEIGHT)
		{
			double newRe = minRe + x * (maxRe - minRe) / WIDTH;
			double newIm = minIm + y * (maxIm - minIm) / HEIGHT;
			int i = 0;

			while (i < MAX_ITER)
			{
				double oldRe = newRe;
				double oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + cRe;
				newIm = 2 * oldRe * oldIm + cIm;

				if ((newRe * newRe + newIm * newIm) > 4)
					break;

				i++;
			}

			int color = (i == MAX_ITER) ? 0x00336600 : 0x0033CC00; // Coloring
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			y++;
		}
		x++;
	}
}