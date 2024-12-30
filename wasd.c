/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:00:49 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/30 14:46:17 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keycode, t_data *data)
{
	if (keycode == K_W)
		pressw(data);
	else if (keycode == K_A)
		pressa(data);
	else if (keycode == K_S)
		presss(data);
	else if (keycode == K_D)
		pressd(data);
	else if (keycode == K_ARRRGT)
		data->a = fmod(data->a + 5.0, 360.0);
	else if (keycode == K_ARRLFT)
		data->a = fmod(data->a - 5.0 + 360.0, 360.0);
	else if (keycode == K_ARRUP)
	{
		if (data->clear < 5)
			data->clear++;
	}
	else if (keycode == K_ARRDWN)
	{
		if (data->clear > 1)
			data->clear--;
	}
	redraw_map(data);
	return (0);
}

void	pressw(t_data *data)
{
	double	ang;
	double	nextx;
	double	nexty;

	ang = data->a + 1920 * 0.02;
	nextx = data->pos_x + cos(ang * (PI / 180.0)) * data->movespeed;
	nexty = data->pos_y + sin(ang * (PI / 180.0)) * data->movespeed;
	if (ft_detectpoint(data, nextx, nexty) != 1 && ft_detectpoint(data, nextx
			- 1, nexty - 1) != 1)
	{
		data->pos_x = nextx;
		data->pos_y = nexty;
	}
	else
		printf("You hit a wall\n");
}

void	presss(t_data *data)
{
	double	ang;
	double	nextx;
	double	nexty;

	ang = data->a + 1920 * 0.02;
	nextx = data->pos_x - cos(ang * (PI / 180.0)) * data->movespeed;
	nexty = data->pos_y - sin(ang * (PI / 180.0)) * data->movespeed;
	if (ft_detectpoint(data, nextx, nexty) != 1 && ft_detectpoint(data, nextx
			- 1, nexty - 1) != 1)
	{
		data->pos_x = nextx;
		data->pos_y = nexty;
	}
	else
		printf("You hit a wall\n");
}

void	pressa(t_data *data)
{
	double	ang;
	double	nextx;
	double	nexty;

	ang = data->a + 1920 * 0.02;
	nextx = data->pos_x + sin(ang * (PI / 180.0)) * data->movespeed;
	nexty = data->pos_y - cos(ang * (PI / 180.0)) * data->movespeed;
	if (ft_detectpoint(data, nextx, nexty) != 1 && ft_detectpoint(data, nextx
			- 1, nexty - 1) != 1)
	{
		data->pos_x = nextx;
		data->pos_y = nexty;
	}
	else
		printf("You hit a wall\n");
}

void	pressd(t_data *data)
{
	double	ang;
	double	nextx;
	double	nexty;

	ang = data->a + 1920 * 0.02;
	nextx = data->pos_x - sin(ang * (PI / 180.0)) * data->movespeed;
	nexty = data->pos_y + cos(ang * (PI / 180.0)) * data->movespeed;
	if (ft_detectpoint(data, nextx, nexty) != 1 && ft_detectpoint(data, nextx
			- 1, nexty - 1) != 1)
	{
		data->pos_x = nextx;
		data->pos_y = nexty;
	}
	else
		printf("You hit a wall\n");
}
