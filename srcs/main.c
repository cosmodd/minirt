/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/22 12:30:25 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	quit(t_engine *engine)
{
	destroy_image(engine->frame);
	mlx_destroy_window(engine->mlx, engine->win);
	exit(0);
}

int	key_hook(int keycode, t_engine *engine)
{
	(void) engine;
	if (keycode == ESC)
		quit(engine);
	return (0);
}

int	main(void)
{
	t_engine	engine;

	engine.mlx = mlx_init();
	engine.win = mlx_new_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	engine.frame = new_image(engine.mlx, WIN_WIDTH, WIN_HEIGHT);
	basic_raytracer(engine.frame);
	mlx_put_image_to_window(engine.mlx, engine.win, engine.frame.ptr, 0, 0);
	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_loop(engine.mlx);
}
