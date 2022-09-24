/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cross.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:36:14 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/22 15:44:16 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	vec2_cross(t_vec2 a, t_vec2 b)
{
	return (a.x * b.y - a.y * b.x);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}
