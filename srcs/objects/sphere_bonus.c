/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:47:06 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 10:03:51 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Returns a sphere object.
 *
 * @param pos Position of the center of the sphere.
 * @param dsr Diameter, specularity, reflection.
 * @param c Color of the sphere object.
 * @return t_sphere*
 */
t_sphere	*new_sphere(t_vec3 pos, t_vec3 dsr, t_vec3 c)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->position = pos;
	sphere->radius = dsr.x * 0.5f;
	sphere->color = c;
	sphere->specular = dsr.y;
	sphere->reflection = dsr.z;
	return (sphere);
}

t_collideable	*new_sphere_col(t_vec3 pos, t_vec3 dsr, t_vec3 c)
{
	t_collideable	*collideable;
	t_sphere		*sphere;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = SPHERE;
	collideable->color = c;
	sphere = new_sphere(pos, dsr, c);
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
	double		r;
	t_vec3		vec_co;

	r = sphere->radius;
	vec_co = vec3_sub(hit->pos, sphere->position);
	f.a = vec3_dot(hit->raydir, hit->raydir);
	f.b = 2.0 * vec3_dot(hit->raydir, vec_co);
	f.c = vec3_dot(vec_co, vec_co) - r * r;
	nearest_t(hit, &f);
	hit->collided->normal = vec3_sub(\
		vec3_add(vec3_scalar(hit->raydir, hit->t), hit->pos), \
			sphere->position);
	hit->collided->specular = hit->collided->sphere->specular;
	hit->collided->reflection = hit->collided->sphere->reflection;
}
