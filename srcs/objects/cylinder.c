/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:08 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 10:19:45 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*new_cylinder(t_vec3 pos, t_vec3 dir, t_vec2 dh, t_vec3 c)
{
	t_cylinder	*cyl;

	cyl = malloc(sizeof(t_cylinder));
	if (cyl == NULL)
		return (NULL);
	cyl->position = pos;
	cyl->direction = dir;
	cyl->radius = dh.x / 2;
	cyl->diameter = dh.x;
	cyl->height = dh.y;
	cyl->color = c;
	cyl->specular = -1;
	cyl->reflection = 0;
	return (cyl);
}

t_collideable	*new_cylinder_col(t_vec3 pos, t_vec3 dir, t_vec2 dh, t_vec3 c)
{
	t_collideable	*collideable;
	t_cylinder		*cyl;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = CYLINDER;
	collideable->color = c;
	cyl = new_cylinder(pos, dir, dh, c);
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
	t_vec3	v;
	double	denom;
	double	t;

	denom = vec3_dot(d, hit->raydir);
	if (fabs(denom) <= 1e-6)
		return ;
	co = vec3_sub(p, hit->pos);
	t = vec3_dot(co, d) / denom;
	if (t < 0)
		return ;
	hit->point = vec3_add(hit->pos, vec3_scalar(hit->raydir, t));
	v = vec3_sub(hit->point, p);
	if (vec3_dot(v, v) <= rad * rad && (hit->t == -1 || t < hit->t))
	{
		hit->t = t;
		hit->collided->normal = d;
	}
}

void	intersect_cylinder(t_hit *hit, t_cylinder *c)
{
	t_factors	f;
	t_vec3		c_h[2];
	t_vec3		h[2];
	t_vec3		w;

	c_h[0] = vec3_sub(c->position, vec3_scalar(c->direction, c->height / 2.0));
	c_h[1] = vec3_add(c->position, vec3_scalar(c->direction, c->height / 2.0));
	h[0] = vec3_sub(c_h[1], c_h[0]);
	h[1] = vec3_normalize(h[0]);
	w = vec3_sub(hit->pos, c_h[0]);
	f.a = vec3_dot2(hit->raydir) - pow(vec3_dot(hit->raydir, h[1]), 2);
	f.b = 2 * (vec3_dot(hit->raydir, w) - vec3_dot(hit->raydir, h[1]) \
		* vec3_dot(w, h[1]));
	f.c = vec3_dot2(w) - pow(vec3_dot(w, h[1]), 2) - pow(c->radius, 2);
	nearest_t(hit, &f);
	hit->point = vec3_add(hit->pos, vec3_scalar(hit->raydir, hit->t));
	hit->collided->normal = vec3_sub(hit->point, vec3_add(c_h[0], \
		vec3_scalar(h[1], vec3_dot(vec3_sub(hit->point, c_h[0]), h[1]))));
	if (vec3_dot(vec3_sub(hit->point, c_h[0]), h[0]) < 0 \
		|| vec3_dot(vec3_sub(hit->point, c_h[0]), h[0]) > vec3_dot2(h[0]))
		hit->t = -1;
	intersect_disk(hit, c_h[0], vec3_scalar(h[1], -1), c->radius);
	intersect_disk(hit, c_h[1], h[1], c->radius);
	hit->collided->specular = hit->collided->cylinder->specular;
	hit->collided->reflection = hit->collided->cylinder->reflection;
}
