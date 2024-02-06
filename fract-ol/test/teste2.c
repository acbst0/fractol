#include "../libs/minilibx_opengl_20191021/mlx.h"
#include <math.h>
#include <stdlib.h>

typedef struct s_fractal
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     width;
    int     height;
    double  min_real;
    double  max_real;
    double  min_imag;
    double  max_imag;
    int     max_iter;
    int     bpp;
    int     line_len;
    int     endian;
}               t_fractal;

typedef struct s_complex
{
    double  real;
    double  imag;
}               t_complex;

t_complex complex_add(t_complex a, t_complex b)
{
    t_complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return (result);
}

t_complex complex_square(t_complex z)
{
    t_complex result;
    result.real = z.real * z.real - z.imag * z.imag;
    result.imag = 2 * z.real * z.imag;
    return (result);
}

double complex_abs(t_complex z)
{
    return (z.real * z.real + z.imag * z.imag);
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

int mouse_move(int x, int y, t_fractal *fractal)
{
    t_complex c;
    c.real = fractal->min_real + x * (fractal->max_real - fractal->min_real) / fractal->width;
    c.imag = fractal->min_imag + y * (fractal->max_imag - fractal->min_imag) / fractal->height;

    mlx_clear_window(fractal->mlx, fractal->win);
    draw_julia(fractal, c);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

int main(void)
{
    t_fractal   fractal;
    t_complex   c;

    fractal.mlx = mlx_init();
    fractal.width = 800;
    fractal.height = 600;
    fractal.min_real = -2.0;
    fractal.max_real = 2.0;
    fractal.min_imag = -1.5;
    fractal.max_imag = 1.5;
    fractal.max_iter = 100;
    fractal.win = mlx_new_window(fractal.mlx, fractal.width, fractal.height, "Julia Set");
    fractal.img = mlx_new_image(fractal.mlx, fractal.width, fractal.height);
    fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bpp, &fractal.line_len, &fractal.endian);

    c.real = -0.7;
    c.imag = 0.27015;
    draw_julia(&fractal, c);
    mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
    mlx_loop(fractal.mlx);
    return (0);
}
