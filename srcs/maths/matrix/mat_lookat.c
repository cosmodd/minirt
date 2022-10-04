/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_lookat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:57:03 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/04 15:16:29 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include <stdio.h>

t_mat4	mat4_lookat(t_vec3 from, t_vec3 to)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = vec3_normalize(vec3_sub(from, to));
	right = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, forward));
	up = vec3_cross(forward, right);
	return ((t_mat4){
		.m = {
			{right.x, up.x, forward.x, 0},
			{right.y, up.y, forward.y, 0},
			{right.z, up.z, forward.z, 0},
			{0, 0, 0, 1},
		}
	});
}
