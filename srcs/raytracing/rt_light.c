/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:11:09 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/27 14:03:45by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	color_add(t_vec3 *dest, t_vec3 col, t_vec3 src, double i)
{
	dest->x += fmin(col.x, src.x * i);
	dest->y += fmin(col.y, src.y * i);
	dest->z += fmin(col.z, src.z * i);
}

static double specular_reflection(double intensity, t_hit *hit, double ndl, t_vec3 vecto_l)
{
	t_vec3 R;
	double rdv;

	if (hit->collided->specular == -1)
		return (0);
	R = vec3_scalar(hit->collided->normal, 2);
	R = vec3_scalar(R, ndl);
	R = vec3_sub(R, vecto_l);
	rdv = vec3_dot(R, vec3_scalar(hit->raydir, -1));
	if (rdv > 0)
		return (intensity * \
			pow(rdv / (vec3_magnitude(R) * vec3_magnitude(hit->raydir)), \
				hit->collided->specular));
	return (0);
}

void	compute_lighting(t_scene scene, t_hit *hit)
{
	t_list	*light_node;
	t_light	light;
	t_vec3	vecto_l;
	double	i;
	double	ndl;

	color_add(&hit->color, hit->collided->color, scene.ambient_light.color, scene.ambient_light.intensity);
	light_node = scene.lights;
	while (light_node != NULL)
	{
		light = *(t_light *)(light_node->content);
		vecto_l = vec3_sub(light.position, hit->point);
		ndl = vec3_dot(hit->collided->normal, vecto_l);
		if (!in_shadow(hit->point, light, scene, hit->collided)) {
			if (ndl > 0)
			{
				i = light.intensity * ndl / (vec3_magnitude(hit->collided->normal) * vec3_magnitude(vecto_l));
				i += specular_reflection(light.intensity, hit, ndl, vecto_l);
				color_add(&hit->color, hit->collided->color, light.color, i);
			}
		}
		light_node = light_node->next;
	}
	hit->color.x = fmin(hit->color.x, 255);
	hit->color.y = fmin(hit->color.y, 255);
	hit->color.z = fmin(hit->color.z, 255);
}

