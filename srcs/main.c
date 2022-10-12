/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/12 10:34:38 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	print_vec3(t_vec3 v)
// {
// 	printf("(%10.5f, %10.5f, %10.5f)\n", v.x, v.y, v.z);
// }

// void	print_mat4(t_mat4 mat)
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (i == 0)
// 			printf("┌ ");
// 		else if (i == 3)
// 			printf("└ ");
// 		else
// 			printf("│ ");
// 		for (int j = 0; j < 4; j++)
// 		{
// 			printf("%10.5f", mat.m[i][j]);
// 			if (j < 3)
// 				printf(", ");
// 		}
// 		if (i == 0)
// 			printf(" ┐");
// 		else if (i == 3)
// 			printf(" ┘");
// 		else
// 			printf(" │");
// 		printf("\n");
// 	}
// }

void	quit(t_engine *engine)
{
	ft_lstclear(&engine->scene.lights, free);
	ft_lstclear(&engine->scene.collideables, free_collideable);
	destroy_image(engine->frame);
	mlx_destroy_window(engine->mlx, engine->win);
	// system("leaks minirt");
	exit(0);
}

int	key_hook(int keycode, t_engine *engine)
{
	if (keycode == ESC)
		quit(engine);
	if (keycode == K_W || keycode == K_S)
	{
		t_vec3	dir = vec3_scalar(engine->scene.camera.direction, (keycode == K_W) * 2 - 1);
		// printf("dir: %f %f %f\n", dir.x, dir.y, dir.z);
		// dir.x *= -1;
		// dir.z *= -1;
		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	if (keycode == K_A || keycode == K_D)
	{
		t_vec3	camdir = vec3_rotate(engine->scene.camera.direction, (t_vec3){0, 1, 0}, -M_PI_2);
		t_vec3	dir = vec3_scalar(camdir, (keycode == K_D) * 2 - 1);
		// dir.x *= -1;
		// dir.z *= -1;
		// printf("ir: %f %f %f\n", dir.x, dir.y, dir.z);
		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
	{
		double	abs_angle = M_PI / 6;
		double	rot_angle = (keycode == ARROW_RIGHT) * 2 * abs_angle - abs_angle;
		engine->scene.camera.direction = vec3_rotate(engine->scene.camera.direction, (t_vec3){0, 1, 0}, -rot_angle);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_engine		engine;
	t_collideable	*coll;

	ft_bzero(&engine, sizeof(engine));
	engine.mlx = mlx_init();
	engine.win = mlx_new_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	engine.frame = new_image(engine.mlx, WIN_WIDTH, WIN_HEIGHT);

	engine.vw = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	engine.vh = 1;
	engine.vp_dist = engine.vw / tan(FOV * M_PI / 180 / 2);

	engine.hfov = FOV * M_PI / 180;
	engine.vfov = 2 * atan(tan(engine.hfov / 2) * (engine.vh / engine.vw));

	engine.scene.camera.position = (t_vec3){14, -14, 14};
	// engine.scene.camera.position = (t_vec3){0, 0, 15};
	engine.scene.camera.direction = vec3_normalize((t_vec3){-2, 1, -2});
	// engine.scene.camera.direction = vec3_normalize((t_vec3){0, 0, -1});
	engine.scene.camera.view = mat4_lookat(
		engine.scene.camera.position,
		vec3_add(engine.scene.camera.position, engine.scene.camera.direction)
		// (t_vec3){2.5, 0, -10}
	);

	if (ac < 2)
	{
		plog(ERROR, "Not enough arguments ! Usage: ./minirt <scene.rt>");
		return (EXIT_FAILURE);
	}
	parse_scene(&engine, av[1]);

	// engine.scene.ambient_light.intensity = 0.2;

	// t_vec3	lightPosition = (t_vec3){0, -10, 0};

	// // Light
	// t_light	*lightPoint = new_light_point(lightPosition, .8, (t_vec3){0xFF, 0xFF, 0xFF});
	// ft_lstadd_back(&engine.scene.lights, ft_lstnew(lightPoint));

	// Light sphere
	// coll = new_sphere_col(lightPosition, .1, (t_vec3){0x0, 0x0, 0x0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Red sphere
	// coll = new_sphere_col((t_vec3){2.5, 0, -10}, 2, (t_vec3){254, 74, 73});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Yellow sphere
	// coll = new_sphere_col((t_vec3){-2.5, 0, -10}, 2, (t_vec3){254, 215, 102});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// coll = new_sphere_col((t_vec3){0, -7.5, 0}, 2, (t_vec3){254, 215, 102});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (floor)
	// coll = new_plane_col((t_vec3){0, -15, 0}, (t_vec3){0, 1, 0}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (ceiling)
	// coll = new_plane_col((t_vec3){0, 15, 0}, (t_vec3){0, -1, 0}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (front wall)
	// coll = new_plane_col((t_vec3){0, 0, -15}, (t_vec3){0, 0, 1}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (back wall)
	// coll = new_plane_col((t_vec3){0, 0, 15}, (t_vec3){0, 0, -1}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (right wall)
	// coll = new_plane_col((t_vec3){15, 0, 0}, (t_vec3){-1, 0, 0}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (left wall)
	// coll = new_plane_col((t_vec3){-15, 0, 0}, (t_vec3){1, 0, 0}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (diag wall)
	// coll = new_plane_col((t_vec3){-10, 0, -10}, (t_vec3){1, 0, 1}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (diag wall)
	// coll = new_plane_col((t_vec3){10, 0, -10}, (t_vec3){-1, 0, 1}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// // Gray plane (diag wall)
	// coll = new_plane_col((t_vec3){-10, 0, 10}, (t_vec3){1, 0, -1}, (t_vec3){0xF0, 0xF0, 0xF0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(coll));

	// basic_raytracer(&engine);

	// Put crosshair
	// for (int i = -5; i <= 5; i++)
	// {
	// 	t_vec2	hpos = (t_vec2){WIN_WIDTH / 2 + i, WIN_HEIGHT / 2};
	// 	t_vec2	vpos = (t_vec2){WIN_WIDTH / 2, WIN_HEIGHT / 2 + i};
	// 	int		hpixel = get_pixel(engine.frame, hpos.x, hpos.y);
	// 	int		vpixel = get_pixel(engine.frame, vpos.x, vpos.y);
	// 	put_pixel(engine.frame, hpos.x, hpos.y, 0xFFFFFF - hpixel);
	// 	put_pixel(engine.frame, vpos.x, vpos.y, 0xFFFFFF - vpixel);
	// }

	// mlx_put_image_to_window(engine.mlx, engine.win, engine.frame.ptr, 0, 0);
	// mlx_key_hook(engine.win, key_hook, &engine);
	// mlx_loop(engine.mlx);
}
