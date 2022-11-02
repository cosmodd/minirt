/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:17:48 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 16:38:19 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_forward(t_engine *engine, int direction)
{
	t_vec3	d;

	d = vec3_scalar(engine->scene.camera.direction, direction);
	engine->scene.camera.position = vec3_add(engine->scene.camera.position, d);
	engine->scene.camera.view = mat4_lookat(engine->scene.camera.position, \
		vec3_add(engine->scene.camera.position, \
		engine->scene.camera.direction));
}

static void	move_right(t_engine *engine, int direction)
{
	t_vec3	d;
	t_vec3	u;
	t_vec3	wu;

	d = engine->scene.camera.direction;
	wu = (t_vec3){0, 1, 0};
	if (fabs(d.y) == 1)
		wu = (t_vec3){0, 0, 1};
	u = vec3_cross(d, wu);
	d = vec3_scalar(u, direction);
	engine->scene.camera.position = vec3_add(engine->scene.camera.position, d);
	engine->scene.camera.view = mat4_lookat(engine->scene.camera.position, \
		vec3_add(engine->scene.camera.position, \
		engine->scene.camera.direction));
}

static void	move_up(t_engine *engine, int direction)
{
	t_vec3	d;
	t_vec3	u;
	t_vec3	r;
	t_vec3	wu;

	d = engine->scene.camera.direction;
	wu = (t_vec3){0, 1, 0};
	if (fabs(d.y) == 1)
		wu = (t_vec3){0, 0, 1};
	r = vec3_normalize(vec3_cross(d, wu));
	u = vec3_normalize(vec3_cross(d, r));
	d = vec3_scalar(u, direction * -1);
	engine->scene.camera.position = vec3_add(engine->scene.camera.position, d);
	engine->scene.camera.view = mat4_lookat(engine->scene.camera.position, \
		vec3_add(engine->scene.camera.position, \
		engine->scene.camera.direction));
}

static void	rotate_up(t_engine *engine, int direction)
{
	static double	rot_angle = M_PI / 90;
	t_vec3			d;
	t_vec3			r;
	t_vec3			wu;

	d = engine->scene.camera.direction;
	wu = (t_vec3){0, 1, 0};
	if (fabs(d.y) == 1)
		wu = (t_vec3){0, 0, 1};
	r = vec3_normalize(vec3_cross(d, wu));
	engine->scene.camera.direction = vec3_rotate(\
		engine->scene.camera.direction, r, rot_angle * direction);
	engine->scene.camera.view = mat4_lookat(engine->scene.camera.position, \
		vec3_add(engine->scene.camera.position, \
		engine->scene.camera.direction));
}

int	key_hook(int keycode, t_engine *engine)
{
	static double	rot_angle = M_PI / 90;
	double			rot;

	if (keycode == KEY_ESC)
		quit(engine);
	if (keycode == KEY_W || keycode == KEY_S)
		move_forward(engine, (keycode == KEY_W) * 2 - 1);
	if (keycode == KEY_D || keycode == KEY_A)
		move_right(engine, (keycode == KEY_D) * 2 - 1);
	if (keycode == KEY_SPACE || keycode == KEY_CTRL)
		move_up(engine, (keycode == KEY_SPACE) * 2 - 1);
	if (keycode == KEY_L || keycode == KEY_J)
	{
		rot = (keycode == KEY_L) * 2 * rot_angle - rot_angle;
		engine->scene.camera.direction = vec3_rotate(\
			engine->scene.camera.direction, (t_vec3){0, 1, 0}, rot * -1);
		engine->scene.camera.view = mat4_lookat(engine->scene.camera.position, \
			vec3_add(engine->scene.camera.position, \
			engine->scene.camera.direction));
	}
	if (keycode == KEY_I || keycode == KEY_K)
		rotate_up(engine, (keycode == KEY_I) * 2 - 1);
	draw(engine);
	return (0);
}
