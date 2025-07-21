/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:54:57 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 15:08:36 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"
# include "cub3d_define.h"

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				set;
}			t_color;

typedef struct s_coord
{
	float	x;
	float	y;
}			t_coord;

typedef struct s_coord_int
{
	int	x;
	int	y;
}		t_coord_int;

typedef struct s_door
{
	t_coord_int	pos;
	int			is_opening;
	float		open_state;
}				t_door;

typedef struct s_ray
{
	float	angle;
	float	length;
	int		target_type;
	int		target_orientation;
	float	target_column;
}			t_ray;

typedef struct s_inter
{
	t_coord	hor;
	t_coord	ver;
	t_coord	step;
	t_coord	tile_step;
}			t_inter;

typedef struct s_player
{
	t_coord	pos;
	float	angle;
	int		pitch;
}			t_player;

typedef struct s_sprite
{
	int		type;
	int		frame;
	int		frame_nb;
	t_coord	pos;
	t_ray	ray_to_sprite;
	float	distance;
	int		is_in_sight;
}			t_sprite;

typedef struct s_texture
{
	char		*path;
	t_coord_int	size;
	void		*img;
	int			bpp;
	int			line_size;
	int			endian;
	char		*buf;
}				t_texture;

typedef struct s_display
{
	void		*mlx;
	void		*win;
	t_texture	img;
	t_texture	minimap;
	t_texture	wall_n;
	t_texture	wall_e;
	t_texture	wall_s;
	t_texture	wall_w;
	t_texture	door;
	t_texture	flashlight;
	t_texture	phone;
	t_texture	overlay;
	t_texture	the_thing;
	t_texture	battery;
	t_texture	skybox;
	t_texture	exit;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_display;

typedef struct s_key
{
	int	m_up;
	int	m_down;
	int	m_left;
	int	m_right;
	int	r_left;
	int	r_right;
	int	r_up;
	int	r_down;
}		t_key;

typedef struct s_game
{
	char		**map;
	t_ray		**ray;
	t_coord_int	map_size;
	t_player	*player;
	t_display	*display;
	t_key		key_pressed;
	int			flashlight;
	t_coord_int	flashlight_offset;
	int			mini_map;
	t_list		*sprite;
	t_list		*door;
	t_list		*thing_path;
	float		battery_lvl;
	int			space_bar;
	int			start_time;
	char		*fps;
	int			sky;
	int			thing_exist;
	int			pursuit;
}				t_game;

/////////////////////	DISPLAY
//	display
void		ft_display(t_game *game);
void		ft_free_rays(t_ray **ray);
//	ceiling
void		ft_display_ceiling(t_game *game, t_coord_int pixel);

//	floor
void		ft_display_floor(t_game *game, t_coord_int pixel);
//	wall
void		ft_display_wall(t_game *game, t_coord_int pixel, int wall_size);

//	flashlight
void		ft_flashlight(t_game *game, float ray_len, char *buf,
				t_coord_int pixel);
t_coord_int	ft_flashlight_offset(t_coord_int flashlight_offset);
//	minimap
void		ft_draw_phone(t_texture *texture, char *buf);
void		ft_draw_minimap(t_game *game);
//	camera_overlay
void		ft_draw_camera_overlay(t_game *game);
//	sprite
void		ft_display_sprite(t_game *game);
// sprite_utils
t_texture	ft_get_sprite_texture(t_game *game, t_sprite *sprite);
int			ft_find_sprite_center(t_game *game, t_list *lst);
t_list		*ft_find_farthest_sprite(t_list *lst, float *prev_max_dist);

/////////////////////	RAYCASTER
//	raycaster
t_ray		**ft_raycaster(t_game *game);
//	ray_intersection
void		ft_find_ray_intersection(t_game *game, t_ray *ray, t_inter *inter);
//	ray_collision
void		ft_find_ray_collision(t_game *game, t_ray *ray, t_inter *inter,
				int a_correction);
//	ray_collision_door
int			ft_hor_collision_door(t_game *game, t_ray *ray, t_inter *inter,
				float angle);
int			ft_ver_collision_door(t_game *game, t_ray *ray, t_inter *inter,
				float angle);
//	ray_collision_wall
int			ft_hor_collision_wall(t_game *game, t_ray *ray, t_inter *inter,
				float angle);
int			ft_ver_collision_wall(t_game *game, t_ray *ray, t_inter *inter,
				float angle);

/////////////////////	GAME
//	exit
int			ft_exit(t_game *game);
void		ft_free_display_path(t_display *display);

//	initialization
t_game		*ft_initialization(char *filename);
// init_textures
t_texture	ft_init_texture(void *mlx, t_texture tx);
int			ft_import_constant_textures(t_display *display);
int			ft_import_textures(t_display *display);

//	game_event
void		ft_game_event(t_game *game);
//	battery
void		ft_drain_battery(t_game *game);
void		ft_flashlight_flicker(t_game *game);
void		ft_pick_battery(t_game *game);

//	thing_behavior
int			ft_the_thing_behavior(t_game *game);

//	thing_behavior_2
void		ft_move_the_thing(char **map, t_coord *pos, t_coord_int *dest);
t_list		*ft_del_current_node(t_sprite *thing, t_list *path);
t_coord_int	ft_get_destination(t_game *game, t_coord_int origin);

//	doors
t_coord_int	ft_find_door_to_open(t_game *game);
void		ft_set_door_as_opening(t_game *game, t_coord_int door_pos);
void		ft_open_doors(t_game *game);
//	sprites
void		ft_check_if_mob_in_sight(t_game *game);

/////////////////////	INPUT
//	input
void		ft_input(t_game *game);
//	player_movement
int			ft_player_move(t_game *game, t_player *player, int x_dir, int i);
int			ft_player_move_side(t_game *game, t_player *ply, int y_dir);
void		ft_player_rotate(t_game *game, int dir);
void		ft_player_pitch(t_game *game, int dir);
//	game_event.x
void		ft_game_event(t_game *game);

/////////////////////	PATHFINDER
//	pathfinder.c
t_list		*ft_pathfinder(char **map, t_coord_int *origin, t_coord_int *dest);
int			ft_check_path_exist(char **map, t_coord_int *origin,
				t_coord_int *destination);
//	pathfinder_optimize.c
t_list		*ft_optimize_path(char **map, t_list *path);
t_list		*ft_find_node(t_list *node, int x, int y);
//	pathfinder_utils.c
int			ft_check_redundancy(char **map, t_coord_int *position);
void		ft_clean_map(char **map, char c);
char		**ft_floodfill(char **map, int x, int y, char new_c);
void		ft_change_doors_to_space(char **map);
//	pathfinder_utils_2.c
t_coord_int	ft_find_direction(t_coord_int *current, t_coord_int *dest);
t_coord_int	*ft_get_best_move_2(char **map, t_coord_int *new_pos,
				t_coord_int dir);
t_coord_int	*ft_get_best_move(char **map, t_coord_int *pos, t_coord_int *dest);
int			ft_check_path_exist(char **map, t_coord_int *origin,
				t_coord_int *dest);
char		**ft_arrdup(char **arr);

/////////////////////	UTILS
float		ft_normalize_angle(float angle);
void		ft_pixel_dup(char *buf, char *texture);
void		ft_pixtobuf(char *buf, int red, int green, int blue);
void		ft_normalize_target(t_coord *target, t_texture *texture);
char		*ft_newline(char *line);

/////////////////////	PARSING
//	parsing
int			ft_parsing(t_game *game, char *filename, int fd);

// create_map
char		**ft_create_map(t_list *lst);
// parse_map_utils
void		ft_free_map(char **map, int i);

// parse_thing
void		ft_set_thing_start(t_list *lst, t_coord_int pos);
int			ft_check_map_thing_pos(t_game *game);
// parse_door
int			ft_init_doors(char **map, t_list **lst);

// parse_player
int			ft_check_map_player_pos(t_game *game);

// parse_battery
t_list		*ft_create_batteries(char **map, t_list *lst);

// parse_color
int			ft_init_color(t_color *color, char *str);

// parse_map
int			ft_check_map_validity(t_game *game);

// parse_textures
t_display	*ft_parse_texture(t_list **lst);
void		ft_free_game_display_path(t_display *display);

void		ft_display_double_char(char **arr);
void		ft_display_list_content(t_list *lst);

#endif
