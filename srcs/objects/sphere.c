/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:47:06 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 16:12:24 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a sphere object.
 *
 * @param position Position of the center of the sphere.
 * @param radius Radius of the sphere.
 * @param color Color of the sphere object.
 * @return t_sphere*
 */
t_sphere	*new_sphere(t_vec3 position, double radius, t_vec3 color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->position = position;
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}

/**
 * @brief Finds the first point of intersection to a sphere.
 *
 * @param camera Position of the camera.
 * @param raydir Direction of the ray.
 * @param sphere Sphere object.
 * @return double - Distance to the intersection with the sphere.
 */
double	intersect_sphere(t_vec3 camera, t_vec3 raydir, t_sphere sphere)
{
	double	r;
	t_vec3	vec_co;
	t_vec3	abc;
	double	discriminant;

	r = sphere.radius;
	vec_co = vec3_sub(camera, sphere.position);
	abc.x = vec3_dot(raydir, raydir);
	abc.y = 2.0 * vec3_dot(vec_co, raydir);
	abc.z = vec3_dot(vec_co, vec_co) - r * r;
	discriminant = abc.y * abc.y - 4.0 * abc.x * abc.z;
	if (discriminant >= 0)
		return ((-abc.y - sqrt(discriminant)) / (2.0 * abc.x));
	return (INF);
}
