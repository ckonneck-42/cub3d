/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:32 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/21 15:20:52 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data)
{
	t_RaycastVars ray = 
	{
    .screenWidth = 1920,
    .screenHeight = 1080,
    .posX = 22.0, .posY = 12.0, 
    .dirX = -1.0, .dirY = 0.0,
    .planeX = 0.0, .planeY = 0.66,
    .texWidth = 64, .texHeight = 64
	};

}
