/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:46:55 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/22 15:49:21 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2_normalize(t_vec2 vec)
{
	t_vec2	result;
	double	magnitude;

	magnitude = vec2_magnitude(vec);
	result.x = vec.x / magnitude;
	result.y = vec.y / magnitude;
	return (result);
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	t_vec3	result;
	double	magnitude;

	magnitude = vec3_magnitude(vec);
	result.x = vec.x / magnitude;
	result.y = vec.y / magnitude;
	result.z = vec.z / magnitude;
	return (result);
}
