/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:55:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/06 21:54:17 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_empty_line(char *line)
{
	while (*line)
		if (!ft_isspace(*line++))
			return (false);
	return (true);
}

t_vec3	parse_vec3(t_scene *scene, char *str)
{
	t_vec3	result;
	char	**split;

	if (str == NULL)
		quit_error(scene, (plog(ERROR, "Missing vector attribute !") & 0) | 1);
	split = str_split(str, ",");
	if (strl_len(split) != 3)
	{
		strl_free(&split);
		quit_error(scene, ((plog(ERROR, \
			"Invalid vector format ! Expected x,y,z") & 0) | 1));
	}
	result.x = ft_atof(split[0]);
	result.y = ft_atof(split[1]);
	result.z = ft_atof(split[2]);
	strl_free(&split);
	return (result);
}

t_vec3	parse_color(t_scene *scene, char *str)
{
	t_vec3	result;
	char	**split;

	if (str == NULL)
		quit_error(scene, (plog(ERROR, "Missing color attribute !") & 0) | 1);
	split = str_split(str, ",");
	if (strl_len(split) != 3)
	{
		strl_free(&split);
		quit_error(scene, ((plog(ERROR, \
			"Invalid color format ! Expected r,g,b") & 0) | 1));
	}
	result.x = ft_atof(split[0]);
	result.y = ft_atof(split[1]);
	result.z = ft_atof(split[2]);
	if (result.x > 255 || result.y > 255 || result.z > 255 \
		|| result.x < 0 || result.y < 0 || result.z < 0)
		quit_error(scene, ((plog(ERROR, "Invalid color format ! " \
			"Expected range [0-255]") & 0) | 1));
	strl_free(&split);
	return (result);
}

double	parse_double(t_scene *scene, char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		quit_error(scene, (plog(ERROR, "Missing double value !") & 0) | 1);
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '.')
			quit_error(scene, ((plog(ERROR, \
				"Invalid double format ! Expected +0.0") & 0) | 1));
	return (ft_atof(str));
}

bool	parse_scene(t_engine *engine, char *path)
{
	t_counts	counts;
	char		*line;
	char		**parameters;
	int			fd;

	counts = (t_counts){0, 0};
	if (ft_strcmp(path + ft_strlen(path) - 3, ".rt"))
		return (plog(ERROR, "Invalid file extension ! Expected '.rt'") & 0);
	fd = open(path, O_EXCL | O_RDONLY);
	if (fd < 0)
		return (plog(ERROR, "Invalid file path !") & 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parameters = str_split(line, " \t\n\v\f\r");
		if (!is_empty_line(line) && line[0] != '#')
			parse_object(engine, parameters[0], parameters + 1, &counts);
		if (line != NULL)
			free(line);
		strl_free(&parameters);
		line = get_next_line(fd);
	}
	if (counts.cams == 0)
		quit_error(&engine->scene, plog(ERROR, "No camera in scene !") & 0);
	return (true);
}
