/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:52:24 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 10:54:49 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	math_minf(double a, double b)
{
	return (a * (a <= b) + b * (a > b));
}

double	math_maxf(double a, double b)
{
	return (a * (a >= b) + b * (a < b));
}
