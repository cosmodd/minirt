/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:52:38 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 13:26:18 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*new_plane(t_vec3 position, t_vec3 direction, t_vec3 color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (NULL);
	plane->position = position;
	plane->direction = direction;
	plane->color = color;
	return (plane);
}

double	intersect_plane(t_vec3 camera, t_vec3 raydir, t_plane plane)
{
	t_vec3	co;
	double	denom;
	double	t;

	denom = vec3_dot(raydir, plane.direction);
	if (denom > 1e-6)
	{
		co = vec3_sub(plane.position, camera);
		t = vec3_dot(co, plane.direction) / denom;
		if (t < 0)
			return (INF);
		return (t);
	}
	return (INF);
}
