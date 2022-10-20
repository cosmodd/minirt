/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_lookat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:57:03 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/19 17:28:05 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include <stdio.h>

t_mat4	mat4_lookat(t_vec3 from, t_vec3 to)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	world_up;

	world_up = (t_vec3){0, 1, 0};
	forward = vec3_normalize(vec3_sub(from, to));
	if (fabs(forward.y) == 1)
		world_up = (t_vec3){0, 0, -forward.y};
	right = vec3_normalize(vec3_cross(world_up, forward));
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
