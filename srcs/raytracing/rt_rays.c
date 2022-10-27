/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/26 16:56:42 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray(t_hit *hit, t_scene *scene)
{
	t_list			*current;
	t_collideable	*closest;
	double			min_dist;

	min_dist = INFINITY;
	closest = NULL;
	current = scene->collideables;
	while (current != NULL)
	{
		hit->collided = (t_collideable *)current->content;
		hit->collided->intersect(hit, hit->collided->ptr);
		if (hit->t > THRESHOLD && hit->t < min_dist)
		{
			min_dist = hit->t;
			closest = hit->collided;
		}
		current = current->next;
	}
	if (closest == NULL)
		return ((void)(hit->color = vec3_from_rgba(VOID_COLOR)));
	hit->t = min_dist;
	hit->point = vec3_add(hit->pos, vec3_scalar(hit->raydir, min_dist));
	hit->collided = closest;
	hit->color = closest->color;
}

void	raytrace(t_scene scene, t_hit *hit)
{
	ray(hit, &scene);
	if (hit->collided == NULL || hit->t < 0)
		return ;
	hit->collided->normal = vec3_normalize(hit->collided->normal);
	compute_lighting(scene, hit);
}