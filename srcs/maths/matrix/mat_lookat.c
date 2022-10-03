/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_lookat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:57:03 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/03 08:57:57 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include <stdio.h>

t_mat4	mat4_lookat(t_vec3 from, t_vec3 to)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = vec3_normalize(vec3_sub(to, from));
	// printf("forward: %f %f %f\n", forward.x, forward.y, forward.z);
	// forward = vec3_scalar(forward, -1);
	right = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, forward));
	// printf("right: %f %f %f\n", right.x, right.y, right.z);
	// right = vec3_scalar(right, -1);
	up = vec3_cross(forward, right);
	// printf("up: %f %f %f\n", up.x, up.y, up.z);
	// up = vec3_scalar(up, -1);
	return ((t_mat4){
		.m = {
			{right.x, up.x, forward.x, 0},
			{right.y, up.y, forward.y, 0},
			{right.z, up.z, forward.z, 0},
			{0, 0, 0, 1}
		}
	});
}