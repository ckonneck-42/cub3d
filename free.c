/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:55:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 15:19:36 by ckonneck         ###   ########.fr       */
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
	printf("Error\n%s\nexiting game\n", errormessage);
	close_window(data);
}

void	freetextures(t_data *data)
{
	if (data->northtxt)
		free(data->northtxt);
	if (data->westtxt)
		free(data->westtxt);
	if (data->easttxt)
		free(data->easttxt);
	if (data->southtxt)
		free(data->southtxt);
	if (data->wall_texture[3].img)
		mlx_destroy_image(data->mlx, data->wall_texture[3].img);
	if (data->wall_texture[2].img)
		mlx_destroy_image(data->mlx, data->wall_texture[2].img);
	if (data->wall_texture[1].img)
		mlx_destroy_image(data->mlx, data->wall_texture[1].img);
	if (data->wall_texture[0].img)
		mlx_destroy_image(data->mlx, data->wall_texture[0].img);
}

void	seperate_clean_exit(t_data *data, char *errormessage)
{
	int	i;

	printf("Error\n%s\nexiting game\n", errormessage);
	mlx_clear_window(data->mlx, data->win);
	if (data->textureflag == 1)
		freetextures(data);
	mlx_destroy_image(data->mlx, data->img[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	i = 0;
	while (data->fd_parsearray && data->fd_parsearray[i])
		free(data->fd_parsearray[i++]);
	i = 0;
	while (data->rawmaparray[i])
		free(data->rawmaparray[i++]);
	i = 0;
	while (data->squaremap && data->squaremap[i])
		free(data->squaremap[i++]);
	if (data->squaremap)
		free(data->squaremap);
	free(data->fd_parsearray);
	free(data->mlx);
	free(data);
	exit(0);
}
