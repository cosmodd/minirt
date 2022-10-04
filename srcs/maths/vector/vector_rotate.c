/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:33:21 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/04 13:59:34 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2_rotate(t_vec2 vec, double angle)
{
	t_vec2	rotated;
	double	ca;
	double	sa;

	ca = cos(angle);
	sa = sin(angle);
	rotated.x = vec.x * ca - vec.y * sa;
	rotated.y = vec.x * sa + vec.y * ca;
	return (rotated);
}

t_vec3	vec3_rotate(t_vec3 vec, t_vec3 axis, double angle)
{
	t_vec3	rotated;
	double	cosa;
	double	sina;

	cosa = cos(angle);
	sina = sin(angle);
	rotated.x = vec.x * (cosa + axis.x * axis.x * (1 - cosa))
		+ vec.y * (axis.x * axis.y * (1 - cosa) - axis.z * sina)
		+ vec.z * (axis.x * axis.z * (1 - cosa) + axis.y * sina);
	rotated.y = vec.x * (axis.y * axis.x * (1 - cosa) + axis.z * sina)
		+ vec.y * (cosa + axis.y * axis.y * (1 - cosa))
		+ vec.z * (axis.y * axis.z * (1 - cosa) - axis.x * sina);
	rotated.z = vec.x * (axis.z * axis.x * (1 - cosa) - axis.y * sina)
		+ vec.y * (axis.z * axis.y * (1 - cosa) + axis.x * sina)
		+ vec.z * (cosa + axis.z * axis.z * (1 - cosa));
	return (rotated);
}
