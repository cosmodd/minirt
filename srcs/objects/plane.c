/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:52:38 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/28 14:31:25 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a plane object.
 *
 * @param position Position of the center of the plane.
 * @param direction Direction the plane is facing.
 * @param color Color of the plane object.
 * @return t_plane*
 */
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

/**
 * @brief Finds the first point of intersection to a plane.
 *
 * @param camera Position of the camera.
 * @param raydir Direction of the ray.
 * @param plane Plane object.
 * @return double - Distance to the intersection.
 */
double	intersect_plane(t_vec3 camera, t_vec3 raydir, t_plane plane)
{
	t_vec3	co;
	double	denom;
	double	t;

	denom = vec3_dot(raydir, plane.direction);
	if (math_abs(denom) > 0)
	{
		co = vec3_sub(plane.position, camera);
		t = vec3_dot(co, plane.direction) / denom;
		if (t > 0)
			return (t);
	}
	return (INF);
}
