/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:08 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/21 17:42:38 by mrattez          ###   ########.fr       */
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

static double	intersect_disk(t_vec3 camera, t_vec3 r, t_vec3 p, t_vec3 d, double rad)
{
	t_vec3	co;
	t_vec3	inter;
	t_vec3	v;
	double	denom;
	double	t;

	denom = vec3_dot(d, r);
	if (fabs(denom) > 1e-6)
	{
		co = vec3_sub(p, camera);
		t = vec3_dot(co, d) / denom;
		if (t < 0)
			return (-1);
		inter = vec3_add(camera, vec3_scalar(r, t));
		v = vec3_sub(inter, p);
		if (vec3_dot(v, v) <= rad * rad)
			return (t);
	}
	return (-1);
}

double	intersect_cylinder(t_vec3 camera, t_vec3 r, t_cylinder *cyl)
{
	t_vec3	c_h[2];
	t_vec3	h[2];
	t_vec3	w;
	t_vec3	abc;
	double	disc;
	double	t[3];

	c_h[0] = vec3_add(cyl->position, vec3_scalar(cyl->direction, cyl->height / 2.0));
	c_h[1] = vec3_sub(cyl->position, vec3_scalar(cyl->direction, cyl->height / 2.0));
	h[0] = vec3_sub(c_h[0], c_h[1]);
	h[1] = vec3_normalize(h[0]);
	w = vec3_sub(camera, c_h[1]);

	abc.x = vec3_dot(r, r) - pow(vec3_dot(r, h[1]), 2);
	abc.y = 2 * (vec3_dot(r, w) - vec3_dot(r, h[1]) * vec3_dot(w, h[1]));
	abc.z = vec3_dot(w, w) - pow(vec3_dot(w, h[1]), 2) - pow(cyl->radius, 2);
	disc = pow(abc.y, 2) - 4 * abc.x * abc.z;
	t[0] = (-abc.y + sqrt(disc)) / (2 * abc.x);
	t[1] = (-abc.y - sqrt(disc)) / (2 * abc.x);

	if (disc < THRESHOLD || t[0] < 0 || t[1] < 0){
		t[0] = intersect_disk(camera, r, c_h[0], h[0], cyl->radius);
		t[1] = intersect_disk(camera, r, c_h[1], h[1], cyl->radius);
		if (t[0] >= 0 && (t[0] < t[1] || t[1] < 0))
			return (t[0]);
		return (t[1]);
	}
	
	t[2] = fmin(t[0], t[1]);

	t_vec3	inter = vec3_add(camera, vec3_scalar(r, t[2]));
	if (vec3_dot(vec3_sub(inter, c_h[1]), h[0]) < 0)
		return (intersect_disk(camera, r, c_h[1], h[1], cyl->radius));
	if (vec3_dot(vec3_sub(inter, c_h[0]), h[0]) > 0)
		return (intersect_disk(camera, r, c_h[0], vec3_scalar(h[1], -1), cyl->radius));

	return (t[2]);
}