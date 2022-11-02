/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:17:48 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 11:18:46 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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