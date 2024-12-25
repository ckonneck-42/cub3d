/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:55:58 by dyao              #+#    #+#             */
/*   Updated: 2024/12/22 17:10:10 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_other(t_data *data, int screenColumn)
{
	double	y;

	data->colours = data->floorcolor;
	y = data->wallendy;
	while (y < 1080)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y++;
	}
	data->colours = data->ceilingcolor;
	y = data->wallstarty;
	while (y > 0)
	{
		if (screenColumn < 500 && y < 300)
			data->colours = 0000000;
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y--;
	}
}

void	ft_draw_wall(t_data *data, int screenColumn, int i)
{
	double	tex_x;
	double	tex_y;
	double	y;

	tex_y = 0;
	tex_x = fmod(data->final_point[screenColumn].y, GRID_SIZE);
	y = data->wallstarty;
	while (y <= data->wallendy)
	{
		tex_y = (y - data->wall_true_start_y)
			* data->wall_texture[i].height / data->walltotal;
		data->colours = *(int *)(data->wall_texture[i].addr + ((int)tex_y
					* data->wall_texture[i].line_length
					+ (int)tex_x * (data->wall_texture[i].bpp / 8)));
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y++;
	}
	ft_draw_other(data, screenColumn);
	data->colours = 0;
	data->pre_color = *(int *)(data->wall_texture[i].addr + ((int)tex_y
				* data->wall_texture[i].line_length
				+ (int)tex_x * (data->wall_texture[i].bpp / 8)));
}

void	ft_draw_other_2(t_data *data, int screenColumn)
{
	double	y;

	data->colours = data->floorcolor;
	y = data->wallendy;
	while (y < 1080)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y++;
	}
	data->colours = data->ceilingcolor;
	y = data->wallstarty;
	while (y > 0)
	{
		if (screenColumn < 500 && y < 300)
			data->colours = 0000000;
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y--;
	}
}

void	ft_draw_wall_2(t_data *data, int screenColumn, int i)
{
	double	tex_x;
	double	tex_y;
	double	y;

	tex_y = 0;
	tex_x = fmod(data->final_point[screenColumn].x, GRID_SIZE);
	y = data->wallstarty;
	while (y <= data->wallendy)
	{
		tex_y = (y - data->wall_true_start_y)
			* data->wall_texture[i].height / data->walltotal;
		data->colours = *(int *)(data->wall_texture[i].addr + ((int)tex_y
					* data->wall_texture[i].line_length + (int)tex_x
					* (data->wall_texture[i].bpp / 8)));
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y++;
	}
	ft_draw_other_2(data, screenColumn);
	data->pre_color = *(int *)(data->wall_texture[i].addr + ((int)tex_y
				* data->wall_texture[i].line_length + (int)tex_x
				* (data->wall_texture[i].bpp / 8)));
}

void	draw_middle(t_data *data, int screenColumn)
{
	double	y;

	y = data->wallstarty;
	data->colours = data->pre_color;
	while (y <= data->wallendy)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y++;
	}
	data->colours = data->floorcolor;
	y = data->wallendy;
	while (y < 1080)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y++;
	}
	data->colours = data->ceilingcolor;
	y = data->wallstarty;
	while (y > 0)
	{
		if (screenColumn < 500 && y < 300)
			data->colours = 0000000;
		my_mlx_pixel_put(data, screenColumn, y, 1);
		y--;
	}
}
