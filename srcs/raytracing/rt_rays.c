/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/25 15:41:10 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ray(t_hit *hit, t_scene *scene)
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

static bool	in_shadow(t_vec3 point, t_light light, t_scene scene)
{
	t_hit	hit;
	t_vec3	point_to_light;
	double	dist_to_light;

	hit = (t_hit){0};
	hit.pos = point;
	point_to_light = vec3_sub(light.position, point);
	dist_to_light = vec3_magnitude(point_to_light);
	point_to_light = vec3_normalize(point_to_light);
	hit.raydir = point_to_light;
	ray(&hit, &scene);
	return (hit.t > THRESHOLD && hit.t < dist_to_light);
}

static void	compute_lighting(t_scene scene, t_hit *hit)
{
	t_list	*light_node;
	t_light	light;
	t_vec3	vecto_l;
	double	i;
	double	ndl;

	i = 0;
	i += scene.ambient_light.intensity;
	light_node = scene.lights;
	while (light_node != NULL)
	{
		light = *(t_light *)(light_node->content);
		vecto_l = vec3_sub(light.position, hit->point);
		ndl = vec3_dot(hit->collided->normal, vecto_l);
		if (ndl > 0 && !in_shadow(hit->point, light, scene))
			i += light.intensity * ndl / (vec3_magnitude(hit->collided->normal) * vec3_magnitude(vecto_l));
		light_node = light_node->next;
	}
	i = fmin(1, i);
	hit->color = vec3_scalar(hit->color, i);
}

void	raytrace(t_scene scene, t_hit *hit)
{
	ray(hit, &scene);
	if (hit->collided == NULL || hit->t < 0)
		return ;
	hit->collided->normal = vec3_normalize(hit->collided->normal);
	compute_lighting(scene, hit);
}