/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:32 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/03 15:55:26 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_detectpointbeam(float beamX, float beamY, t_data *data, double rad_angle)
{
    // Calculate grid indices
    int gridX = (int)((beamX + cos(rad_angle)) / GRID_SIZE);
    int gridY = (int)((beamY + sin(rad_angle)) / GRID_SIZE);
	// printf("BeamX: %.2f, BeamY: %.2f -> GridX: %d, GridY: %d\n", 
    //    beamX, beamY, gridX, gridY);
    // Ensure gridX and gridY are within bounds
    if (gridX < 0 || gridY < 0)
    {
        // Out of bounds, no collision detected
        return 0;
    }
	char mapVal = data->coordinates[gridY][gridX].map; // Assuming row-major order
	// printf("MapVal: %c at [%d][%d]\n", mapVal, gridY, gridX);
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
    float beamX;
	float beamY;
	data->colours = 8388736;// purple for beam
	double	ang = data->a - 30;
	int i = 0;
	
	while (i < 1920)
	{
		beamX = data->posX;
		beamY = data->posY;
		double rad_angle_1 = ang * (PI / 180.0);
		while ((beamX >= 0 && beamX <= 1920 && beamY >= 0 && beamY <= 1080 && ft_detectpointbeam(beamX, beamY, data, rad_angle_1) != 1))// beamX != wallline
		{
			my_mlx_pixel_put(data, beamX, beamY, 1);
			beamX += cos(rad_angle_1);
			beamY += sin(rad_angle_1);
		data->distanceahead[i] = sqrt(pow(beamX - data->posX, 2) + pow(beamY - data->posY, 2));
		}
		ang += 0.04;
		i++;
	}
	// while ((beamX_2 >= 0 && beamX_2 <= 1920 && beamY_2 >= 0 && beamY_2 <= 1080 && ft_detectpointbeam(beamX_2, beamY_2, data, rad_angle_2) != 1))// beamX_2 != wallline
	// {
	// 	my_mlx_pixel_put(data, beamX_2, beamY_2, 1);
	// 	beamX_2 += cos(rad_angle_2);
	// 	beamY_2 += sin(rad_angle_2);
	// }
	// 	data->distanceright = sqrt(pow(beamX_2 - data->posX, 2) + pow(beamY_2 - data->posY, 2));
	// while ((beamX_3 >= 0 && beamX_3 <= 1920 && beamY_3 >= 0 && beamY_3 <= 1080 && ft_detectpointbeam(beamX_3, beamY_3, data, rad_angle_3) != 1))// beamX_3 != wallline
	// {
	// 	my_mlx_pixel_put(data, beamX_3, beamY_3, 1);
	// 	beamX_3 += cos(rad_angle_3);
	// 	beamY_3 += sin(rad_angle_3);
	// }
	// 	data->distanceleft = sqrt(pow(beamX_3 - data->posX, 2) + pow(beamY_3 - data->posY, 2));
		
	// printf("beam distanceahead = %f\n",data->distanceahead);

	
	// printf("beam distanceleft = %f\n",data->distanceleft);
	// printf("beam distanceright = %f\n",data->distanceright);
}