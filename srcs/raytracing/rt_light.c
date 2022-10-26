/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:11:09 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/26 14:47:16 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
static double specular_reflection(double intensity, t_hit *hit, double ndl, t_vec3 vecto_l)
{
	t_vec3 R;
	double rdv;

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

	i = 0;
	i += scene.ambient_light.intensity;
	light_node = scene.lights;
	while (light_node != NULL)
	{
		light = *(t_light *)(light_node->content);
		vecto_l = vec3_sub(light.position, hit->point);
		ndl = vec3_dot(hit->collided->normal, vecto_l);
		if (!in_shadow(hit->point, light, scene)) {
			if (ndl > 0)
				i += light.intensity * ndl / (vec3_magnitude(hit->collided->normal) * vec3_magnitude(vecto_l));
			if (hit->collided->specular != -1)
				i += specular_reflection(light.intensity, hit, ndl, vecto_l);
		}
		light_node = light_node->next;
	}
	i = fmin(1, i);
	hit->color = vec3_scalar(hit->color, i);
}

