/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 14:38:00 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	int	i;

	i = 0;
	mlx_clear_window(data->mlx, data->win);
	freetextures(data);
	mlx_destroy_image(data->mlx, data->img[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	freecall(data->coordinates, data->rows + 3);
	while (data->fd_parsearray && data->fd_parsearray[i])
		free(data->fd_parsearray[i++]);
	i = 0;
	while (data->rawmaparray[i])
		free(data->rawmaparray[i++]);
	i = 0;
	while (data->squaremap && data->squaremap[i])
		free(data->squaremap[i++]);
	free(data->squaremap);
	free(data->fd_parsearray);
	free(data->mlx);
	free(data);
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
		close_window(data);
		exit(0);
	}
	else
		return (0);
}

int	ft_detectpoint(t_data *data, double nextx, double nexty)
{
	int	gridx;
	int	gridy;

	gridx = (int)(nextx / GRID_SIZE);
	gridy = (int)(nexty / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	return (0);
}

void	redraw_map(t_data *data)
{
	reinit_data(data);
	data->colours = 16711680;
	parse_map(data);
	castbeams(data);
	renderscene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	data->colours = 45000;
}

void	reinit_data(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img[0]);
	data->img[0] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img[0], &data->bits_per_pixel,
			&data->line_length, &data->endian);
}
