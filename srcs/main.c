/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/03 09:25:24 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_camera_orientation(t_engine *engine);

void	print_vec3(t_vec3 v)
{
	printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

void	print_mat4(t_mat4 mat)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
			printf("┌ ");
		else if (i == 3)
			printf("└ ");
		else
			printf("│ ");
		for (int j = 0; j < 4; j++)
		{
			printf("%f", mat.m[i][j]);
			if (j < 3)
				printf(", ");
		}
		if (i == 0)
			printf(" ┐");
		else if (i == 3)
			printf(" ┘");
		else
			printf(" │");
		printf("\n");
	}
}

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
	if (keycode == K_W || keycode == K_S)
	{
		t_vec3	dir = vec3_scalar(engine->scene.camera.direction, (keycode == K_W) * 2 - 1);
		// printf("dir: %f %f %f\n", dir.x, dir.y, dir.z);
		dir.x *= -1;
		// dir.z *= -1;
		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		draw_camera_orientation(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	if (keycode == K_A || keycode == K_D)
	{
		t_vec3	camdir = vec3_rotate(engine->scene.camera.direction, (t_vec3){0, 1, 0}, -M_PI_2);
		t_vec3	dir = vec3_scalar(camdir, (keycode == K_D) * 2 - 1);
		// dir.x *= -1;
		dir.z *= -1;
		// printf("ir: %f %f %f\n", dir.x, dir.y, dir.z);
		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		draw_camera_orientation(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	if (keycode == ARROW_RIGHT || keycode == ARROW_LEFT)
	{
		double	abs_angle = M_PI / 6;
		double	rot_angle = (keycode == ARROW_RIGHT) * 2 * abs_angle - abs_angle;
		engine->scene.camera.direction = vec3_rotate(engine->scene.camera.direction, (t_vec3){0, 1, 0}, rot_angle);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		draw_camera_orientation(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	return (0);
}

void	draw_line(t_image image, t_vec2 origin, t_vec2 dest, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = (int)floor(fabs(dest.x - origin.x));
	dy = (int)floor(fabs(dest.y - origin.y));
	sx = origin.x < dest.x ? 1 : -1;
	sy = origin.y < dest.y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		put_pixel(image, origin.x, origin.y, color);
		if (origin.x == dest.x && origin.y == dest.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			origin.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			origin.y += sy;
		}
	}
}

void	draw_camera_orientation(t_engine *engine)
{
	t_vec2	origin;
	t_vec2	forward;
	t_vec2	right;
	t_vec2	up;

	origin = (t_vec2){100, 100};
	forward.x = engine->scene.camera.view.m[0][2];
	forward.y = engine->scene.camera.view.m[1][2];
	right.x = engine->scene.camera.view.m[0][0];
	right.y = engine->scene.camera.view.m[1][0];
	up.x = engine->scene.camera.view.m[0][1];
	up.y = engine->scene.camera.view.m[1][1];
	forward = vec2_add(origin, vec2_scalar(forward, 100));
	right = vec2_add(origin, vec2_scalar(right, 100));
	up = vec2_add(origin, vec2_scalar(up, 100));

	forward.x = floor(forward.x);
	forward.y = floor(forward.y);
	right.x = floor(right.x);
	right.y = floor(right.y);
	up.x = floor(up.x);
	up.y = floor(up.y);

	printf("forward: (%f, %f)\n", forward.x, forward.y);
	printf("right: (%f, %f)\n", right.x, right.y);
	printf("up: (%f, %f)\n", up.x, up.y);
	
	draw_line(engine->frame, origin, forward, 0xFF0000);
	draw_line(engine->frame, origin, up, 0x00FF00);
	draw_line(engine->frame, origin, right, 0x0000FF);
}

int	main(void)
{
	t_engine	engine;
	t_sphere	*sphere;
	t_plane		*plane;

	ft_bzero(&engine, sizeof(engine));
	engine.mlx = mlx_init();
	engine.win = mlx_new_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	engine.frame = new_image(engine.mlx, WIN_WIDTH, WIN_HEIGHT);

	engine.vw = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	engine.vh = 1;
	engine.vp_dist = engine.vw / tan(FOV * M_PI / 180 / 2);

	engine.hfov = FOV * M_PI / 180;
	engine.vfov = 2 * atan(tan(engine.hfov / 2) * (engine.vh / engine.vw));

	engine.scene.camera.position = (t_vec3){0, 0, 0};
	engine.scene.camera.direction = vec3_normalize((t_vec3){0, 0, 1});
	engine.scene.camera.view = mat4_lookat(
		engine.scene.camera.position,
		// vec3_add(engine.scene.camera.position, engine.scene.camera.direction)
		(t_vec3){2, 2, 15}
	);

	engine.scene.ambient_light.intensity = 0.2;

	// Light
	t_light	*lightPoint = new_light_point((t_vec3){2, 2, 15}, .75, (t_vec3){255, 255, 255});
	ft_lstadd_back(&engine.scene.lights, ft_lstnew(lightPoint));

	// Light sphere
	sphere = new_sphere((t_vec3){2, 2, 15}, .1, (t_vec3){0xFF, 0xFF, 0xFF});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(SPHERE, sphere)));

	// Red sphere
	sphere = new_sphere((t_vec3){.75, 0, 10}, 1, (t_vec3){254, 74, 73});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(SPHERE, sphere)));

	// Yellow sphere
	sphere = new_sphere((t_vec3){-.75, 0, 10}, 1, (t_vec3){254, 215, 102});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(SPHERE, sphere)));

	// Gray plane (floor)
	plane = new_plane((t_vec3){0, -2, 0}, (t_vec3){0, 1, 0}, (t_vec3){0xF0, 0xF0, 0xF0});
	ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	// plane = new_plane((t_vec3){0, 2, 0}, (t_vec3){0, -1, 0}, (t_vec3){0, 255, 0});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	// plane = new_plane((t_vec3){0, 0, 15}, (t_vec3){0, 0, -1}, (t_vec3){0, 0, 255});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	// plane = new_plane((t_vec3){3, 0, 0}, (t_vec3){-1, 0, 0}, (t_vec3){0, 0, 255});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	// plane = new_plane((t_vec3){-3, 0, 0}, (t_vec3){1, 0, 0}, (t_vec3){0, 0, 255});
	// ft_lstadd_back(&engine.scene.collideables, ft_lstnew(to_collideable(PLANE, plane)));

	basic_raytracer(&engine);

	printf("Putting crosshair...\n");

	// Put crosshair
	for (int i = -5; i <= 5; i++)
	{
		printf("Pixel %d for crosshair\n", i);
		t_vec2	hpos = (t_vec2){WIN_WIDTH / 2 + i, WIN_HEIGHT / 2};
		t_vec2	vpos = (t_vec2){WIN_WIDTH / 2, WIN_HEIGHT / 2 + i};
		int		hpixel = get_pixel(engine.frame, hpos.x, hpos.y);
		int		vpixel = get_pixel(engine.frame, vpos.x, vpos.y);
		put_pixel(engine.frame, hpos.x, hpos.y, 0xFFFFFF - hpixel);
		put_pixel(engine.frame, vpos.x, vpos.y, 0xFFFFFF - vpixel);
	}

	printf("Drawing camera orientation...");
	draw_camera_orientation(&engine);
	printf("\r\e[2K✅ Camera rotation!\n");

	mlx_put_image_to_window(engine.mlx, engine.win, engine.frame.ptr, 0, 0);
	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_loop(engine.mlx);
}
