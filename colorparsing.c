/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:40:03 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/21 14:57:36 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_colors(char *ttf, t_data *data)
{
	int		i;
	int		k;
	char	**temp;

	i = 0;
	k = 0;
	while (data->fd_parsearray[i])
	{
		while (data->fd_parsearray[i][k] == ' '
			|| data->fd_parsearray[i][k] == 9)
			k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 1) == 0)
		{
			parse_the_color(data, data->fd_parsearray[i], k, temp);
			data->flag++;
			return (1);
		}
		else
			k = 0;
		i++;
	}
	return (0);
}

void	parse_the_color(t_data *data, char *line, int k, char **temp)
{
	if (line[k] == 'F')
	{
		while (line[k] == 'F' || line[k] == ' ')
			k++;
		temp = ft_split(line + k, ',');
		if (assign_colors(temp, data) == 1)
			free_array(data, temp);
		data->floorcolor = (data->redc << 16)
			| (data->greenc << 8) | data->bluec;
	}
	else if (line[k] == 'C')
	{
		while (line[k] == 'C' || line[k] == ' ')
			k++;
		temp = ft_split(line + k, ',');
		if (assign_colors(temp, data) == 1)
			free_array(data, temp);
		data->ceilingcolor = (data->redc << 16)
			| (data->greenc << 8) | data->bluec;
	}
	k = 0;
	while (temp[k])
		free(temp[k++]);
	free(temp);
}

void	free_array(t_data *data, char **temp)
{
	int	k;

	k = 0;
	while (temp[k])
		free(temp[k++]);
	free(temp);
	if (data->northtxt)
		free(data->northtxt);
	if (data->westtxt)
		free(data->westtxt);
	if (data->easttxt)
		free(data->easttxt);
	if (data->southtxt)
		free(data->southtxt);
	seperate_clean_exit(data, "error colors");
}

int	assign_colors(char **temp, t_data *data)
{
	if (ft_isalnumwhole(temp[0]) == 0)
		data->redc = ft_atoi(temp[0]);
	else
	{
		return (1);
	}
	if (ft_isalnumwhole(temp[1]) == 0)
		data->greenc = ft_atoi(temp[1]);
	else
	{
		return (1);
	}
	if (ft_isalnumwhole(temp[2]) == 0)
		data->bluec = ft_atoi(temp[2]);
	else
	{
		return (1);
	}
	return (0);
}
