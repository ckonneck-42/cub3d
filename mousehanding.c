/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:47:06 by dyao              #+#    #+#             */
/*   Updated: 2024/12/20 20:55:45 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mouse_press(int button, int x, int y, t_data *data)
{
    if (button == 1)
        drawgun(data, 1);
    return (0);
}

int mouse_release(int button, int x, int y, t_data *data)
{
    if (button == 1)
		drawgun(data, 0);
    return (0);
}

int	mousemovement(int button, int x, int y, t_data *data)
{
	// mlx_mouse_move(data->mlx, data->win, 1920 / 2, 1080 / 2);
	// printf("this is button: %d, this is a: %d\n", button, data->a);
	if (button == 3 && data->fire == 0)
		data->fire = 1;
	else if (button == 3 && data->fire == 1)
		data->fire = 0;
	while (1)
	{
		mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
		// printf("this is x: %d, this is y: %d\n", x, y);
		if (x > 1920)
			x = 1920;
		else if (x < 0)
			x = 0;
		if (x < 930)
		{
			data->a += (x - 960) * 0.04;
			redraw_map(data);
		}
		else if (x > 990)
		{
			data->a += (x - 960) * 0.04;
			redraw_map(data);
		}
		else
			break ;
	}
	redraw_map(data);
	return (0);
}

// int	mousemovement(t_data *data)
// {
// 	int x;
// 	int y;
// 	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
// 	// printf("this is x: %d, this is y: %d\n", x, y);
// 	if (x > 1920)
// 		x = 1920;
// 	else if (x < 0)
// 		x = 0;
// 	if (x < 930)
// 	{
// 		data->a += (x - 960) * 0.04;
// 		redraw_map(data);
// 	}
// 	else if (x > 990)
// 	{
// 		data->a += (x - 960) * 0.04;
// 		redraw_map(data);
// 	}
// 	else
// 		return (0);

// 	return (0);
// }
