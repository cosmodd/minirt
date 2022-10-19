/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:43 by mrattez           #+#    #+#             */
/*   Updated: 2022/10/19 14:33:03 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vec3(t_vec3 v)
{
	printf("(%10.5f, %10.5f, %10.5f)\n", v.x, v.y, v.z);
}

static char	*get_coll_type(t_object type)
{
	if (type == SPHERE)
		return ("⚪️ Sphere");
	else if (type == PLANE)
		return ("⬜️ Plane");
	else if (type == CYLINDER)
		return ("💊 Cylinder");
	return ("❓ Unknown");
}

static void	print_collideables(t_scene *scene)
{
	t_list			*lst;
	t_collideable	*coll;

	lst = scene->collideables;
	while (lst != NULL)
	{
		coll = lst->content;
		if (coll->type == SPHERE)
		{
			printf("\e[1;3;37;44m %s \e[0m\n", get_coll_type(coll->type));
			printf("POS: "); print_vec3(coll->sphere->position);
			printf("RAD: %.3f\n", coll->sphere->radius);
			printf("COL: "); print_vec3(coll->sphere->color);
		}
		else if (coll->type == PLANE)
		{
			printf("\e[1;3;37;44m %s \e[0m\n", get_coll_type(coll->type));
			printf("POS: "); print_vec3(coll->plane->position);
			printf("DIR: "); print_vec3(coll->plane->direction);
			printf("COL: "); print_vec3(coll->plane->color);
		}
		else if (coll->type == CYLINDER)
		{
			printf("\e[1;3;37;44m %s \e[0m\n", get_coll_type(coll->type));
			printf("POS: "); print_vec3(coll->cylinder->position);
			printf("DIR: "); print_vec3(coll->cylinder->direction);
			printf("DIA: %.3f\n", coll->cylinder->diameter);
			printf("RAD: %.3f\n", coll->cylinder->radius);
			printf("HGT: %.3f\n", coll->cylinder->height);
			printf("COL: "); print_vec3(coll->cylinder->color);
		}
		printf("------------------------\n");
		lst = lst->next;
	}
}

static void	print_lights(t_scene *scene)
{
	t_list	*lst;
	t_light	*light;

	lst = scene->lights;
	while (lst != NULL)
	{
		light = lst->content;
		printf("\e[1;3;37;44m 💡 Light \e[0m\n");
		printf("POS: "); print_vec3(light->position);
		printf("BRT: %.3f\n", light->intensity);
		printf("COL: "); print_vec3(light->color);
		printf("------------------------\n");
		lst = lst->next;
	}
}

static void	print_scene(t_scene *scene)
{
	printf("\e[1;3;37;44m 🎬 Scene \e[0m\n");
	printf("------------------------\n");
	printf("\e[1;3;37;44m 🌞 Ambient light \e[0m\n");
	printf("BRT: %.3f\n", scene->ambient_light.intensity);
	printf("COL: "); print_vec3(scene->ambient_light.color);
	printf("------------------------\n");
	printf("\e[1;3;37;44m 📷 Camera \e[0m\n");
	printf("POS: "); print_vec3(scene->camera.position);
	printf("DIR: "); print_vec3(scene->camera.direction);
	printf("FOV: %.3f\n", scene->camera.fov);
	printf("------------------------\n");
	print_lights(scene);
	print_collideables(scene);
}

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
		t_vec3	right = vec3_cross(engine->scene.camera.direction, (t_vec3){0, 1, 0});
		t_vec3	dir = vec3_scalar(right, (keycode == K_D) * 2 - 1);

		engine->scene.camera.position = vec3_add(engine->scene.camera.position, dir);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	if (keycode == K_J || keycode == K_L)
	{
		double	abs_angle = M_PI / 6;
		double	rot_angle = (keycode == K_L) * 2 * abs_angle - abs_angle;

		engine->scene.camera.direction = vec3_rotate(engine->scene.camera.direction, (t_vec3){0, 1, 0}, -rot_angle);
		engine->scene.camera.view = mat4_lookat(
			engine->scene.camera.position,
			vec3_add(engine->scene.camera.position, engine->scene.camera.direction)
		);
		basic_raytracer(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame.ptr, 0, 0);
	}
	if (keycode == K_I || keycode == K_K)
	{
		double	abs_angle = M_PI / 6;
		double	rot_angle = (keycode == K_K) * 2 * abs_angle - abs_angle;
		t_vec3	right = vec3_cross(engine->scene.camera.direction, (t_vec3){0, 1, 0});

		engine->scene.camera.direction = vec3_rotate(engine->scene.camera.direction, right, -rot_angle);
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

	ft_bzero(&engine, sizeof(engine));
	engine.mlx = mlx_init();
	engine.win = mlx_new_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
	engine.frame = new_image(engine.mlx, WIN_WIDTH, WIN_HEIGHT);

	engine.vw = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	engine.vh = 1;

	if (ac < 2)
	{
		plog(ERROR, "Not enough arguments ! Usage: ./minirt <scene.rt>");
		return (EXIT_FAILURE);
	}

	parse_scene(&engine, av[1]);
	engine.vp_dist = engine.vw / tan(engine.scene.camera.fov * M_PI / 180 / 2);

	print_scene(&engine.scene);

	basic_raytracer(&engine);
	mlx_put_image_to_window(engine.mlx, engine.win, engine.frame.ptr, 0, 0);

	mlx_key_hook(engine.win, key_hook, &engine);
	mlx_loop(engine.mlx);
}
