/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:36:25 by abostano          #+#    #+#             */
/*   Updated: 2024/02/08 18:30:10 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1250
# define HEIGHT 1250
# define MAX_ITER 25

# include "../libs/minilibx_opengl_20191021/mlx.h"
# include "../libs/ft_printf/ft_printf.h"
# include <math.h>
# include <stdlib.h>

typedef struct s_fractal
{
	int		id;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	int		max_iter;
	int		bpp;
	int		line_len;
	int		endian;
}	t_fractal;

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

//fractal_types.c
void		draw_mandelbrot(t_fractal *fractal);
void		draw_mandelbrot_two(t_fractal *fractal, t_complex *c,
				t_complex *z, int y);
void		draw_julia(t_fractal *fractal, t_complex c);
void		draw_julia_two(t_fractal *fractal, t_complex *c, int y);
void		define_set(char **argv, t_fractal *f, t_complex c);
//fractol.c
void		set_color(t_fractal *fractal, int iter, int *color);
int			ft_strcmp(char *s1, char *s2);
void		init_f(t_fractal *f);
void		clean_f(t_fractal *f);
//img_num
t_complex	complex_add(t_complex a, t_complex b);
t_complex	complex_square(t_complex z);
double		complex_abs(t_complex z);
//mouse_key
int			mouse_scroll(int button, int x, int y, t_fractal *fractal);
void		mouse_scroll_two(double zoom_factor, int x, int y,
				t_fractal *fractal);
int			key_hook(int keycode, t_fractal *data);
int			close_window(t_fractal *fractal);

#endif
