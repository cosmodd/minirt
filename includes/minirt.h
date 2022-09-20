/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:30:22 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/20 10:25:21 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// STANDARD
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

// LIBRARIES
# include "mlx.h"
# include "libft.h"

// OTHERS
# include "xutils.h"
# include "keys.h"

// CONSTANTS
# define WIN_WIDTH	960
# define WIN_HEIGHT	540

typedef struct s_engine
{
	void	*mlx;
	void	*win;
	t_image	frame;
}	t_engine;

#endif
