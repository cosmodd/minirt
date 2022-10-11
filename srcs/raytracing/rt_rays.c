/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:27:13 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/11 10:25:14 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*object_name(t_object type)
{
	if (type == SPHERE)
		return ("⚪️ sphere");
	else if (type == PLANE)
		return ("⬜️ plane");
	else if (type == CYLINDER)
		return ("💊 cylinder");
	return ("unknown");
}

static char	*get_object_position(t_collideable *collideable)
{
	t_vec3	position = {0, 0, 0};
	char	*str = malloc(100);
	
	if (collideable->type == PLANE)
		position = collideable->plane->position;
	else if (collideable->type == SPHERE)
		position = collideable->sphere->position;
	else if (collideable->type == CYLINDER)
		position = collideable->cylinder->position;
	sprintf(str, "(%6.2f, %6.2f, %6.2f)", position.x, position.y, position.z);
	return (str);
}

static bool	in_shadow(t_vec3 point, t_light light, t_scene scene)
{
	// static int		occurence = 0;
	t_list			*current;
	t_collideable	*collideable;
	t_vec3			point_to_light;
	t_vec3			intersection;
	double			distance;
	double			t;

	point_to_light = vec3_sub(light.position, point);
	distance = vec3_magnitude(point_to_light);
	point_to_light = vec3_normalize(point_to_light);
	current = scene.collideables;
	while (current)
	{
		collideable = current->content;
		t = collideable->intersect(point, point_to_light, collideable->ptr);
		// intersection = vec3_scalar(point_to_light, t);
		if (t > 1e-6 && t < distance)
		{
			// printf(
			// 	"☄️ Collision with \e[1;37;44m %s %s \e[0m at t=%6.2f (%6.2f, %6.2f, %6.2f)\n",
			// 	object_name(collideable->type),
			// 	get_object_position(collideable),
			// 	t,
			// 	intersection.x,
			// 	intersection.y,
			// 	intersection.z
			// );
			// printf("🔵 (%6.2f, %6.2f, %6.2f) | ", point.x, point.y, point.z);
			// printf("💡 (%6.2f, %6.2f, %6.2f) | ", light.position.x, light.position.y, light.position.z);
			// printf("👉 (%6.2f, %6.2f, %6.2f)\n", point_to_light.x, point_to_light.y, point_to_light.z);
			return (true);
		}
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
	t_list	*lightNode;
	t_light	light;
	double	i;
	t_vec3	vecto_l;
	double	ndl;

	i = 0;
	i += scene.ambient_light.intensity;
	lightNode = scene.lights;
	while (lightNode != NULL)
	{
		light = *(t_light*)(lightNode->content);
		vecto_l = vec3_sub(light.position, point);
		ndl = vec3_dot(normal, vecto_l);
		if (ndl > 0 && !in_shadow(point, light, scene))
			i += light.intensity * (ndl / (vec3_magnitude(normal) * vec3_magnitude(vecto_l)));
		lightNode = lightNode->next;
	}
	i = math_minf(1, i);
	return (i);
}

t_vec3	get_coll_color(t_scene scene, t_collideable coll, double min, t_vec3 rd)
{
	t_vec3	P;
	t_vec3	N;
	t_vec3	color;

	// Lighting compute
	P = vec3_add(scene.camera.position, vec3_scalar(rd, min)); // Compute intersection point
	// color = (t_vec3){0, 0, 0};
	color = coll.color;
	N = (t_vec3){0, 0, 0};
	if (coll.type == PLANE)
	{
		N = coll.plane->direction;
		// N = ((t_plane *)coll.object)->direction; // Compute intersection normal
		// color = coll.plane->color;
		// color = ((t_plane*)coll.object)->color;
	}
	else if (coll.type == SPHERE)
	{
		N = vec3_sub(P, coll.sphere->position);
		// N = vec3_sub(P, ((t_sphere*)coll.object)->position); // Compute intersection normal
		// color = ((t_sphere*)coll.object)->color;
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
		dist = coll.intersect(scene.camera.position, raydir, coll.ptr);
		if (dist < min && dist >= 0)
		{
			min = dist;
			nearest = coll_node->content;
		}
		coll_node = coll_node->next;
	}
	if (nearest == NULL)
		return (0);
	color = get_coll_color(scene, *nearest, min, raydir);
	return (create_rgba(color.x, color.y, color.z, 0));
}
