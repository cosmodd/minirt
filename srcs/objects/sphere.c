/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:47:06 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 11:46:23 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*new_sphere(t_vec3 position, double radius, t_vec3 color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = position;
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}

/**
 * @brief Find if a ray intercept a sphere.
 * Quadratic equation obtained from : the equation for
 * all points on a sphere && the equation from all points on
 * a ray.
 *
 * @param O Origin of the ray (camera).
 * @param D Direction of the ray (viewport square).
 * @param sphere
 * @return t_vec2 - instant t where the ray touches the sphere
 */
double	intersect_sphere(t_vec3 camera, t_vec3 raydir, t_sphere sphere)
{
	double	r;
	t_vec3	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	r = sphere.radius;
	CO = vec3_sub(camera, sphere.center);
	a = vec3_dot(raydir, raydir);
	b = 2.0 * vec3_dot(CO, raydir);
	c = vec3_dot(CO, CO) - r * r;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant >= 0)
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
		// t.y = (-b - sqrt(discriminant)) / (2.0 * a);
		// printf("x=%f\ny=%f\n", t.x, t.y);
	}
	return (INF);
}
