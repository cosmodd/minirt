/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2022/11/01 11:09:45 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quit(t_engine *engine)
{
	ft_lstclear(&engine->scene.lights, free);
	ft_lstclear(&engine->scene.collideables, free_collideable);
	destroy_image(engine->frame);
	mlx_destroy_window(engine->mlx, engine->win);
	// system("leaks minirt");
	exit(0);
	return (0);
}

static void	draw(t_engine *engine)
{
	static const int	crosshair_size = 10;
	static char			display_text[1024];

	basic_raytracer(engine);
	for (int i = -crosshair_size / 2; i < crosshair_size / 2; i++)
	{
		t_vec2	hpos = (t_vec2){
			i + (engine->frame.width / 2 - floor(crosshair_size / 2.0)),
			engine->frame.height / 2.0
		};
		t_vec2	vpos = (t_vec2){
			engine->frame.width / 2.0,
			i + (engine->frame.height / 2 - floor(crosshair_size / 2.0))
		};
		int	hp = get_pixel(engine->frame, hpos.x, hpos.y);
		int	vp = get_pixel(engine->frame, vpos.x, vpos.y);
		put_pixel(engine->frame, hpos.x, hpos.y, hp ^ 0xFFFFFF);
		put_pixel(engine->frame, vpos.x, vpos.y, vp ^ 0xFFFFFF);
	}
	mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	printf("Direction: (%f, %f, %f)\n", engine->scene.camera.direction.x, engine->scene.camera.direction.y, engine->scene.camera.direction.z);
	printf("Position: (%f, %f, %f)\n", engine->scene.camera.position.x, engine->scene.camera.position.y, engine->scene.camera.position.z);
	sprintf(display_text, "Direction: (%f, %f, %f)", engine->scene.camera.direction.x, engine->scene.camera.direction.y, engine->scene.camera.direction.z);
	mlx_string_put(engine->mlx, engine->win, 10, 20, 0xFFFFFF, display_text);
	sprintf(display_text, "Position: (%f, %f, %f)", engine->scene.camera.position.x, engine->scene.camera.position.y, engine->scene.camera.position.z);
	mlx_string_put(engine->mlx, engine->win, 10, 40, 0xFFFFFF, display_text);
}

int	key_hook(int keycode, t_engine *engine)
{
	static double	rotationAngle = M_PI / 90;
	
	if (keycode == KEY_ECHAP)
		quit(engine);
	if (keycode == KEY_W || keycode == KEY_S)
	{
		t_vec3	dir = vec3_scalar(engine->scene.camera.direction, (keycode == KEY_W) * 2 - 1);

		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		draw(engine);
	}
	if (keycode == KEY_A || keycode == KEY_D)
	{
		t_vec3	right = vec3_cross(engine->scene.camera.direction, (t_vec3){0, 1, 0});
		t_vec3	dir = vec3_scalar(right, (keycode == KEY_D) * 2 - 1);

		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		draw(engine);
	}
	if (keycode == KEY_SPACE || keycode == KEY_CTRL)
	{
		t_vec3	right = vec3_cross(engine->scene.camera.direction, (t_vec3){0, 1, 0});
		t_vec3	up = vec3_normalize(vec3_cross(engine->scene.camera.direction, right));
		t_vec3	dir = vec3_normalize(vec3_scalar(up, (keycode == KEY_CTRL) * 2 - 1));

		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		draw(engine);
	}
	if (keycode == KEY_J || keycode == KEY_L)
	{
		double	rot_angle = (keycode == KEY_L) * 2 * rotationAngle - rotationAngle;

		engine->scene.camera.direction = vec3_rotate(engine->scene.camera.direction, (t_vec3){0, 1, 0}, -rot_angle);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		draw(engine);
	}
	if (keycode == KEY_I || keycode == KEY_K)
	{
		double	rot_angle = (keycode == KEY_K) * 2 * rotationAngle- rotationAngle;
		t_vec3	right = vec3_cross(engine->scene.camera.direction, (t_vec3){0, 1, 0});

		if (fabs(engine->scene.camera.direction.y) == 1)
			right = vec3_cross(engine->scene.camera.direction, (t_vec3){0, 0, -engine->scene.camera.direction.y});
		right = vec3_normalize(right);
		engine->scene.camera.direction = vec3_rotate(engine->scene.camera.direction, right, -rot_angle);
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
	t_engine		engine;

	if (ac != 2)
	{
		plog(ERROR, "Not the right number of arguments ! Usage: ./minirt <scene.rt>");
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

	engine.vp_dist = engine.vw / tan(engine.scene.camera.fov * M_PI / 180 / 2);

	// print_scene(&engine.scene);

	draw(&engine);
	mlx_do_key_autorepeaton(engine.mlx);
	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_hook(engine.win, 17, 0, quit, &engine);
	mlx_loop(engine.mlx);
}
