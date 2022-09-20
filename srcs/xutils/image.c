/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:09:26 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/19 14:40:08 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xutils.h"

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

	if (x < 0 || x > image.width || y < 0 || y > image.height)
		return ;
	destination = image.addr;
	destination += x * image.bits_per_pixel / 8 + y * image.line_length;
	*(int *)destination = color;
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
