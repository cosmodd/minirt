/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/20 17:39:25 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	in_shadow(t_vec3 point, t_light light, t_scene scene)
{
	t_list			*current;
	t_collideable	*coll;
	t_vec3			point_to_light;
	t_vec2			dist_t;

	point_to_light = vec3_sub(light.position, point);
	dist_t.x = vec3_magnitude(point_to_light);
	point_to_light = vec3_normalize(point_to_light);
	current = scene.collideables;
	while (current)
	{
		coll = current->content;
		dist_t.y = coll->intersect(point, point_to_light, coll->ptr);
		if (dist_t.y > 1e-6 && dist_t.y < dist_t.x)
			return (true);
		current = current->next;
	}
	return (false);
}

/**
 * @brief Compute the intensity I from the different light sources in the scene
 *        for a specific point.
 *
 * @param P Point for which to compute light intensity.
 * @param N Normal of the point in relation to its surface.
 * @param scene Current scene.
 * @return double - Intensity I from the light sources.
 */
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
		ndl = vec3_dot(hit->normal, vecto_l);
		if (ndl > 0 && !in_shadow(hit->point, light, scene))
			i += light.intensity * \
				(ndl / (vec3_magnitude(hit->normal) * vec3_magnitude(vecto_l)));
		light_node = light_node->next;
	}
	i = fmin(1, i);
	hit->color = vec3_scalar(hit->color, i);
}

static void	get_coll_color(t_scene scene, t_collideable coll, t_hit *hit)
{
	t_vec3	normal;
	
	hit->color = coll.color;
	hit->normal = (t_vec3){0, 0, 0};
	if (coll.type == PLANE)
		hit->normal = coll.plane->direction;
	else if (coll.type == SPHERE)
		hit->normal = vec3_sub(hit->point, coll.sphere->position);
	else if (coll.type == CYLINDER)
		return ((void)(hit->color = coll.cylinder->color));
	hit->normal = vec3_normalize(hit->normal);
	compute_lighting(scene, hit);
}

void	raytrace(t_scene scene, t_hit *hit)
{
	t_list			*coll_node;
	t_collideable	coll;
	t_collideable	*nearest;
	t_vec2			dist_min;

	dist_min.y = INFINITY;
	nearest = NULL;
	coll_node = scene.collideables;
	while (coll_node != NULL)
	{
		coll = *(t_collideable *)(coll_node->content);
		dist_min.x = coll.intersect(scene.camera.position, hit->raydir, coll.ptr);
		if (dist_min.x >= 0 && dist_min.x < dist_min.y)
		{
			dist_min.y = dist_min.x;
			nearest = coll_node->content;
		}
		coll_node = coll_node->next;
	}
	if (nearest == NULL)
		return ((void)(hit->color = vec3_from_rgba(VOID_COLOR)));
	hit->point = vec3_add(scene.camera.position, vec3_scalar(hit->raydir, dist_min.y));
	get_coll_color(scene, *nearest, hit);
}
