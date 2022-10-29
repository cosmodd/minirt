/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:08 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/29 03:04:47 by pforesti         ###   ########.fr       */
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
	cyl->specular = 10;
	cyl->reflection = 0.5f;
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
			return ((void)(hit->collided->normal = d));
	}
	hit->t = -1;
}

void	intersect_cylinder(t_hit *hit, t_cylinder *c)
{
	t_vec3	c_h[2];
	t_vec3	h[2];
	t_vec3	w;
	double	abc[3];
	double	disc;
	double	t[2];

	c_h[0] = vec3_sub(c->position, vec3_scalar(c->direction, c->height / 2.0));
	c_h[1] = vec3_add(c->position, vec3_scalar(c->direction, c->height / 2.0));
	h[0] = vec3_sub(c_h[1], c_h[0]);
	h[1] = vec3_normalize(h[0]);
	w = vec3_sub(hit->pos, c_h[0]);

	abc[0] = vec3_dot2(hit->raydir) - pow(vec3_dot(hit->raydir, h[1]), 2);
	abc[1] = 2 * (vec3_dot(hit->raydir, w) - vec3_dot(hit->raydir, h[1]) * vec3_dot(w, h[1]));
	abc[2] = vec3_dot2(w) - pow(vec3_dot(w, h[1]), 2) - pow(c->radius, 2);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	
	if (disc < 0)
		return ((void)(hit->t = -1));
	
	t[0] = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	if (t[0] <= 0 || t[1] <= 0)
		hit->t = fmax(t[0], t[1]);
	else
		hit->t = fmin(t[0], t[1]);
	hit->point = vec3_add(hit->pos, vec3_scalar(hit->raydir, hit->t));
	hit->collided->normal = vec3_sub(hit->point, vec3_add(c_h[0], vec3_scalar(h[1], vec3_dot(vec3_sub(hit->point, c_h[0]), h[1]))));

	if (vec3_dot(vec3_sub(hit->point, c_h[0]), h[0]) < 0)
		intersect_disk(hit, c_h[0], h[1], c->radius);
	else if (vec3_dot(vec3_sub(hit->point, c_h[0]), h[0]) > vec3_dot2(h[0]))
		intersect_disk(hit, c_h[1], vec3_scalar(h[1], -1), c->radius);

	hit->collided->specular = hit->collided->cylinder->specular;
}