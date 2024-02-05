#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>

typedef struct	s_fractal
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	int		max_iter;
}				t_fractal;

#endif