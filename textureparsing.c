/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureparsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:36:01 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 15:54:00 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_the_texturepath(t_data *data, char *line, int k, char *ttf)
{
	int	i;

	i = 0;
	if (ft_strncmp(ttf, "NO", 2) == 0)
		parse_north(data, line, k, i);
	else if (ft_strncmp(ttf, "EA", 2) == 0)
		parse_east(data, line, k, i);
	else if (ft_strncmp(ttf, "WE", 2) == 0)
		parse_west(data, line, k, i);
	else if (ft_strncmp(ttf, "SO", 2) == 0)
		parse_south(data, line, k, i);
}

void	parse_north(t_data *data, char *line, int k, int i)
{
	data->northtxt = malloc(ft_strlen(line) + 1);
	while (line[k] == 'N' || line[k] == 'O' || line[k] == ' ')
		k++;
	while (line[k] != '\n')
		data->northtxt[i++] = line[k++];
	data->northtxt[i] = '\0';
	data->northflag = 1;
}

void	parse_east(t_data *data, char *line, int k, int i)
{
	data->easttxt = malloc(ft_strlen(line) + 1);
	while (line[k] == 'E' || line[k] == 'A' || line[k] == ' ')
		k++;
	while (line[k] != '\n')
		data->easttxt[i++] = line[k++];
	data->easttxt[i] = '\0';
	data->eastflag = 1;
}

void	parse_west(t_data *data, char *line, int k, int i)
{
	data->westtxt = malloc(ft_strlen(line) + 1);
	while (line[k] == 'W' || line[k] == 'E' || line[k] == ' ')
		k++;
	while (line[k] != '\n')
		data->westtxt[i++] = line[k++];
	data->westtxt[i] = '\0';
	data->westflag = 1;
}

void	parse_south(t_data *data, char *line, int k, int i)
{
	data->southtxt = malloc(ft_strlen(line) + 1);
	while (line[k] == 'S' || line[k] == 'O' || line[k] == ' ')
		k++;
	while (line[k] != '\n')
		data->southtxt[i++] = line[k++];
	data->southtxt[i] = '\0';
	data->southflag = 1;
}
