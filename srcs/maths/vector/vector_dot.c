/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:44:42 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:25:38 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/* a • b */
double	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec2_dot2(t_vec2 a)
{
	return (vec2_dot(a, a));
}

/* a • b */
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	vec3_dot2(t_vec3 a)
{
	return (vec3_dot(a, a));
}
