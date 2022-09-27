/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2022/09/27 16:37:56 by mrattez          ###   ########.fr       */
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
	if (keycode == ESC)
		quit(engine);
	return (0);
}

int	main(void)
{
	t_engine	engine;

	ft_bzero(&engine, sizeof(engine));
	engine.mlx = mlx_init();
	engine.win = mlx_new_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	engine.frame = new_image(engine.mlx, WIN_WIDTH, WIN_HEIGHT);

	engine.vw = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	engine.vh = 1;
	engine.vp_dist = engine.vw / tan(FOV * M_PI / 180 / 2);

	engine.scene.camera.position = (t_vec3){0, 0, 0};

	engine.scene.ambient_light.intensity = 0.2;

	t_light	*lightPoint = new_light_point((t_vec3){0, 0, 5}, .75, (t_vec3){255, 255, 255});
	ft_lstadd_back(&engine.scene.lights, ft_lstnew(lightPoint));

	t_sphere	*sphere = new_sphere((t_vec3){.5, 0, 10}, 1, (t_vec3){254, 74, 73});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(SPHERE, sphere)));

	sphere = new_sphere((t_vec3){-.5, 0, 10}, 1, (t_vec3){254, 215, 102});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(SPHERE, sphere)));

	sphere = new_sphere((t_vec3){0, 0, 5}, .025, (t_vec3){0xFF, 0xFF, 0xFF});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(SPHERE, sphere)));

	t_plane		*plane = new_plane((t_vec3){0, -2, 0}, (t_vec3){0, -1, 0}, (t_vec3){255, 0, 0});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	plane = new_plane((t_vec3){0, 2, 0}, (t_vec3){0, 1, 0}, (t_vec3){0, 255, 0});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	plane = new_plane((t_vec3){0, 0, 15}, (t_vec3){0, 0, 1}, (t_vec3){0, 0, 255});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	basic_raytracer(&engine);
	mlx_put_image_to_window(engine.mlx, engine.win, engine.frame.ptr, 0, 0);
	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_loop(engine.mlx);
}
