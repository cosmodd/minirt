/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:47:06 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/01 14:19:02 by mrattez          ###   ########.fr       */
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
	sphere->specular = 100;
	sphere->reflection = 0;
	return (sphere);
}

t_collideable	*new_sphere_col(t_vec3 position, double radius, t_vec3 color)
{
	t_collideable	*collideable;
	t_sphere		*sphere;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = SPHERE;
	collideable->color = color;
	sphere = new_sphere(position, radius, color);
	if (sphere == NULL)
	{
		free(collideable);
		return (NULL);
	}
	collideable->sphere = sphere;
	collideable->intersect = intersect_sphere;
	return (collideable);
}

void	intersect_sphere(t_hit *hit, t_sphere *sphere)
{
	t_factors	f;
	double	r;
	t_vec3	vec_co;
	t_vec3	abc;
	double	discriminant;
	double	t[2];

	r = sphere->radius;
	vec_co = vec3_sub(hit->pos, sphere->position);
	f.a = vec3_dot(hit->raydir, hit->raydir);
	f.b = 2.0 * vec3_dot(hit->raydir, vec_co);
	f.c = vec3_dot(vec_co, vec_co) - r * r;
	nearest_t(hit, &f);
	hit->collided->normal = vec3_sub(
		vec3_add(vec3_scalar(hit->raydir, hit->t), hit->pos),
		sphere->position);
	hit->collided->specular = hit->collided->sphere->specular;
	hit->collided->reflection = hit->collided->sphere->reflection;
}
