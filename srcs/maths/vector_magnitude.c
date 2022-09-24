/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_magnitude.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:45:11 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/22 15:45:18 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	vec2_magnitude(t_vec2 a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

double	vec3_magnitude(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
