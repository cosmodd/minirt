/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_unique.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:28:17 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 11:24:15 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_ambient(t_scene *scene, char **params, t_counts *c)
{
	if (++c->ambients > 1)
		exit((plog(ERROR, "Ambient light already defined") & 0) | 1);
	scene->ambient_light = (t_ambient){
		.intensity = parse_double(params[0]),
		.color = parse_color(params[1]),
	};
}

void	parse_camera(t_scene *scene, char **params, t_counts *c)
{
	if (++c->cams > 1)
		exit((plog(ERROR, "Camera already defined") & 0) | 1);
	scene->camera = (t_camera){
		.position = parse_vec3(params[0]),
		.direction = parse_vec3(params[1]),
		.fov = parse_double(params[2]),
	};
	if (vec3_magnitude(scene->camera.direction) == 0)
		scene->camera.direction = (t_vec3){0, 0, 1};
	else
		scene->camera.direction = vec3_normalize(scene->camera.direction);
	scene->camera.view = mat4_lookat(scene->camera.position, \
		vec3_add(scene->camera.position, scene->camera.direction));
}

void	parse_light(t_scene *scene, char **params)
{
	t_light	*light;

	light = new_light_point(parse_vec3(params[0]), parse_double(params[1]), \
							parse_color(params[2]));
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
}
