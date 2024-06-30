/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:25:46 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/28 12:19:52 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSET_BONUS_H
# define ASSET_BONUS_H

# define GAME_ASSETS 17
# define GAME_COLORS 2
# define GAME_SPRITES 2

# define TEX_FLOOR		"./textures/bonus/floor.png"
# define TEX_ROOF		"./textures/bonus/roof.png"
# define TEX_DOOR		"./textures/bonus/door.png"
# define TEX_PLAYER		"./textures/bonus/minimap/player.png"
# define TEX_HEALTH		"./textures/bonus/pickup/health.png"
# define TEX_AMMO		"./textures/bonus/pickup/ammo.png"

# define FRAMES_WEAPON 16

# define TEX_GUN1		"./textures/bonus/gun/idle.png"
# define TEX_GUN2		"./textures/bonus/gun/shoot0.png"
# define TEX_GUN3		"./textures/bonus/gun/shoot1.png"
# define TEX_GUN4		"./textures/bonus/gun/shoot2.png"
# define TEX_GUN5		"./textures/bonus/gun/shoot3.png"
# define TEX_GUN6		"./textures/bonus/gun/reload0.png"
# define TEX_GUN7		"./textures/bonus/gun/reload1.png"
# define TEX_GUN8		"./textures/bonus/gun/reload2.png"
# define TEX_GUN9		"./textures/bonus/gun/reload3.png"
# define TEX_GUN10		"./textures/bonus/gun/reload4.png"
# define TEX_GUN11		"./textures/bonus/gun/reload5.png"
# define TEX_GUN12		"./textures/bonus/gun/reload6.png"
# define TEX_GUN13		"./textures/bonus/gun/reload7.png"
# define TEX_GUN14		"./textures/bonus/gun/reload8.png"
# define TEX_GUN15		"./textures/bonus/gun/reload9.png"

# define FRAMES_PORTAL 8

# define TEX_GATE1		"./textures/bonus/portal/portal0.png"
# define TEX_GATE2		"./textures/bonus/portal/portal1.png"
# define TEX_GATE3		"./textures/bonus/portal/portal2.png"
# define TEX_GATE4		"./textures/bonus/portal/portal3.png"
# define TEX_GATE5		"./textures/bonus/portal/portal4.png"
# define TEX_GATE6		"./textures/bonus/portal/portal5.png"
# define TEX_GATE7		"./textures/bonus/portal/portal6.png"
# define TEX_GATE8		"./textures/bonus/portal/portal7.png"

typedef enum e_image
{
	IMG_NO,
	IMG_SO,
	IMG_WE,
	IMG_EA,
	IMG_DR,
	IMG_FL,
	IMG_RF,
	IMG_BG,
	IMG_FG,
	IMG_OL,
	IMG_MM,
	IMG_FV,
	IMG_PL,
	IMG_AM,
	IMG_HL,
	IMG_HD,
	IMG_FX,
	IMG_BASE = 0
}	t_image;

typedef enum e_color
{
	COL_FL,
	COL_RF
}	t_color;

typedef enum e_animation
{
	SPRT_WPN,
	SPRT_GATE
}	t_animation;

typedef enum e_sprstat
{
	SHOOT_WPN,
	MOVE_WPN
}	t_sprstat;

typedef enum e_weapon
{
	IMG_W1 = 1,
	IMG_W2,
	IMG_W3,
	IMG_W4,
	IMG_W5,
	IMG_W6,
	IMG_W7,
	IMG_W8,
	IMG_W9,
	IMG_W10,
	IMG_W11,
	IMG_W12,
	IMG_W13,
	IMG_W14,
	IMG_W15
}	t_weapon;

typedef enum e_portal
{
	IMG_P1 = 1,
	IMG_P2,
	IMG_P3,
	IMG_P4,
	IMG_P5,
	IMG_P6,
	IMG_P7,
}	t_portal;

#endif
