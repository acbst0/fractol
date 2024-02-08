/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:10:38 by abostano          #+#    #+#             */
/*   Updated: 2024/02/08 14:18:19 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Karmaşık sayıları topla
t_complex	complex_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return (result);
}

// Karmaşık sayıları karesini al
t_complex	complex_square(t_complex z)
{
	t_complex	result;

	result.real = z.real * z.real - z.imag * z.imag;
	result.imag = 2 * z.real * z.imag;
	return (result);
}

// Karmaşık sayıyı mutlak değerini döndür
double	complex_abs(t_complex z)
{
	return (z.real * z.real + z.imag * z.imag);
}
