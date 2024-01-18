# define WIDTH 1600
# define HEIGHT 1600
# define MAX_ITER 100

# include "../libs/minilibx_opengl_20191021/mlx.h"
# include <math.h>
# include "../libs/libft/libft.h"

struct Fractal
{
    double min_re;
    double max_re;
    double min_im;
    double max_im;
    double zoom;
};

struct Fractal fractal;

void draw_mandelbrot(void *mlx_ptr, void *win_ptr);
int handle_scroll(int button, int x, int y, void *param);

int handle_scroll(int button, int x, int y, void *param)
{
    (void)x;
    (void)y;

    double zoom_factor = 1.1;

    if (button == 4) // Scroll Up
    {
        fractal.zoom *= zoom_factor;
    }
    else if (button == 5) // Scroll Down
    {
        fractal.zoom /= zoom_factor;
    }

    fractal.min_re = fractal.min_re / fractal.zoom + (1 - 1 / zoom_factor) * x / WIDTH;
    fractal.max_re = fractal.max_re / fractal.zoom + (1 - 1 / zoom_factor) * x / WIDTH;
    fractal.min_im = fractal.min_im / fractal.zoom + (1 - 1 / zoom_factor) * y / HEIGHT;
    fractal.max_im = fractal.max_im / fractal.zoom + (1 - 1 / zoom_factor) * y / HEIGHT;

    mlx_clear_window(param, param);
    draw_mandelbrot(param, param);
    return 0;
}

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
            while (z_re * z_re + z_im * z_im < 4 && iteration < MAX_ITER)
            {
                tmp = z_re;
                z_re = z_re * z_re - z_im * z_im + c_re;
                z_im = 2 * tmp * z_im + c_im;
                iteration++;
            }

            // Draw pixel based on iteration count
            if (iteration == MAX_ITER)
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x000000);
            else
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, iteration * 0x001122);
        }
    }
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();

    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Mandelbrot Fractal");

    ft_memset(&fractal, 0, sizeof(struct Fractal));

    fractal.min_re = -2.0;
    fractal.max_re = 2.0;
    fractal.min_im = -2.0;
    fractal.max_im = 2.0;
    fractal.zoom = 1.0;

    mlx_hook(win_ptr, 6, 0, handle_scroll, win_ptr);
    draw_mandelbrot(mlx_ptr, win_ptr);

    mlx_loop(mlx_ptr);

    return 0;
}
