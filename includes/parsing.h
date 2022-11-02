/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:55:26 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 11:19:13 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// STANDARD INCLUDES
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

// LIBRARY INCLUDES

// PROJECT INCLUDES
# include "minirt.h"
# include "utils.h"

typedef struct s_counts
{
	int	cams;
	int	ambients;
}	t_counts;

t_vec3	parse_vec3(char *str);
t_vec3	parse_color(char *str);
double	parse_double(char *str);

void	parse_ambient(t_scene *scene, char **params, t_counts *c);
void	parse_camera(t_scene *scene, char **params, t_counts *c);
void	parse_light(t_scene *scene, char **params);

void	parse_object(t_engine *engine, char *type, char **param, t_counts *c);

#endif // PARSING_H