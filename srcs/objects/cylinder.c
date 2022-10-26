/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:08 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/26 09:04:03 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*new_cylinder(t_vec3 position, t_vec3 direction, double radius, double height, t_vec3 color)
{
	t_cylinder	*cyl;

	cyl = malloc(sizeof(t_cylinder));
	if (cyl == NULL)
		return (NULL);
	cyl->position = position;
	cyl->direction = direction;
	cyl->radius = radius;
	cyl->diameter = 2 * radius;
	cyl->height = height;
	cyl->color = color;
	return (cyl);
}

t_collideable	*new_cylinder_col(t_vec3 position, t_vec3 direction, double diameter, double height, t_vec3 color)
{
	t_collideable	*collideable;
	t_cylinder		*cyl;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = CYLINDER;
	collideable->color = color;
	cyl = new_cylinder(position, direction, diameter / 2, height, color);
	if (cyl == NULL)
	{
		free(collideable);
		return (NULL);
	}
	collideable->cylinder = cyl;
	collideable->intersect = intersect_cylinder;
	return (collideable);
}

static void	intersect_disk(t_hit *hit, t_vec3 p, t_vec3 d, double rad)
{
	t_vec3	co;
	t_vec3	inter;
	t_vec3	v;
	double	denom;

	denom = vec3_dot(d, hit->raydir);
	if (fabs(denom) > 1e-6)
	{
		co = vec3_sub(p, hit->pos);
		hit->t = vec3_dot(co, d) / denom;
		if (hit->t < 0)
			return ;
		inter = vec3_add(hit->pos, vec3_scalar(hit->raydir, hit->t));
		v = vec3_sub(inter, p);
		if (vec3_dot(v, v) <= rad * rad)
			return ;
	}
	hit->t = -1;
}

void	intersect_cylinder(t_hit *hit, t_cylinder *c)
{
	t_vec3	c_h[2];
	t_vec3	h[2];
	t_vec3	w;
	t_vec3	abc;
	double	disc;
	double	t[3];

	c_h[0] = vec3_sub(c->position, vec3_scalar(c->direction, c->height / 2.0));
	c_h[1] = vec3_add(c->position, vec3_scalar(c->direction, c->height / 2.0));
	h[0] = vec3_sub(c_h[1], c_h[0]);
	h[1] = vec3_normalize(h[0]);
	w = vec3_sub(hit->pos, c_h[0]);

	abc.x = vec3_dot(hit->raydir, hit->raydir) - pow(vec3_dot(hit->raydir, h[1]), 2);
	abc.y = 2 * (vec3_dot(hit->raydir, w) - vec3_dot(hit->raydir, h[1]) * vec3_dot(w, h[1]));
	abc.z = vec3_dot(w, w) - pow(vec3_dot(w, h[1]), 2) - pow(c->radius, 2);
	disc = pow(abc.y, 2) - 4 * abc.x * abc.z;
	t[0] = (-abc.y + sqrt(disc)) / (2.0 * abc.x);
	t[1] = (-abc.y - sqrt(disc)) / (2.0 * abc.x);
	t[2] = fmin(t[0], t[1]);

	t_vec3	inter = vec3_add(hit->pos, vec3_scalar(hit->raydir, t[2]));
	t_vec3	centroid = vec3_scalar(c->direction, vec3_magnitude(vec3_sub(inter, c_h[0])));
	t_vec3	proj = vec3_add(c_h[0], centroid);
	
	hit->collided->normal = vec3_sub(inter, proj);
	
	double	intermarche = vec3_dot(vec3_sub(inter, c_h[0]), h[0]);
	
	if (intermarche < 0)
		intersect_disk(hit, c_h[0], vec3_scalar(h[1], -1), c->radius);
	else if (intermarche > vec3_dot(h[0], h[0]))
		intersect_disk(hit, c_h[1], h[1], c->radius);
	else
		hit->t = t[2];
	// if (vec3_dot(vec3_sub(inter, c_h[1]), h[0]) < 0)
	// {
	// 	intersect_disk(hit, c_h[1], h[1], c->radius);
	// 	hit->collided->normal = c->direction;
	// }
	// else if (vec3_dot(vec3_sub(inter, c_h[0]), h[0]) > 0)
	// {
	// 	intersect_disk(hit, c_h[0], vec3_scalar(h[1], -1), c->radius);
	// 	hit->collided->normal = vec3_scalar(h[1], -1);
	// }
	// else
	// {
	// 	hit->t = t[2];
	// 	hit->collided->normal = vec3_scalar(h[1], vec3_dot(vec3_sub(inter, c_h[1]), h[1]));
	// 	hit->collided->normal = vec3_sub(inter, hit->collided->normal);
	// }
}