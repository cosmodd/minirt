/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xutils.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:07:46 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/21 10:31:16 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XUTILS_H
# define XUTILS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include "mlx.h"

typedef struct s_image
{
	void	*mlx;
	void	*ptr;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

t_image	new_image(void *mlx, int width, int height);
void	destroy_image(t_image image);

void	put_pixel(t_image image, int x, int y, int color);
void	put_pixel_canvas(t_image image, int x, int y, int color);
int		get_pixel(t_image image, int x, int y);
int		create_trgb(int t, int r, int g, int b);

#endif
