/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:55:57 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 16:02:01 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_scene(t_engine *engine, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	return (true);
}
