/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:08 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/12 14:22:34y pforesti         ###   ########.fr       */
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

double	intersect_cylinder(t_vec3 camera, t_vec3 r, t_cylinder *cyl)
{
	t_vec3	c;
	t_vec3	h_;
	t_vec3	w;
	t_vec3	abc;
	double	disc[2];
	double	t[2];

	h_ = vec3_scalar(cyl->direction, -1);
	c = vec3_add(cyl->position, vec3_scalar(h_, cyl->height));
	w = vec3_sub(camera, c);
	abc.x = vec3_dot(r, r) - pow(vec3_dot(r, h_), 2);
	abc.y = 2 * (vec3_dot(r, w) - vec3_dot(r, h_) * vec3_dot(w, h_));
	abc.z = vec3_dot(w, w) - pow(vec3_dot(w, h_), 2) - pow(cyl->radius, 2);
	disc[0] = pow(abc.y, 2) - 4.0 * abc.x * abc.z;
	disc[1] = sqrt(disc[0]);
	t[0] = (-abc.y - disc[1]) / 2.0 * abc.x;
	t[1] = (-abc.y + disc[1]) / 2.0 * abc.x;
	if (disc[0] < 0)
		return (-1);
	if (t[0] < 0 || t[1] < 0)
		return (-1);
	return (math_minf(t[0], t[1]));
}

// double	intersect_cylinder(t_vec3 camera, t_vec3 raydir, t_cylinder *cyl)
// {
// 	t_vec3	abc;
// 	double	discriminant;

// 	t_vec3	co = vec3_sub(camera, cyl->position);
// 	t_vec3	v = vec3_scalar(cyl->direction, vec3_dot(raydir, cyl->direction));
// 	v = vec3_sub(raydir, v);
// 	t_vec3	u = vec3_scalar(cyl->direction, vec3_dot(co, cyl->direction));
// 	u = vec3_sub(co, u);

// 	abc.x = vec3_dot(v, v);
// 	abc.y = 2.0 * vec3_dot(v, u);
// 	abc.z = vec3_dot(u, u) - pow(cyl->radius, 2);
// 	discriminant = abc.y * abc.y - 4.0 * abc.x * abc.z;
// 	if (discriminant >= 0)
// 		return (-abc.y - sqrt(discriminant) / (2.0 * abc.x));
// 	return (INF);
// }
