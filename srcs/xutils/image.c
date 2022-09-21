/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:09:26 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/21 10:31:05 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xutils.h"
#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_image	new_image(void *mlx, int width, int height)
{
	t_image	image;

	image.mlx = mlx;
	image.ptr = mlx_new_image(mlx, width, height);
	image.addr = mlx_get_data_addr(
			image.ptr,
			&image.bits_per_pixel,
			&image.line_length,
			&image.endian);
	image.width = width;
	image.height = height;
	return (image);
}

void	destroy_image(t_image image)
{
	if (image.ptr == NULL)
		return ;
	mlx_destroy_image(image.mlx, image.ptr);
}

void	put_pixel(t_image image, int x, int y, int color)
{
	char	*destination;

	if (x < 0 || x >= image.width || y < 0 || y >= image.height)
		return ;
	destination = image.addr;
	destination += x * image.bits_per_pixel / 8 + y * image.line_length;
	*(int *)destination = color;
}

/**
 * @brief Put a pixel on a coord system where (0,0) 
 * is a the center of the frame.
 * @param image 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel_canvas(t_image image, int x, int y, int color)
{
	int	cx;
	int	cy;

	cx = WIN_WIDTH * 0.5f + x;
	cy = WIN_HEIGHT * 0.5f - y;
	put_pixel(image, cx, cy, color);
}

int	get_pixel(t_image image, int x, int y)
{
	char	*source;

	if (x < 0 || x > image.width || y < 0 || y > image.height)
		return (0x0);
	source = image.addr;
	source += x * image.bits_per_pixel / 8 + y * image.line_length;
	return (*(int *)source);
}
