/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:10:55 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/21 08:42:09 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathutils.h"

/**
 * @brief Dot product of two vec3f.
 * 
 * @param a First vec3f.
 * @param b Second vec3f.
 * @return double 
 */
double	v3f_dot_v3f(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Dot product of a vec3f by a real number.
 * 
 * @param a The vec3f.
 * @param b The real number.
 * @return t_vec3f 
 */
t_vec3f	v3f_scale(t_vec3f a, double b)
{
	t_vec3f	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

/**
 * @brief Substraction of a vec3f by a real number.
 * 
 * @param a The vec3f.
 * @param b The real number.
 * @return t_vec3f 
 */
t_vec3f	v3f_minus(t_vec3f a, double b)
{
	t_vec3f	ret;

	ret.x = a.x - b;
	ret.y = a.y - b;
	ret.z = a.z - b;
	return (ret);
}