/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:44:42 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/22 15:44:45 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/* a • b */
double	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

/* a • b */
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
