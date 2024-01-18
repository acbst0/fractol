/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:36:25 by abostano          #+#    #+#             */
/*   Updated: 2024/01/10 15:29:44 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1600
# define HEIGHT 1600
# define MAX_ITER 100

# include "../libs/minilibx_opengl_20191021/mlx.h"
# include <math.h>
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <string.h>

struct Fractal
{
    double min_re;
    double max_re;
    double min_im;
    double max_im;
    double zoom;
};

struct Fractal fractal;

void draw_julia(void *mlx_ptr, void *win_ptr);
void draw_mandelbrot(void *mlx_ptr, void *win_ptr);
int handle_scroll(int button, int x, int y, void *param);

#endif
