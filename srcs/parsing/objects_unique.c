/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_unique.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:28:17 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 14:19:41 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_ambient(t_scene *scene, char **params, t_counts *c)
{
	if (++c->ambients > 1)
		quit_error(scene, ((plog(ERROR, \
			"Ambient light already defined") & 0) | 1));
	scene->ambient_light = (t_ambient){
		.intensity = parse_double(scene, params[0]),
		.color = parse_color(scene, params[1]),
	};
	if (scene->ambient_light.intensity > 1 \
		|| scene->ambient_light.intensity < 0)
		quit_error(scene, ((plog(ERROR, \
			"Ambient intensity expected range [0-1]") & 0) | 1));
}

void	parse_camera(t_scene *scene, char **params, t_counts *c)
{
	if (++c->cams > 1)
		quit_error(scene, ((plog(ERROR, "Camera already defined") & 0) | 1));
	scene->camera = (t_camera){
		.position = parse_vec3(scene, params[0]),
		.direction = parse_vec3(scene, params[1]),
		.fov = parse_double(scene, params[2]),
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

	light = new_light_point(parse_vec3(scene, params[0]), \
		parse_double(scene, params[1]), \
			parse_color(scene, params[2]));
	if (light->intensity > 1 || light->intensity < 0)
		quit_error(scene, ((plog(ERROR, \
			"Light intensity expected range [0-1]") & 0) | 1));
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
}
