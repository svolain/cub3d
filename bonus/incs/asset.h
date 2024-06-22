/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:25:46 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/17 22:36:26 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSET_H
# define ASSET_H

# define GAME_ASSETS 15
# define GAME_COLORS 2
# define GAME_ANIMS 16

# define TEX_FLOOR		"./textures/floor.png"
# define TEX_ROOF		"./textures/roof.png"
# define TEX_DOOR		"./textures/door.png"
# define TEX_PLAYER		"./textures/player.png"
# define TEX_HEALTH		"./textures/pickup/health.png"
# define TEX_AMMO		"./textures/pickup/ammo.png"

# define TEX_GUN1		"./textures/gun/idle.png"
# define TEX_GUN2		"./textures/gun/shoot0.png"
# define TEX_GUN3		"./textures/gun/shoot1.png"
# define TEX_GUN4		"./textures/gun/shoot2.png"
# define TEX_GUN5		"./textures/gun/shoot3.png"
# define TEX_GUN6		"./textures/gun/reload0.png"
# define TEX_GUN7		"./textures/gun/reload1.png"
# define TEX_GUN8		"./textures/gun/reload2.png"
# define TEX_GUN9		"./textures/gun/reload3.png"
# define TEX_GUN10		"./textures/gun/reload4.png"
# define TEX_GUN11		"./textures/gun/reload5.png"
# define TEX_GUN12		"./textures/gun/reload6.png"
# define TEX_GUN13		"./textures/gun/reload7.png"
# define TEX_GUN14		"./textures/gun/reload8.png"
# define TEX_GUN15		"./textures/gun/reload9.png"

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
	IMG_HL
}	t_image;

typedef enum e_color
{
	COL_FL,
	COL_RF
}	t_color;

typedef enum e_weapon
{
	IMG_GO,
	IMG_G1,
	IMG_G2,
	IMG_G3,
	IMG_G4,
	IMG_G5,
	IMG_G6,
	IMG_G7,
	IMG_G8,
	IMG_G9,
	IMG_G10,
	IMG_G11,
	IMG_G12,
	IMG_G13,
	IMG_G14,
	IMG_G15
}	t_weapon;

#endif
