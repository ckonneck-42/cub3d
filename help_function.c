/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:54:14 by dyao              #+#    #+#             */
/*   Updated: 2024/12/15 16:26:25 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//this function's goal is to find the longest line of the map and return how long is that line, this will include the newline('\n').
int	ft_find_longest_line(char *map)
{
	int	i;
	int	j;
	int	keep_longest;

	i = 0;
	j = 0;
	keep_longest = 0;
	while (map[i])
	{
		j = i;
		while (map[j] != '\n' || map[j] != '\0')
			j++;
		if (keep_longest < (j - i))
			keep_longest = j - i;
		if (map[j] == '\n')
			i = j + 1;
		else
			i = j;
	}
	return (keep_longest);
}

//this function's goal is to find how many line in the map
int ft_find_lines(char *map)
{
    int i = 0;
    int line_count = 0;

    if (map[0] != '\0')
        line_count = 1;
    while (map[i])
    {
        if (map[i] == '\n')
            line_count++;
        i++;
    }
    return (line_count);
}

//this funciton's goal is to creat a map with empty '\0' inside.(this function over 25 line)
char	**ft_create_empty_map(char *map)
{
	int		longest_line;
	int		line_count;
	char	**output_map;
	int		i;

	line_count = ft_find_lines(map);
	longest_line = ft_find_longest_line(map);
	output_map = malloc((line_count + 1) * sizeof(char *));
	if (!output_map)
		return (NULL);
	output_map[line_count] = NULL;
	i = 0;
	while (i < line_count)
	{
		output_map[i] = malloc((longest_line + 1) * sizeof(char));
		if (!output_map[i])
		{
			while (i > 0)
				free(output_map[--i]);
			free(output_map);
			return (NULL);
		}
		ft_bzero(output_map[i], longest_line + 1);
		i++;
	}
	return (output_map);
}
