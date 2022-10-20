/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/20 11:06:33 by mrattez          ###   ########.fr       */
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
double	compute_lighting(t_vec3	point, t_vec3 normal, t_scene scene)
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
		vecto_l = vec3_sub(light.position, point);
		ndl = vec3_dot(normal, vecto_l);
		if (ndl > 0 && !in_shadow(point, light, scene))
			i += light.intensity * \
				(ndl / (vec3_magnitude(normal) * vec3_magnitude(vecto_l)));
		light_node = light_node->next;
	}
	i = fmin(1, i);
	return (i);
}

t_vec3	get_coll_color(t_scene scene, t_collideable coll, double min, t_vec3 rd)
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;

	point = vec3_add(scene.camera.position, vec3_scalar(rd, min));
	color = coll.color;
	normal = (t_vec3){0, 0, 0};
	if (coll.type == PLANE)
		normal = coll.plane->direction;
	else if (coll.type == SPHERE)
		normal = vec3_sub(point, coll.sphere->position);
	else if (coll.type == CYLINDER)
		return (coll.cylinder->color);
	normal = vec3_normalize(normal);
	return (vec3_scalar(color, compute_lighting(point, normal, scene)));
}

static char	*get_coll_type(t_object type)
{
	if (type == SPHERE)
		return ("⚪️ Sphere");
	else if (type == PLANE)
		return ("⬜️ Plane");
	else if (type == CYLINDER)
		return ("💊 Cylinder");
	return ("❓ Unknown");
}

int	raytrace(t_scene scene, t_vec3 raydir, t_vec2 sp)
{
	t_list			*coll_node;
	t_collideable	coll;
	t_collideable	*nearest;
	t_vec2			dist_min;
	t_vec3			color;

	dist_min.y = INF;
	nearest = NULL;
	coll_node = scene.collideables;
	while (coll_node != NULL)
	{
		coll = *(t_collideable *)(coll_node->content);
		dist_min.x = coll.intersect(scene.camera.position, raydir, coll.ptr);
		if (dist_min.x >= 0 && dist_min.x < dist_min.y)
		{
			dist_min.y = dist_min.x;
			nearest = coll_node->content;
		}
		coll_node = coll_node->next;
	}
	if (nearest == NULL)
		return (0);
	color = get_coll_color(scene, *nearest, dist_min.y, raydir);
	return (create_rgba(color.x, color.y, color.z, 0));
}
