/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scalar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:22:08 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/22 15:23:59 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2_scalar(t_vec2 vec, double scalar)
{
	t_vec2	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}

t_vec3	vec3_scalar(t_vec3 vec, double scalar)
{
	t_vec3	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}
