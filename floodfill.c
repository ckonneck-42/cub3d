/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:57:28 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 17:08:53 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_data *data, int x, int y)
{
	char	current_char;
	int		linenr;

	if (y == -1)
		y = 0;
	linenr = 0;
	linenr = get_nr_of_lines(data);
	if (y > linenr || data->squaremap[y][x] == '\n'
		|| data->squaremap[y][x] == '\0' || (x <= 0 || y <= 0))
		return ;
	if (x != 0)
	{
		current_char = get_char_at(data, x, y);
		if (current_char == '1' || current_char == 'F' || current_char == ' '
			|| current_char == '2' || current_char == 'N' || current_char == 'W'
			|| current_char == 'E' || current_char == 'S')
			return ;
		set_char_at(data, x, y, 'F');
		flood_fill(data, x + 1, y);
		flood_fill(data, x - 1, y);
		flood_fill(data, x, y + 1);
		flood_fill(data, x, y - 1);
	}
}

void	checktheplayer(t_data *data)
{
	int		x;
	int		y;

	x = (data->pos_x - 25) / GRID_SIZE;
	y = (data->pos_y - 25) / GRID_SIZE;
	flood_fill(data, x, y);
	if (is_valid_adjacent(data, x, y) == 1)
		clean_exit(data, "player is not within bounds");
}

void	fill_from_zero(t_data *data)
{
	unsigned long		x;
	int					y;
	char				current;
	int					linenr;
	int					k;

	y = 1;
	k = 1;
	linenr = 0;
	linenr = get_nr_of_lines(data);
	while (y < linenr)
	{
		x = 1;
		while (x < ft_strlen(data->squaremap[k]) - 1)
		{
			current = get_char_at(data, x, y);
			if (current == '0' || current == ' ')
				flood_fill(data, x, y);
			x++;
		}
		k++;
		y++;
	}
}

int	is_surrounded(t_data *data)
{
	size_t	player_x;
	size_t	player_y;
	size_t	i;
	size_t	j;

	player_x = data->pos_x - GRID_SIZE / 2;
	player_y = data->pos_y - GRID_SIZE / 2;
	complete_flood(data, player_x / GRID_SIZE, player_y / GRID_SIZE);
	i = 1;
	while (data->squaremap[i])
	{
		j = 1;
		while (j < ft_strlen(data->squaremap[i]) - 1)
		{
			if (data->squaremap[i][j] == 'F')
			{
				if (is_valid_adjacent(data, j, i) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
// if floodfill fails, try strlen -2

int	is_valid_adjacent(t_data *data, int x, int y)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = get_char_at(data, x - 1, y);
	down = get_char_at(data, x + 1, y);
	left = get_char_at(data, x, y - 1);
	right = get_char_at(data, x, y + 1);
	if (up == '2' || down == '2' || right == '2' || left == '2')
	{
		return (1);
	}
	return (0);
}
// printf("up %c\n", up);
// printf("down %c\n", down);
// printf("left %c\n", left);
// printf("right%c\n", right);
// printf("current map is\n");
// for (int i = 0; data->squaremap[i]; i++)
//     printf("%s\n", data->squaremap[i]);
