/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:28:24 by dyao              #+#    #+#             */
/*   Updated: 2024/12/21 19:47:23 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_all(t_data *data, int screenColumn)
{
	if ((int)data->final_point[screenColumn].x % GRID_SIZE == 0
		&& (int)data->final_point[screenColumn].y % GRID_SIZE == 0)
		draw_middle(data, screenColumn);
	else if (((int)data->final_point[screenColumn].x % GRID_SIZE == 0)
		&& data->final_point[screenColumn].x > data->pos_x)
		ft_draw_wall(data, screenColumn, 0);
	else if (((int)data->final_point[screenColumn].x % GRID_SIZE == 0)
		&& data->final_point[screenColumn].x < data->pos_x)
		ft_draw_wall(data, screenColumn, 1);
	else if (((int)data->final_point[screenColumn].y % GRID_SIZE == 0)
		&& data->final_point[screenColumn].y > data->pos_y)
		ft_draw_wall_2(data, screenColumn, 2);
	else if (((int)data->final_point[screenColumn].y % GRID_SIZE == 0)
		&& data->final_point[screenColumn].y < data->pos_y)
		ft_draw_wall_2(data, screenColumn, 3);
}

void	render3d(t_data *data, double distance,
		double cubeHeight, int screenColumn)
{
	if (screenColumn < 0 || screenColumn > data->screen_width)
		printf("Error: screenColumn (%d) out of bounds!\n", screenColumn);
	data->wallstarty = (data->screen_height / 2) - ((cubeHeight
				* (data->screen_width / 2) / tan(data->fov / 2)) / distance / 2);
	data->wallendy = (data->screen_height / 2) + ((cubeHeight
				* (data->screen_width / 2) / tan(data->fov / 2)) / distance / 2);
	data->walltotal = data->wallendy - data->wallstarty;
	data->wall_true_start_y = data->wallstarty;
	if (screenColumn < 500)
		if (data->wallstarty < 300)
			data->wallstarty = 300;
	if (data->wallstarty < 0)
		data->wallstarty = 0;
	if (data->wallendy > data->screen_height)
		data->wallendy = data->screen_height - 1;
	draw_all(data, screenColumn);
}

int	ft_detectgrid(t_data *data, double x, double y)
{
	int	gridx;
	int	gridy;

	gridx = (int)((x) / GRID_SIZE);
	gridy = (int)((y) / GRID_SIZE);
	if (data->check_x && data->check_y && (int)x == data->check_x
		&& (int)y == data->check_y)
		return (0);
	if (gridx < 0 || gridy < 0)
		return (0);
	if (gridx >= data->rows || gridy >= data->coloumns
		|| !data->coordinates[gridx])
		return (1);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	if (ft_detectgrid_2(data, x, y))
		return (1);
	data->check_x = (int)x;
	data->check_y = (int)y;
	return (0);
}

void	smallmap(t_data *data)
{
	double	x;
	double	a;
	double	y;
	double	b;

	a = 0;
	x = data->pos_x - 250;
	data->colours = 6666666;
	while (x <= (data->pos_x + 250))
	{
		y = data->pos_y - 150;
		b = 0;
		while (y <= data->pos_y + 150)
		{
			if (ft_detectgrid(data, x, y))
				my_mlx_pixel_put(data, a, b, 1);
			y += 1;
			b += 1;
		}
		x += 1;
		a += 1;
	}
	data->colours = 9999999;
	my_mlx_pixel_put(data, 250, 150, 10);
}

void	renderscene(t_data *data)
{
	int	screencolumn;

	screencolumn = 0;
	while (screencolumn < data->screen_width)
	{
		render3d(data, data->distanceahead[screencolumn],
			GRID_SIZE * 4 / 5, screencolumn);
		screencolumn++;
	}
	smallmap(data);
}
