/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:46:17 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 10:59:04 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	color_add(t_vec3 *dest, t_vec3 col, t_vec3 src, double i)
{
	dest->x += fmin(col.x, src.x * i);
	dest->y += fmin(col.y, src.y * i);
	dest->z += fmin(col.z, src.z * i);
}

static double	diffuse_reflect(double i, double ndl, t_vec3 normal, t_vec3 v_l)
{
	return (i * ndl / (vec3_magnitude(normal) * vec3_magnitude(v_l)));
}

static double	specular_reflect(double i, t_hit *hit, double ndl, t_vec3 v_l)
{
	t_vec3	v_inv;
	double	rdv;

	if (hit->collided->specular == -1)
		return (0);
	v_inv = vec3_scalar(hit->collided->normal, 2);
	v_inv = vec3_scalar(v_inv, ndl);
	v_inv = vec3_sub(v_inv, v_l);
	rdv = vec3_dot(v_inv, vec3_scalar(hit->raydir, -1));
	if (rdv > 0)
		return (i * \
			pow(rdv / (vec3_magnitude(v_inv) * vec3_magnitude(hit->raydir)), \
				hit->collided->specular));
	return (0);
}

void	compute_lighting(t_scene scene, t_hit *hit)
{
	t_list	*light_node;
	t_light	light;
	t_vec3	v;
	double	i;
	double	ndl;

	color_add(&hit->color, hit->collided->color, scene.ambient_light.color, \
		scene.ambient_light.intensity);
	light_node = scene.lights;
	while (light_node != NULL)
	{
		light = *(t_light *)(light_node->content);
		v = vec3_sub(light.position, hit->point);
		ndl = vec3_dot(hit->collided->normal, v);
		if (!in_shadow(hit->point, light, scene, hit->collided) && ndl > 0)
		{
			i = diffuse_reflect(light.intensity, ndl, hit->collided->normal, v);
			i += specular_reflect(light.intensity, hit, ndl, v);
			color_add(&hit->color, hit->collided->color, light.color, i);
		}
		light_node = light_node->next;
	}
	hit->color.x = fmin(hit->color.x, 255);
	hit->color.y = fmin(hit->color.y, 255);
	hit->color.z = fmin(hit->color.z, 255);
}
