/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:54:14 by dyao              #+#    #+#             */
/*   Updated: 2024/12/15 18:29:29 by dyao             ###   ########.fr       */
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

//this function's goal is to find the start pos of map.
int	ft_find_map(char *str)
{
	int	i;
	int	j;
	int	keep;
	int	check;

	i = 0;
	while (str[i])
	{
		check = 0;
		keep = i;
		j = i;
		while (str[i] != '\n')
		{
			check = 1;//this means there are something in this line
			i++;
		}
		if (check == 1)
		{
			while (str[j] != '\n' && (str[j] == ' ' || str[j] == '\t' || str[j] == '1' || str[j] == '0'))
				j++;
			if (j == i)
				check = 2;//this means this line only contain ' ' || '\t' || '1' || '0' but there is a possiblity that this line dont have 0 or 1
			if (check == 2)
			{
				j = keep;
				while (str[j] != '\n' && (str[j] == ' ' || str[j] == '\t'))
					j++;
				if (j == i)
					check = 0;//this means this line only contain space or tab
				if (check == 2)
					return (keep);
			}
		}
		i++;
	}
	perror("No map here!\n");
	return (0);
}

//this function's goal is to find the end of the map and skip the new line after the map.
int	ft_find_map_end(char *str, int start)
{
	int	i;
	int	j;

	j = start;
	while (str[j])
	{
		i = j;
		while (str[j] != '\n' && str[j] != '\0')
			j++;
		if (i == j)
			return (i - 1);
		else if (str[j] == '\0')
			break ;
		else
			j++;
	}
	return (j);
}

//this function's goal is to copy the map into a string and output it for the better use.
char	*ft_return_full_map(char *str, int start, int end)
{
	char	*output_map;
	int		i;

	output_map = malloc((end - start + 2) * sizeof(char));
	if (!output_map)
		return (NULL);
	output_map[end - start + 1] = '\0';
	i = 0;
	while (str[start] && start <= end)
	{
		output_map[i] = str[start];
		i++;
		start++;
	}
	return (output_map);
}

//as the name, this function's goal is to copy the map
void	ft_copy_map(char **map_output, char *map_str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (map_str[i])
	{
		j = 0;
		while (map_str[i] != '\n' || map_str[i] != '\0')
		{
			map_output[k][j] = map_str[i];
			j++;
			i++;
		}
		if (map_str[i] == '\0')
			break ;
		i++;
		k++;
	}
}

//this function's goal is to output the map, after this function, we got a map that is correct and fill with \0 when not needed.
char	**ft_output_map(char *str)
{
	char	*map_str;
	char	**map_output;

	map_str = ft_return_full_map(str, ft_find_map(str), ft_find_map_end(str, ft_find_map(str)));//this might look creapy ( o _ 0 )
	map_output = ft_create_empty_map(map_str);
	ft_copy_map(map_output, map_str);
	return (map_output);
}
