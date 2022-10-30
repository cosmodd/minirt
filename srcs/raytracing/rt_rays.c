/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/30 13:07:05 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	reflect_ray(t_vec3 raydir, t_vec3 normal) {
	t_vec3	reflected_ray;

	reflected_ray = vec3_scalar(normal, 2);
	reflected_ray = vec3_scalar(reflected_ray, vec3_dot(normal, raydir));
	reflected_ray = vec3_sub(reflected_ray, raydir);
	return (reflected_ray);
}

void	ray(t_hit *hit, t_scene *scene, t_collideable *o_p, size_t rec_limit)
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
		if (hit->collided != o_p || rec_limit == REC_LIMIT)
		{
			hit->collided->intersect(hit, hit->collided->ptr);
			if (hit->t > THRESHOLD && hit->t < min_dist)
			{
				min_dist = hit->t;
				closest = hit->collided;
			}
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

void	raytrace(t_scene scene, t_hit *hit, size_t rec_limit)
{
	double	r = 0;

	ray(hit, &scene, hit->collided, rec_limit);
	if (hit->collided == NULL || hit->t < 0)
		return ;
	hit->collided->normal = vec3_normalize(hit->collided->normal);
	compute_lighting(scene, hit);

	r = hit->collided->reflection;
	if (!rec_limit|| !r)
		return ;

	hit->raydir = vec3_normalize(reflect_ray(vec3_scalar(hit->raydir, -1), hit->collided->normal));
	t_vec3 local_color = hit->color; // color of previous iteration 
	hit->pos = hit->point;
	raytrace(scene, hit, rec_limit - 1);
	
	hit->color = vec3_add(vec3_scalar(local_color, (1.0 - r)), vec3_scalar(hit->color, r));
}