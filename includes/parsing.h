/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:55:26 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/14 10:43:04 by mrattez          ###   ########.fr       */
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

t_vec3	parse_vec3(char *str);
t_vec3	parse_color(char *str);
double	parse_double(char *str);

void	parse_object(t_engine *engine, char *type, char **parameters);

#endif // PARSING_H