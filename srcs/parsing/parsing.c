/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:55:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/01 09:55:42 by pforesti         ###   ########.fr       */
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

t_vec3	parse_vec3(char *str)
{
	t_vec3	result;
	char	**split;
	
	split = str_split(str, ",");
	if (strl_len(split) != 3)
	{
		strl_free(&split);
		plog(ERROR, "Invalid vector format ! Expected x,y,z (check spaces)");
		exit(1);
	}
	result.x = ft_atof(split[0]);
	result.y = ft_atof(split[1]);
	result.z = ft_atof(split[2]);
	strl_free(&split);
	return (result);
}

t_vec3	parse_color(char *str)
{
	t_vec3	result;
	char	**split;
	
	split = str_split(str, ",");
	if (strl_len(split) != 3)
	{
		strl_free(&split);
		plog(ERROR, "Invalid color format ! Expected R,G,B (check spaces)");
		exit(1);
	}
	result.x = ft_atof(split[0]);
	result.y = ft_atof(split[1]);
	result.z = ft_atof(split[2]);
	strl_free(&split);
	return (result);
}

double	parse_double(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
		{
			plog(ERROR, "Invalid double format ! Expected a number");
			exit(1);
		}
		i++;
	}
	return (ft_atof(str));
}

bool	parse_scene(t_engine *engine, char *path)
{
	char	*line;
	char	**parameters;
	int		fd;

	if (ft_strcmp(path + ft_strlen(path) - 3, ".rt"))
	{
		plog(ERROR,"File suffix does not end with \".rt\"");
		return (false);
	}

	fd = open(path, O_EXCL | O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parameters = str_split(line, " \t\n\v\f\r");
		if (is_empty_line(line) || line[0] == '#')
		{
			line = get_next_line(fd);
			continue ;
		}
		parse_object(engine, parameters[0], parameters + 1);
		line = get_next_line(fd);
	}
	return (true);
}
