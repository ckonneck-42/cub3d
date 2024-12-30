/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:12:22 by dyao              #+#    #+#             */
/*   Updated: 2024/12/30 15:24:00 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == K_A)
		data->move_a = 1;
	else if (keycode == K_D)
		data->move_d = 1;
	else if (keycode == K_W)
		data->move_w = 1;
	else if (keycode == K_S)
		data->move_s = 1;
	else if (keycode == K_ARRRGT)
		data->look_right = 1;
	else if (keycode == K_ARRLFT)
		data->look_left = 1;
	else if (keycode == K_ARRUP)
		data->clearadd = 1;
	else if (keycode == K_ARRDWN)
		data->clearmin = 1;
	if (keycode == K_ESC)
	{
		close_window(data);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == K_A)
		data->move_a = 0;
	else if (keycode == K_D)
		data->move_d = 0;
	else if (keycode == K_W)
		data->move_w = 0;
	else if (keycode == K_S)
		data->move_s = 0;
	else if (keycode == K_ARRRGT)
		data->look_right = 0;
	else if (keycode == K_ARRLFT)
		data->look_left = 0;
	else if (keycode == K_ARRUP)
		data->clearadd = 0;
	else if (keycode == K_ARRDWN)
		data->clearmin = 0;
	return (0);
}

int	move(t_data *data)
{
	if (data->move_w == true)
		pressw(data);
	if (data->move_a == true)
		pressa(data);
	if (data->move_s == true)
		presss(data);
	if (data->move_d == true)
		pressd(data);
	if (data->look_right == true)
		data->a = fmod(data->a + 5.0, 360.0);
	if (data->look_left == true)
		data->a = fmod(data->a - 5.0 + 360.0, 360.0);
	if (data->clearadd == true)
	{
		if (data->clear < 5)
			data->clear++;
	}
	if (data->clearmin == true)
	{
		if (data->clear > 1)
			data->clear--;
	}
	redraw_map(data);
	return (0);
}

void	base_init3(t_data *data)
{
	data->textureflag = 0;
	data->westflag = 0;
	data->eastflag = 0;
	data->southflag = 0;
	data->northflag = 0;
	data->move_a = 0;
	data->move_d = 0;
	data->move_s = 0;
	data->move_w = 0;
	data->look_right = 0;
	data->look_left = 0;
	data->clearadd = 0;
	data->clearmin = 0;
}
