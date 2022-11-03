/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:52:38 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/30 11:34:36 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Returns a plane object.
 *
 * @param pos Position of the center of the plane.
 * @param dir Direction the plane is facing.
 * @param sr Specularity and reflection.
 * @param color Color of the plane object.
 * @return t_plane*
 */
t_plane	*new_plane(t_vec3 pos, t_vec3 dir, t_vec2 sr, t_vec3 color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (NULL);
	plane->position = pos;
	plane->direction = dir;
	plane->color = color;
	plane->specular = sr.x;
	plane->reflection = sr.y;
	return (plane);
}

t_collideable	*new_plane_col(t_vec3 pos, t_vec3 dir, t_vec2 sr, t_vec3 color)
{
	t_collideable	*collideable;
	t_plane			*plane;

	collideable = malloc(sizeof(t_collideable));
	if (collideable == NULL)
		return (NULL);
	collideable->type = PLANE;
	collideable->color = color;
	plane = new_plane(pos, dir, sr, color);
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
