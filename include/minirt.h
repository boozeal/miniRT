/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:28:04 by jbok              #+#    #+#             */
/*   Updated: 2023/04/09 20:08:06 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_vector.h"

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1280UL
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 720UL
# endif

# ifndef EPSILON
#  define EPSILON 0.0001
# endif

typedef union u_color		t_color;
typedef struct s_vec		t_vec;
typedef struct s_ray		t_ray;
typedef struct s_object		t_obj;
typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_viewport	t_viewport;
typedef struct s_image		t_image;
typedef struct s_texture	t_texture;
typedef struct s_normal		t_normal;

union u_color
{
	unsigned int	color;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
};

enum e_property
{
	E_PLANE = 1U,
	E_SPHERE = 1U << 1,
	E_CYLINDER = 1U << 2,
	E_CONE = 1U << 3,
	E_AMBIENT = 1U << 24,
	E_CAM = 1U << 25,
	E_LIGHT = 1U << 26,
	E_TEXTURE = 1U << 27,
	E_NORMAL = 1U << 28,
	E_ERROR = 1U << 29,
};

enum e_oper
{
	E_PLUS = 0,
	E_SUB,
	E_MUL,
	E_DOT,
	E_DIV,
};

struct s_vec
{
	float	x;
	float	y;
	float	z;
};

struct s_ray
{
	t_vec	origin;
	t_vec	dir;
};

struct s_object
{
	enum e_property	property;
	t_vec			origin;
	t_vec			dir;
	union
	{
		float	ratio;
		float	rad;
		float	width;
		float	fov;
	};
	union
	{
		t_color		color;
		int			aa;
	};
	t_texture		*texture;
	t_normal		*normal;
	float			height;
};

struct s_viewport
{
	t_obj	*cam;
	t_ray	*rays;
	t_color	*pixels;
	t_vec	horizonal;
	t_vec	vertical;
	ssize_t	w;
	ssize_t	h;
};

struct s_mlx
{
	void		*mlx;
	void		*win;
	int			*image;
	t_color		*addr;
	int			bit_per_pixel;
	int			line_length;
	int			endian;
};

struct s_data
{
	void		*mlx;
	t_viewport	viewport;
	t_obj		*ambient;
	t_vector	*objs;
	t_vector	*lights;
};

struct s_image
{
	void	*img;
	t_color	*addr;
	int		w;
	int		h;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
};

struct s_texture
{
	t_color	*map;
	int		w;
	int		h;
};

struct s_normal
{
	t_vec	*map;
	int		w;
	int		h;
};

// main.c

//	keyhook.c
int		window_closed(int x, t_mlx *mlx);
int		key_press(int keycode, t_mlx *mlx);

//	init.c
void	init_data(t_data *data, char *file);
void	init_viewport(t_viewport *viewport);
void	init_mlx(t_mlx *mlx, char *name);

//	vec
t_vec	vec_add(t_vec a, t_vec b);
t_vec	*_vec_add(t_vec *a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	*_vec_sub(t_vec *a, t_vec b);
float	vec_len(t_vec vec);
float	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_mul(t_vec vec, float f);
t_vec	*_vec_mul(t_vec *vec, float f);
t_vec	vec_norm(t_vec vec);
t_vec	*_vec_norm(t_vec *vec);

//	minirt_utils.c
float	ft_atof(char *s);
int		checkf(float a);
int		exit_msg(int n, char *str);
int		check_valid_str(char *str);

//	trace.c
float	solution_sphere(t_ray *ray, t_obj *s, float det);
float	solution_cylinder(t_ray	*ray, t_obj *s, float det, float *dis);
float	solution_cone(t_ray	*ray, t_obj *s, float det, float *dis);
float	get_det_sphere(t_ray *ray, t_obj *s);
float	get_det_plane(t_ray *ray, t_obj *s);
float	get_det_cylinder(t_ray *ray, t_obj *s);
float	get_det_cone(t_ray *ray, t_obj *s);
t_color	set_ambient(t_data *data, t_vec *vector, t_obj *obj);
t_color	cal_bright(t_data *data, t_vec nor_vec, t_vec con_vec, t_obj *obj);
float	get_det_subplane(t_ray *ray, t_obj *s, int flag, float *dis);
//	color.c
t_color	add_color(t_color a, t_color b);
t_color	*_add_color(t_color *a, t_color b);
t_color	mul_color(t_color a, float b);
t_color	*_mul_color(t_color *a, float b);
t_color	*_sub_color(t_color *a, t_color b);
t_color	dot_color(t_color a, t_color b);
t_color	*_dot_color(t_color *a, t_color b);
float	oper_color(unsigned char a, float b, int flag);
//	light.c
t_vec	get_incident_light(t_obj light, t_vec contact_vec);
t_color	get_diffuse(t_data *data, t_vec *vector, t_obj *obj, int i);
t_color	get_specular(t_data *data, t_vec *vector, int i);
int		cal_shadow(t_data *data, t_vec contact_vec, int i);
float	distance(t_obj *s, t_vec origin, t_vec dir);
//	vec_oper.c
t_vec	normalize_vec(t_vec vector);
t_vec	reflect_vec(t_vec normal_vector, t_vec incident_vec);
#endif
