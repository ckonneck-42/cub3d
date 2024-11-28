/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:32 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/28 15:46:16 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_detectpointbeam(float beamX, float beamY,t_data *data, double rad_angle)
{
	int gridX; 
	int gridY;
	gridX = (int)((beamX + cos(rad_angle)) / GRID_SIZE) ;
	gridY = (int)((beamY + sin(rad_angle)) / GRID_SIZE);
	if (data->coordinates[gridX][gridY].map == '1')
   		return(1);
	return(0);
}

void castbeams(t_data *data)
{
    double rad_angle_1 = data->a * (PI / 180.0);
	double rad_angle_2 = (data->a + 45) * (PI / 180.0);
	double rad_angle_3 = (data->a - 45) * (PI / 180.0);
    float beamX;
	float beamY;
	float beamX_2;
	float beamY_2;
	float beamX_3;
	float beamY_3;
	beamX = data->posX;
	beamY = data->posY;
	beamX_2 = data->posX;
	beamY_2 = data->posY;
	beamX_3 = data->posX;
	beamY_3 = data->posY;
	data->colours = 8388736;// purple for beam
	while ((beamX >= 0 && beamX <= 1920 && beamY >= 0 && beamY <= 1080 && ft_detectpointbeam(beamX, beamY, data, rad_angle_1) != 1))// beamX != wallline
	{
		my_mlx_pixel_put(data, beamX, beamY, 1);
		beamX += cos(rad_angle_1);
		beamY += sin(rad_angle_1);
	}
	while ((beamX_2 >= 0 && beamX_2 <= 1920 && beamY_2 >= 0 && beamY_2 <= 1080 && ft_detectpointbeam(beamX_2, beamY_2, data, rad_angle_2) != 1))// beamX_2 != wallline
	{
		my_mlx_pixel_put(data, beamX_2, beamY_2, 1);
		beamX_2 += cos(rad_angle_2);
		beamY_2 += sin(rad_angle_2);
	}
	while ((beamX_3 >= 0 && beamX_3 <= 1920 && beamY_3 >= 0 && beamY_3 <= 1080 && ft_detectpointbeam(beamX_3, beamY_3, data, rad_angle_3) != 1))// beamX_3 != wallline
	{
		my_mlx_pixel_put(data, beamX_3, beamY_3, 1);
		beamX_3 += cos(rad_angle_3);
		beamY_3 += sin(rad_angle_3);
	}
}