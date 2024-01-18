/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:01:15 by abostano          #+#    #+#             */
/*   Updated: 2024/01/10 15:19:49 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main()
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();

    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Mandelbrot Fractal");

    ft_memset(&fractal, 0, sizeof(fractal));

    fractal.min_re = -2.0;
    fractal.max_re = 2.0;
    fractal.min_im = -2.0;
    fractal.max_im = 2.0;
    fractal.zoom = 1.0;

    draw_mandelbrot(mlx_ptr, win_ptr);
    mlx_hook(win_ptr, 6, 0, handle_scroll, win_ptr);

    mlx_loop(mlx_ptr);

    return 0;
}