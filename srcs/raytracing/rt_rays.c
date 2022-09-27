/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/09/27 13:43:53 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Compute the intensity I of the different light sources
 * in the scene, for a specific point.
 *
 * @param P Point to compute light intensity.
 * @param N Normal of the point in relation to its surface.
 * @param scene Current scene.
 * @return double - intensity I.
 */
double	compute_lighting(t_vec3	P, t_vec3 N, t_scene scene)
{
	t_list	*lightNode;
	t_light	light;
	double	i;
	t_vec3	L;
	double	ndl;

	i = 0;
	i += scene.ambient_light.intensity;
	lightNode = scene.lights;
	while (lightNode != NULL)
	{
		light = *(t_light*)(lightNode->content);
		L = vec3_sub(light.position, P);
		ndl = vec3_dot(N, L);
		if (ndl > 0)
			i += light.intensity * (ndl / (vec3_magnitude(N) * vec3_magnitude(L)));
		lightNode = lightNode->next;
	}
	i = math_minf(1, i);
	return (i);
}

double	call_collide(t_scene s, t_vec3 raydir, t_object type, void *obj)
{
	double	ret;

	ret = INF;
	if (type == PLANE)
		ret = intersect_plane(s.camera.position, raydir, *(t_plane *)obj);
	else if (type == SPHERE)
		ret = intersect_sphere(s.camera.position, raydir, *(t_sphere *)obj);
	return (ret);
}

t_vec3	get_coll_color(t_scene scene, t_collideable coll, double min, t_vec3 rd)
{
	t_vec3	P;
	t_vec3	N;
	t_vec3	color;

	// Lighting compute
	P = vec3_add(scene.camera.position, vec3_scalar(rd, min)); // Compute intersection point
	color = (t_vec3){0, 0, 0};
	N = (t_vec3){0, 0, 0};
	if (coll.type == PLANE)
	{
		N = vec3_scalar(((t_plane *)coll.object)->direction, -1); // Compute intersection normal
		color = ((t_plane*)coll.object)->color;
	}
	else if (coll.type == SPHERE)
	{
		N = vec3_sub(P, ((t_sphere*)coll.object)->center); // Compute intersection normal
		color = ((t_sphere*)coll.object)->color;
	}
	N = vec3_normalize(N);
	return (vec3_scalar(color, compute_lighting(P, N, scene)));
	// return (color);
}

int	raytrace(t_scene scene, t_vec3 raydir)
{
	t_list			*coll_node;
	t_collideable	coll;
	t_collideable	*nearest;
	double			dist;
	double			min;
	t_vec3			color;

	min = INF;
	nearest = NULL;
	coll_node = scene.collideables;
	while (coll_node != NULL)
	{
		coll = *(t_collideable *)(coll_node->content);
		dist = call_collide(scene, raydir, coll.type, coll.object);
		if (dist < min)
		{
			min = dist;
			nearest = coll_node->content;
		}
		coll_node = coll_node->next;
	}
	if (nearest == NULL)
		return (0);
	color = get_coll_color(scene, *nearest, min, raydir);
	return (create_trgb(0, color.x, color.y, color.z));
}
