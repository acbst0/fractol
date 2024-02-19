/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:26:12 by abostano          #+#    #+#             */
/*   Updated: 2024/02/19 15:59:39 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_set_var(int *a, double *result,
		double *fraction, int *fractionDigits)
{
	*a = 0;
	*result = 0.0;
	*fraction = 0.0;
	*fractionDigits = 0;
}

static void	ft_pow(double *fraction, int *fractiondigits,
									int a, const char *str)
{
	if (str[a] == '.')
	{
		a++;
		while (str[a] >= '0' && str[a] <= '9')
		{
			*fraction = *fraction * 10.0 + (str[a] - '0');
			*fractiondigits += 1;
			a++;
		}
	}
}

double	ft_atod(const char *str)
{
	int		a;
	int		flag;
	double	result;
	double	fraction;
	int		fractiondigits;

	ft_set_var(&a, &result, &fraction, &fractiondigits);
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			flag = -1;
		else
			flag = 1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		result = result * 10.0 + (str[a] - '0');
		a++;
	}
	ft_pow(&fraction, &fractiondigits, a, str);
	result += fraction / pow(10, fractiondigits);
	return (result * flag);
}

void	arg_error(void)
{
	ft_printf("Usage:\n./fractol Mandelbrot\n");
	ft_printf("./fractol Julia\n");
	ft_printf("./fractol Julia [real] [img]\n");
	ft_printf("Use '.' as decimal separator\n");
}

int	ft_check_inputs(int argc, char **argv, t_complex *c)
{
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "Mandelbrot") == 0)
			return (1);
		else if (ft_strcmp(argv[1], "Julia") == 0)
			return (1);
	}
	else if (argc == 4)
	{
		if (ft_strcmp(argv[1], "Julia") == 0)
		{
			c->real = ft_atod(argv[2]);
			c->imag = ft_atod(argv[3]);
			return (1);
		}
	}
	return (0);
}
