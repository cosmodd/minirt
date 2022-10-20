/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:18:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/19 17:47:21 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	parse_ambient(t_scene *scene, char **params)
{
	static int	ambient_parsed = 0;
	
	if (++ambient_parsed > 1)
	{
		plog(ERROR, "Ambient light already defined");
		exit(1);
	}
	scene->ambient_light = (t_ambient){
		.intensity = parse_double(params[0]),
		.color = parse_color(params[1]),
	};
}

static void	parse_camera(t_scene *scene, char **params)
{
	static int	cameras_parsed = 0;
	
	if (++cameras_parsed > 1)
	{
		plog(ERROR, "Camera already defined");
		exit(1);
	}
	scene->camera = (t_camera){
		.position = parse_vec3(params[0]),
		.direction = parse_vec3(params[1]),
		.fov = parse_double(params[2]),
	};
	if (vec3_magnitude(scene->camera.direction) == 0)
		scene->camera.direction = (t_vec3){0, 0, 1};
	else
		scene->camera.direction = vec3_normalize(scene->camera.direction);
	scene->camera.view = mat4_lookat(
		scene->camera.position,
		vec3_add(scene->camera.position, scene->camera.direction)
	);
}

static void	parse_light(t_scene *scene, char **params)
{
	t_light	*light;

	light = new_light_point(
		parse_vec3(params[0]),
		parse_double(params[1]),
		parse_color(params[2])
	);
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
}

static void	push_col(t_scene *scene, t_collideable *col)
{
	ft_lstadd_back(&scene->collideables, ft_lstnew(col));
}

void	parse_object(t_engine *engine, char *type, char **params)
{
	if (ft_strcmp(type, "A") == 0)
		parse_ambient(&engine->scene, params);
	else if (ft_strcmp(type, "C") == 0)
		parse_camera(&engine->scene, params);
	else if (ft_strcmp(type, "L") == 0)
		parse_light(&engine->scene, params);
	else if (ft_strcmp(type, "sp") == 0)
		push_col(&engine->scene, new_sphere_col(parse_vec3(params[0]),
			parse_double(params[1]), parse_color(params[2])));
	else if (ft_strcmp(type, "pl") == 0)
		push_col(&engine->scene, new_plane_col(parse_vec3(params[0]),
			vec3_normalize(parse_vec3(params[1])), parse_color(params[2])));
	else if (ft_strcmp(type, "cy") == 0)
		push_col(&engine->scene, new_cylinder_col(parse_vec3(params[0]),
			vec3_normalize(parse_vec3(params[1])), parse_double(params[2]),
				parse_double(params[3]), parse_color(params[4])));
	else
	{
		plog(ERROR, "Unknown object type");
		exit(1);
	}
}