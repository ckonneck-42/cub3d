/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:32 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/20 16:23:45 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int ft_detectpointbeam(float beamX, float beamY, t_data *data, double rad_angle)
// {
// // Calculate grid indices

// 	// if ((int)beamX % GRID_SIZE == 0 || (int)beamY % GRID_SIZE == 0)
// 	// 	return (1);
//     int gridX = (int)((beamX + cos(rad_angle)) / GRID_SIZE);
//     int gridY = (int)((beamY + sin(rad_angle)) / GRID_SIZE);

// 	// Ensure gridX and gridY are within bounds
//     if (gridX < 0 || gridY < 0)
//     {
//         // Out of bounds, no collision detected
//         return 0;
//     }

// 	if (gridX >= data->rows || gridY >= data->coloumns || !data->coordinates[gridX])
// 		return (1);

// 	// Check for wall at the grid location
// 	if (data->coordinates[gridX][gridY].map == '1')
// 		return 1;

// 	// No wall detected
// 	return 0;
// }

int ft_detectpointbeam(float beamX, float beamY, t_data *data, double rad_angle)
{
// Calculate grid indices
    if (data->check_x && data->check_y && (int)beamX == data->check_x && (int)beamY == data->check_y)
        return (0);
    // int gridX = (int)((beamX + cos(rad_angle)) / GRID_SIZE);
    // int gridY = (int)((beamY + sin(rad_angle)) / GRID_SIZE);
    int gridX = (int)((beamX) / GRID_SIZE);
    int gridY = (int)((beamY) / GRID_SIZE);
    // printf("this is beamX: %f, this is beamY: %f, this is gridX: %d, this is gridY: %d, this is the number: %c\n", beamX, beamY, gridX, gridY, data->coordinates[gridX][gridY].map);
  // Ensure gridX and gridY are within bounds
    if (gridX < 0 || gridY < 0)
    {
        // Out of bounds, no collision detected
        return 0;
    }
  if (gridX >= data->rows || gridY >= data->coloumns || !data->coordinates[gridX])
    return (1);
  // Check for wall at the grid location
  // if (data->coordinates[gridX][gridY].map == '1')
  //  return 1;
    if (data->coordinates[gridX][gridY].map == '1')
    return 1;
    gridX = (int)((beamX + 1) / GRID_SIZE);
    gridY = (int)(beamY / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
    return 1;
    gridX = (int)((beamX) / GRID_SIZE);
    gridY = (int)((beamY + 1) / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
    return 1;
    gridX = (int)((beamX - 1) / GRID_SIZE);
    gridY = (int)((beamY) / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
    return 1;
    gridX = (int)((beamX) / GRID_SIZE);
    gridY = (int)((beamY - 1) / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
    return 1;
    data->check_x = (int)beamX;
    data->check_y = (int)beamY;
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
    double  ang = data->a;
    double ang_mark = data->a + 1920 * 0.02;
    double ang_2 = 1920 * 0.04 + data->a - ang_mark;
    int i = 0;
    while (i < 1920)
    {
        ang = fmod(ang, 360.0);
        if (ang < 0)
            ang += 360.0;
        beamX = data->posX;
        beamY = data->posY;
        double rad_angle_1 = ang * (PI / 180.0);
        double rad_angle_2 = ang_2 * (PI / 180.0);
        while (beamX >= 0 && beamX <= 1920 && beamY >= 0 && beamY <= 1080)
        {
            if ((int)beamX % GRID_SIZE == 0 || (int)beamY % GRID_SIZE == 0)
                if (ft_detectpointbeam(beamX, beamY, data, rad_angle_1) == 1
                && ft_detectpointbeam(beamX -1, beamY - 1, data, rad_angle_1) == 1)
                    break ;
            my_mlx_pixel_put(data, beamX, beamY, 1);
            beamX += cos(rad_angle_1) / data->clear;
            beamY += sin(rad_angle_1) / data->clear;
        }
        data->final_point[i].x = beamX;
        data->final_point[i].y = beamY;
        data->distanceahead[i] = (sqrt(pow(beamX - data->posX, 2) + pow(beamY - data->posY, 2))) * cos(rad_angle_2);
        // printf("this is the beamX: %f, this is the beamY: %f, this is the distance %f\n", beamX, beamY, data->distanceahead[i]);
        ang += 0.04;
        ang_2 -= 0.04;
        i++;
    }
}