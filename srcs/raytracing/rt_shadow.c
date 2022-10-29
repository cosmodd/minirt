/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 02:18:23 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/29 02:22:36 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ray_shadow(t_hit *hit, t_scene *scene, t_collideable *o_p)
{
	t_list			*current;
	double			min_dist;

	min_dist = INFINITY;
	current = scene->collideables;
	while (current != NULL)
	{
		hit->collided = (t_collideable *)current->content;
		if (hit->collided != o_p) {
			hit->collided->intersect(hit, hit->collided->ptr);
			if (hit->t > THRESHOLD && hit->t < min_dist)
				min_dist = hit->t;
		}
		current = current->next;
	}
	hit->t = min_dist;
}

bool in_shadow(t_vec3 point, t_light light, t_scene scene, t_collideable *o_p)
{
	t_hit	hit;
	t_vec3	point_to_light;
	double	dist_to_light;

	hit = (t_hit){0};
	hit.pos = point;
	point_to_light = vec3_sub(light.position, point);
	dist_to_light = vec3_magnitude(point_to_light);
	hit.raydir = vec3_normalize(point_to_light);
	ray_shadow(&hit, &scene, o_p);
	return (hit.t > THRESHOLD && hit.t < dist_to_light);
}