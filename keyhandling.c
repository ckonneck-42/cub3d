/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/26 12:51:27 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img[0]);
	mlx_destroy_image(data->mlx, data->img[1]);
	mlx_destroy_image(data->mlx, data->img[2]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}


int	ft_close(int keycode, t_data *data)
{
	int	i;

	if (keycode == K_ALT)
	{
		i = 0;
		while (i < 10)
		{
			ft_printf("i love tudor\n");
			i++;
		}
	}
	if (keycode == K_ESC)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img[0]);
		mlx_destroy_image(data->mlx, data->img[1]);
		mlx_destroy_image(data->mlx, data->img[2]);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	else
		return (0);
}


int	keypress(int keycode, t_data *data)
{
	if (keycode == K_W)
	{
		data->posX += data->dirX * data->movespeed;
		data->posY += data->dirY * data->movespeed;
		printf("%f\n", data->posX);
	}
	else if (keycode == K_A)
	{
		data->posX -= data->planeX * data->movespeed;
		data->posY -= data->planeY * data->movespeed;
	}
	else if (keycode == K_S)
	{
		data->posX -= data->dirX * data->movespeed;
		data->posY -= data->dirY * data->movespeed;
	}
	else if (keycode == K_D)
	{
		data->posX += data->planeX * data->movespeed;
		data->posY += data->planeY * data->movespeed;
	}
	// draw_map(data, data->filename);
	return (0);
}
