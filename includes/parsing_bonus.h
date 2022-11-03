/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:55:26 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/02 14:14:21 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

// STANDARD INCLUDES
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

// LIBRARY INCLUDES

// PROJECT INCLUDES
# include "minirt_bonus.h"
# include "utils.h"

typedef struct s_counts
{
	int	cams;
	int	ambients;
}	t_counts;

t_vec3	parse_vec3(t_scene *scene, char *str);
t_vec3	parse_color(t_scene *scene, char *str);
double	parse_double(t_scene *scene, char *str);

void	parse_ambient(t_scene *scene, char **params, t_counts *c);
void	parse_camera(t_scene *scene, char **params, t_counts *c);
void	parse_light(t_scene *scene, char **params);

void	parse_object(t_engine *e, char *type, char **param, t_counts *c);

#endif // PARSING_BONUS_H
