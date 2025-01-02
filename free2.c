/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:11:54 by ckonneck          #+#    #+#             */
/*   Updated: 2025/01/02 11:28:40 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	xpm_clean_exit(t_data *data, char *errormessage)
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
	free(data->fd_parsearray);
	free(data->mlx);
	free(data);
	exit(0);
}

void	tex_clean_exit(t_data *data, char *errormessage)
{
	int	i;

	printf("Error\n%s\nexiting game\n", errormessage);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	if (data->northflag == 1)
		free(data->northtxt);
	if (data->westflag == 1)
		free(data->westtxt);
	if (data->eastflag == 1)
		free(data->easttxt);
	if (data->southflag == 1)
		free(data->southtxt);
	i = 0;
	while (data->fd_parsearray && data->fd_parsearray[i])
		free(data->fd_parsearray[i++]);
	free(data->fd_parsearray);
	free(data->mlx);
	free(data);
	exit(0);
}

void	main_exit(t_data *data, char *errormessage)
{
	printf("Error\n%s\nexiting game\n", errormessage);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}
