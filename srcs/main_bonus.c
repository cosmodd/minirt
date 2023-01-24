/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2023/01/24 11:06:53 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	quit_error(t_scene *scene, int plogret)
{
	if (scene->lights)
		ft_lstclear(&scene->lights, free);
	if (scene->collideables)
		ft_lstclear(&scene->collideables, free_collideable);
	exit(plogret);
}

int	quit(t_engine *engine)
{
	ft_lstclear(&engine->scene.lights, free);
	ft_lstclear(&engine->scene.collideables, free_collideable);
	destroy_image(engine->frame);
	mlx_destroy_window(engine->mlx, engine->win);
	exit(0);
	return (0);
}

void	draw(t_engine *engine)
{
	basic_raytracer(engine);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
}

int	loop(t_engine *engine)
{
	// When auto_cam is on, rotates the camera around the origin and looks at it
	if (engine->auto_cam)
	{
		engine->scene.camera.position = vec3_rotate(engine->scene.camera.position, (t_vec3){0, 1, 0}, (5 * M_PI) / 180);
		engine->scene.camera.direction = vec3_normalize(
			vec3_sub((t_vec3){0, 0, 0}, engine->scene.camera.position));
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		draw(engine);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_engine		engine = {0};

	if (ac != 2)
	{
		plog(ERROR, "Wrong number of arguments ! Usage: ./minirt <scene.rt>");
		return (EXIT_FAILURE);
	}
	ft_bzero(&engine, sizeof(engine));
	engine.mlx = mlx_init();
	engine.win = mlx_new_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	engine.frame = new_image(engine.mlx, WIN_WIDTH, WIN_HEIGHT);
	engine.vw = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	engine.vh = 1;
	if (!parse_scene(&engine, av[1]))
		return (EXIT_FAILURE);
	engine.vp_dist = (int)fmin(engine.vw, engine.vh) / tan(engine.scene.camera.fov * M_PI / 180 / 2);
	draw(&engine);
	mlx_do_key_autorepeaton(engine.mlx);
	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_hook(engine.win, 17, 0, quit, &engine);
	mlx_loop_hook(engine.mlx, loop, &engine);
	mlx_loop(engine.mlx);
}
