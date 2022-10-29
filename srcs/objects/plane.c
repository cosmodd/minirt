/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:52:38 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/29 04:09:46 by pforesti         ###   ########.fr       */
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
	plane->specular = -1;
	plane->reflection = -1;
	return (plane);
}

t_collideable	*new_plane_col(t_vec3 position, t_vec3 direction, t_vec3 color)
{
	t_collideable	*collideable;
	t_plane			*plane;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = PLANE;
	collideable->color = color;
	plane = new_plane(position, direction, color);
	if (plane == NULL)
	{
		free(collideable);
		return (NULL);
	}
	collideable->plane = plane;
	collideable->intersect = intersect_plane;
	return (collideable);
}

void	intersect_plane(t_hit *hit, t_plane *plane)
{
	t_vec3	co;
	double	denom;

	hit->t = -1;
	denom = vec3_dot(hit->raydir, plane->direction);
	if (fabs(denom) <= THRESHOLD)
		return ;
	co = vec3_sub(plane->position, hit->pos);
	hit->t = vec3_dot(co, plane->direction) / denom;
	hit->collided->normal = plane->direction;
	hit->collided->specular = hit->collided->plane->specular;
	hit->collided->reflection = hit->collided->plane->reflection;
}
