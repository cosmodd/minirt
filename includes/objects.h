/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:48:50 by pforesti          #+#    #+#             */
/*   Updated: 2022/10/17 09:21:27 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "maths.h"
# include "libft.h"

typedef enum e_object
{
	PLANE = 0,
	SPHERE = 1,
	CYLINDER = 2,
}	t_object;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
	t_mat4	view;
}	t_camera;

/* Lights	*/
/*	- intensity cannot be greater than 1.	*/
typedef struct s_ambient
{
	double	intensity;
	t_vec3	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3	position;
	double	intensity;
	t_vec3	color;
}	t_light;

/* Objects	*/
typedef struct s_sphere
{
	t_vec3	position;
	double	radius;
	t_vec3	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	position;
	t_vec3	direction;
	double	radius;
	double	diameter;
	double	height;
	t_vec3	color;
}	t_cylinder;

/* Other */
typedef struct s_collideable
{
	t_object	type;
	double		(*intersect)();
	union {
		void		*ptr;
		t_sphere	*sphere;
		t_plane		*plane;
		t_cylinder	*cylinder;
	};
	t_vec3		color;
}	t_collideable;

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient_light;
	t_list		*collideables;
	t_list		*lights;
}	t_scene;

t_light			*new_light_point(t_vec3 pos, double intensity, t_vec3 color);
void			free_collideable(void *ptr);
t_plane			*new_plane(t_vec3 position, t_vec3 direction, t_vec3 color);
t_collideable	*new_plane_col(t_vec3 position, t_vec3 direction, t_vec3 color);
double			intersect_plane(t_vec3 camera, t_vec3 raydir, t_plane *plane);
t_sphere		*new_sphere(t_vec3 position, double radius, t_vec3 color);
t_collideable	*new_sphere_col(t_vec3 position, double radius, t_vec3 color);
double			intersect_sphere(t_vec3 cam, t_vec3 raydir, t_sphere *sphere);
t_cylinder 		*new_cylinder(t_vec3 position, t_vec3 direction, double radius, double height, t_vec3 color);
t_collideable	*new_cylinder_col(t_vec3 position, t_vec3 direction, double diameter, double height, t_vec3 color);
double			intersect_cylinder(t_vec3 camera, t_vec3 raydir, t_cylinder *cyl);
#endif
