/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:10:55 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/22 15:18:54 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
