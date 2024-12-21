/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:31:30 by dyao              #+#    #+#             */
/*   Updated: 2024/12/21 17:37:11 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, int x, int y, int i)
{
	int	color;

	color = *(int *)(data->gun[i].addr + ((int)y
				* data->gun[i].line_length + (int)x * (data->gun[i].bpp / 8)));
	return (color);
}

void	drawgun(t_data *data, int i)
{
	int	start_x;
	int	x;
	int	start_y;
	int	y;

	x = 0;
	y = 0;
	start_y = 1080 - data->gun[i].height;
	start_x = 1920 - data->gun[i].width;
	while (start_x < 1920)
	{
		y = 0;
		start_y = 1080 - data->gun[i].height;
		while (start_y < 1080)
		{
			data->colours = get_color(data, x, y, i);
			if (data->colours != -16777216)
				my_mlx_pixel_put(data, start_x, start_y, 1);
			y++;
			start_y++;
		}
		x++;
		start_x++;
	}
	draw_cross(data);
}

void	draw_cross(t_data *data)
{
	int	start_x;
	int	start_y;
	int	i;

	i = 40;
	start_x = 1920 / 2 - 20;
	start_y = 1080 / 2;
	data->colours = 4500000;
	while (i)
	{
		my_mlx_pixel_put(data, start_x, start_y, 4);
		start_x++;
		i--;
	}
	i = 40;
	start_x = 1920 / 2;
	start_y = 1080 / 2 - 20;
	while (i)
	{
		my_mlx_pixel_put(data, start_x, start_y, 4);
		start_y++;
		i--;
	}
}
