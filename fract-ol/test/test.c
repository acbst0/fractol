#include "../minilibx_opengl_20191021/mlx.h"
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

// Karmaşık sayı yapısı
typedef struct s_complex
{
    double  real;
    double  imag;
}               t_complex;

// Karmaşık sayıları topla
t_complex complex_add(t_complex a, t_complex b)
{
    t_complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return (result);
}

// Karmaşık sayıları karesini al
t_complex complex_square(t_complex z)
{
    t_complex result;
    result.real = z.real * z.real - z.imag * z.imag;
    result.imag = 2 * z.real * z.imag;
    return (result);
}

// Karmaşık sayıyı mutlak değerini döndür
double complex_abs(t_complex z)
{
    return (z.real * z.real + z.imag * z.imag);
}

// Mandelbrot kümesi hesaplama
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

// Mouse tekerleği hareketini dinleyen işlev
int mouse_scroll(int button, int x, int y, t_fractal *fractal)
{
    double zoom_factor = (button == 4) ? 1.1 : 0.9; // Zoom faktörü (yukarı tekerlek = yakınlaştırma, aşağı tekerlek = uzaklaştırma)

    double center_real = fractal->min_real + x * (fractal->max_real - fractal->min_real) / fractal->width;
    double center_imag = fractal->min_imag + y * (fractal->max_imag - fractal->min_imag) / fractal->height;

    fractal->min_real = center_real - (center_real - fractal->min_real) / zoom_factor;
    fractal->max_real = center_real + (fractal->max_real - center_real) / zoom_factor;
    fractal->min_imag = center_imag - (center_imag - fractal->min_imag) / zoom_factor;
    fractal->max_imag = center_imag + (fractal->max_imag - center_imag) / zoom_factor;

    mlx_clear_window(fractal->mlx, fractal->win);
    draw_mandelbrot(fractal);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

int     main(void)
{
    t_fractal   fractal;

    fractal.mlx = mlx_init();
    fractal.width = 800;
    fractal.height = 600;
    fractal.min_real = -2.0;
    fractal.max_real = 2.0;
    fractal.min_imag = -1.5;
    fractal.max_imag = 1.5;
    fractal.max_iter = 100;
    fractal.win = mlx_new_window(fractal.mlx, fractal.width, fractal.height, "Mandelbrot Set");
    fractal.img = mlx_new_image(fractal.mlx, fractal.width, fractal.height);
    fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bpp, &fractal.line_len, &fractal.endian);

    mlx_mouse_hook(fractal.win, mouse_scroll, &fractal); // Mouse tekerleği hareketini yakalama

    draw_mandelbrot(&fractal);
    mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
    mlx_loop(fractal.mlx);
    return (0);
}