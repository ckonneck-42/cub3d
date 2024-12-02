/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:32 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/02 11:15:40 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_detectpointbeam(float beamX, float beamY, t_data *data, double rad_angle)
{
    // Calculate grid indices
    int gridX = (int)((beamX + cos(rad_angle)) / GRID_SIZE);
    int gridY = (int)((beamY + sin(rad_angle)) / GRID_SIZE);

    // Ensure gridX and gridY are within bounds
    if (gridX < 0 || gridY < 0 || gridX >= data->coloumns || gridY >= data->rows)
    {
        // Out of bounds, no collision detected
        return 0;
    }

    // Check for wall at the grid location
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;

    // No wall detected
    return 0;
}

// int	ft_detectpointbeam(float beamX, float beamY,t_data *data, double rad_angle) original function, unable to go oob
// {
// 	int gridX; 
// 	int gridY;
// 	gridX = (int)((beamX + cos(rad_angle)) / GRID_SIZE) ;
// 	gridY = (int)((beamY + sin(rad_angle)) / GRID_SIZE);
// 	if (data->coordinates[gridX][gridY].map == '1')
//    		return(1);
// 	return(0);
// }

void castbeams(t_data *data)
{
    double rad_angle_1 = data->a * (PI / 180.0);
	double rad_angle_2 = (data->a + 30) * (PI / 180.0);
	double rad_angle_3 = (data->a - 30) * (PI / 180.0);
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
		data->distanceahead = sqrt(pow(beamX - data->posX, 2) + pow(beamY - data->posY, 2));
	while ((beamX_2 >= 0 && beamX_2 <= 1920 && beamY_2 >= 0 && beamY_2 <= 1080 && ft_detectpointbeam(beamX_2, beamY_2, data, rad_angle_2) != 1))// beamX_2 != wallline
	{
		my_mlx_pixel_put(data, beamX_2, beamY_2, 1);
		beamX_2 += cos(rad_angle_2);
		beamY_2 += sin(rad_angle_2);
	}
		data->distanceright = sqrt(pow(beamX_2 - data->posX, 2) + pow(beamY_2 - data->posY, 2));
	while ((beamX_3 >= 0 && beamX_3 <= 1920 && beamY_3 >= 0 && beamY_3 <= 1080 && ft_detectpointbeam(beamX_3, beamY_3, data, rad_angle_3) != 1))// beamX_3 != wallline
	{
		my_mlx_pixel_put(data, beamX_3, beamY_3, 1);
		beamX_3 += cos(rad_angle_3);
		beamY_3 += sin(rad_angle_3);
	}
		data->distanceleft = sqrt(pow(beamX_3 - data->posX, 2) + pow(beamY_3 - data->posY, 2));
	renderScene(data);
		
	// printf("beam distanceahead = %f\n",data->distanceahead);
	// printf("beam distanceleft = %f\n",data->distanceleft);
	// printf("beam distanceright = %f\n",data->distanceright);
}