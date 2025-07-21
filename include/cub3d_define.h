/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:06:14 by acronert          #+#    #+#             */
/*   Updated: 2025/07/21 14:52:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINE_H
# define CUB3D_DEFINE_H

// # define SUCCESS			0
// # define FAILURE			1

// # define DEG_TO_RAD			0.01745329251
// # define RAD_TO_DEG			57.295779513

// # define WALL				'1'
// # define DOOR_VER			'2'
// # define DOOR_HOR			'3'
// # define EXIT_WALL			'4'
// # define SPACE				'0'

// # define TARGET_N_WALL		1
// # define TARGET_S_WALL		2
// # define TARGET_W_WALL		3
// # define TARGET_E_WALL		4

// # define TARGET_TYPE_WALL	'W'
// # define TARGET_TYPE_EXIT	'X'
// # define TARGET_TYPE_DOOR	'D'

// # define ORIENTATION_N		'N'
// # define ORIENTATION_S		'S'
// # define ORIENTATION_E		'E'
// # define ORIENTATION_W		'W'

// //	KEY_BINDING
// # define MOVE_FORWARD		119		//	W
// # define MOVE_BACKWARD		115		//	S
// # define MOVE_LEFT			97		//	A
// # define MOVE_RIGHT			100		//	D
// # define ROTATE_LEFT		65361	//	left arrow
// # define ROTATE_RIGHT		65363	//	right arrow
// # define ROTATE_UP			65362	//	up arrow
// # define ROTATE_DOWN		65364	//	down arrow
// # define EXIT_KEY			65307	//	exit key
// # define C_KEY				99
// # define M_KEY				109
// # define PLUS_KEY			61
// # define MINUS_KEY			45
// # define SPACE_BAR			32

// //	GAME SETTINGS
// # define THING_SPEED		0.08
// # define MOVE_SPEED			0.12
// # define TURN_SPEED			0.000698132
// # define FOV				70
// # define DISPLAY_W			1400
// # define DISPLAY_H			1050
// # define NUMBER_OF_RAYS		DISPLAY_W
// # define HALF_DISP_WIDTH	700
// # define HALF_DISP_HEIGHT	525
// # define WALL_HEIGHT		2

// //	MINIMAP
// # define PHONE_HEIGHT		735
// # define PHONE_WIDTH		560
// # define PHONE_OFFSET_X		466
// # define PHONE_OFFSET_Y		315
// # define MINIMAP_HEIGHT		448
// # define MINIMAP_WIDTH		302
// # define MINIMAP_OFFSET_X	617
// # define MINIMAP_OFFSET_Y	432
// # define MINIMAP_ZOOM		25.0

// // BATTERY LEVEL
// # define BATTERY_WIDTH		54
// # define BATTERY_HEIGHT		25
// # define BATTERY_OFFSET_X	1215
// # define BATTERY_OFFSET_Y	158

// //	PATHFINDER
// # define VISITED 			125
// # define BACKTRACK 			126

// //	IMG
// # define BPP				32

// //	SPRITE TYPES
// # define TYPE_THING			1
// # define TYPE_BATTERY		2

// //	THREADS
// # define NUMBER_OF_THREADS	2



# define SUCCESS			0
# define FAILURE			1

# define DEG_TO_RAD			(M_PI / 180)
# define RAD_TO_DEG			(180 / M_PI)

# define WALL				'1'
# define DOOR_VER			'2'
# define DOOR_HOR			'3'
# define EXIT_WALL			'4'
# define SPACE				'0'

# define TARGET_N_WALL		1
# define TARGET_S_WALL		2
# define TARGET_W_WALL		3
# define TARGET_E_WALL		4

# define TARGET_TYPE_WALL	'W'
# define TARGET_TYPE_EXIT	'X'
# define TARGET_TYPE_DOOR	'D'

# define ORIENTATION_N		'N'
# define ORIENTATION_S		'S'
# define ORIENTATION_E		'E'
# define ORIENTATION_W		'W'

//	KEY_BINDING
# define MOVE_FORWARD		119		//	W
# define MOVE_BACKWARD		115		//	S
# define MOVE_LEFT			97		//	A
# define MOVE_RIGHT			100		//	D
# define ROTATE_LEFT		65361	//	left arrow
# define ROTATE_RIGHT		65363	//	right arrow
# define ROTATE_UP			65362	//	up arrow
# define ROTATE_DOWN		65364	//	down arrow
# define EXIT_KEY			65307	//	exit key
# define C_KEY				99
# define M_KEY				109
# define PLUS_KEY			61
# define MINUS_KEY			45
# define SPACE_BAR			32

//	GAME SETTINGS
# define THING_SPEED		0.08
# define MOVE_SPEED			0.12
# define TURN_SPEED			(0.04 * DEG_TO_RAD)
# define FOV				70
# define DISPLAY_W			1100
# define DISPLAY_H			800
# define NUMBER_OF_RAYS		DISPLAY_W
# define HALF_DISP_WIDTH	(DISPLAY_W / 2)
# define HALF_DISP_HEIGHT	(DISPLAY_H / 2)
# define WALL_HEIGHT		2

//	MINIMAP
# define PHONE_HEIGHT		(DISPLAY_H * 0.7)
# define PHONE_WIDTH		(DISPLAY_W * 0.4)
# define PHONE_OFFSET_X		(DISPLAY_W / 3)
# define PHONE_OFFSET_Y		(DISPLAY_H - PHONE_HEIGHT)
# define MINIMAP_HEIGHT		(0.61 * PHONE_HEIGHT)
# define MINIMAP_WIDTH		(0.54 * PHONE_WIDTH)
# define MINIMAP_OFFSET_X	(PHONE_OFFSET_X + 0.27 * PHONE_WIDTH)
# define MINIMAP_OFFSET_Y	(PHONE_OFFSET_Y + 0.16 * PHONE_HEIGHT)
# define MINIMAP_ZOOM		25.0

// BATTERY LEVEL
# define BATTERY_WIDTH		(DISPLAY_W * 0.03921)
# define BATTERY_HEIGHT		(DISPLAY_H * 0.02452)
# define BATTERY_OFFSET_X	(DISPLAY_W * 0.86764)
# define BATTERY_OFFSET_Y	(DISPLAY_H * 0.14986)

//	PATHFINDER
# define VISITED 			125
# define BACKTRACK 			126

//	IMG
# define BPP				32

//	SPRITE TYPES
# define TYPE_THING			1
# define TYPE_BATTERY		2

//	THREADS
# define NUMBER_OF_THREADS	2

#endif
