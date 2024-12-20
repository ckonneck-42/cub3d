/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:55:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/20 13:44:51 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freecall(t_Coordinate **coordinates, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(coordinates[i]);
		i++;
	}
	free(coordinates);
}

void	freedom(t_data *data, char *line)
{
	free(line);
	close_window(data);
}

void	clean_exit(t_data *data, char *errormessage)
{
	printf("Error\n%s\nexiting game\n" ,errormessage);
	close_window(data);
}

void	freetextures(t_data *data)
{
	if (data->northtxt)
	{
		free(data->northtxt);
		mlx_destroy_image(data->mlx, data->wall_texture[3].img);
		data->wall_texture[3].img = NULL;
	}
	if (data->westtxt)
	{
		free(data->westtxt);
		mlx_destroy_image(data->mlx, data->wall_texture[1].img);
		data->wall_texture[1].img = NULL;
	}
	if (data->easttxt)
	{
		free(data->easttxt);
		mlx_destroy_image(data->mlx, data->wall_texture[0].img);
		data->wall_texture[0].img = NULL;
	}
	if (data->southtxt)
	{
		free(data->southtxt);
		mlx_destroy_image(data->mlx, data->wall_texture[2].img);
		data->wall_texture[2].img = NULL;
	}
}
