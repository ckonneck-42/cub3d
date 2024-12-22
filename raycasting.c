/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:32 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 14:27:54 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_detectpointbeam_2(double beamX, double beamY, t_data *data)
{
	int	gridx;
	int	gridy;

	gridx = (int)((beamX + 1) / GRID_SIZE);
	gridy = (int)(beamY / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	gridx = (int)((beamX) / GRID_SIZE);
	gridy = (int)((beamY + 1) / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	gridx = (int)((beamX - 1) / GRID_SIZE);
	gridy = (int)((beamY) / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	gridx = (int)((beamX) / GRID_SIZE);
	gridy = (int)((beamY - 1) / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	return (0);
}

int	ft_detectpointbeam(float beamX, float beamY, t_data *data)
{
	int	gridx;
	int	gridy;

	gridx = (int)((beamX) / GRID_SIZE);
	gridy = (int)((beamY) / GRID_SIZE);
	if (data->check_x && data->check_y && (int)beamX == data->check_x
		&& (int)beamY == data->check_y)
		return (0);
	if (gridx < 0 || gridy < 0)
		return (0);
	if (gridx >= data->rows || gridy >= data->coloumns
		|| !data->coordinates[gridx])
		return (1);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	if (ft_detectpointbeam_2(beamX, beamY, data))
		return (1);
	data->check_x = (int)beamX;
	data->check_y = (int)beamY;
	return (0);
}

void	dis_cal(t_data *data, double beamx, double beamy, int i)
{
	double	rad_angle_2;
	double	ang_mark;
	double	ang_2;

	ang_mark = data->a + 1920 * 0.02;
	ang_2 = 1920 * 0.04 + data->a - ang_mark - 0.04 * i;
	rad_angle_2 = ang_2 * (PI / 180.0);
	data->distanceahead[i] = (sqrt(pow(beamx - data->posX, 2)
				+ pow(beamy - data->posY, 2))) * cos(rad_angle_2);
	data->final_point[i].x = beamx;
	data->final_point[i].y = beamy;
}

void	find_beam_end(t_data *data, double beamx,
		double beamy, double rad_angle_1)
{
	while (1)
	{
		if ((int)beamx % GRID_SIZE == 0 || (int)beamy % GRID_SIZE == 0)
			if (ft_detectpointbeam(beamx, beamy, data) == 1
				&& ft_detectpointbeam(beamx -1, beamy - 1, data) == 1)
				break ;
		beamx += cos(rad_angle_1) / data->clear;
		beamy += sin(rad_angle_1) / data->clear;
	}
	data->beamx = beamx;
	data->beamy = beamy;
}

void	castbeams(t_data *data)
{
	double	rad_angle_1;
	double	ang;
	int		i;

	ang = data->a;
	i = 0;
	while (i < 1920)
	{
		ang = fmod(ang, 360.0);
		if (ang < 0)
			ang += 360.0;
		data->beamx = data->posX;
		data->beamy = data->posY;
		rad_angle_1 = ang * (PI / 180.0);
		find_beam_end(data, data->beamx, data->beamy, rad_angle_1);
		dis_cal(data, data->beamx, data->beamy, i);
		ang += 0.04;
		i++;
	}
}
