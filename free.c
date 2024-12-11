/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:55:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/11 13:00:51 by ckonneck         ###   ########.fr       */
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
