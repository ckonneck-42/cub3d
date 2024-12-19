/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:04:48 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/19 16:24:46 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    make_a_square(t_data *data)
{
    int i;
    int k;

    i = 0;
    k = 0;
    data->squaremap = malloc((data->coloumns + 1) * sizeof(char *));
    while(i < data->coloumns + 1)
    {
        data->squaremap[i] = malloc((data->rows + 2) * sizeof(char));
        ft_memset(data->squaremap[i], '2', data->rows + 2);
        data->squaremap[i][data->rows + 2] = '\0';
        i++;
    }
    make_btwo(data);
}

void    make_btwo(t_data *data)
{
    int i;
    int k;
    int len;
    i = 1;
    k = 0;
    while (i < data->coloumns)
    {
        len = ft_strlen(data->rawmaparray[k]);
        ft_memcpy(data->squaremap[i] + 1, data->rawmaparray[k], len - 1);
        data->squaremap[i][data->rows + 2] = '\0';
        i++;
        k++;
    }
}


char    get_char_at(t_data *data, int x, int y)
{
    return(data->squaremap[y][x]);
}

void    set_char_at(t_data *data, int x, int y, char new)
{
    data->squaremap[y][x] = new;// might have leaks if i am overwriting it;
}

int     get_nr_of_lines(t_data *data)
{
    int i;
    
    i = 0;
    while (data->squaremap[i])
    {
        i++;
    }
    return(i - 1);
}

void    flood_fill(t_data *data, int x, int y)
{
    size_t  width;
    size_t  height;
    char    current_char;
    int linenr;
    if(y == -1)
        y = 0;
    linenr = get_nr_of_lines(data);
    if (!data->squaremap[y][x])
        return ;
    if (y > linenr - 1 || data->squaremap[y][x] == '\n' || data->squaremap[y][x] == '\0' || (x <= 0 || y <= 0))
    {
        return ;
    }
    int i = 0;
    if (x != 0)
    {
        current_char = get_char_at(data, x, y);
        if (current_char == '1' || current_char == 'F' || current_char == ' ' || current_char == '2')
            return;
        set_char_at(data, x, y, 'F');
        flood_fill(data, x + 1, y);
        flood_fill(data, x - 1, y);
        flood_fill(data, x, y + 1);
        flood_fill(data, x, y - 1);
    }
}
void complete_flood(t_data *data,int x, int y)
{
    flood_fill(data, x, y);
    fill_from_zero(data);
}

void fill_from_zero(t_data *data)
{
    size_t  width, height;
    int  x, y;
    char    current;
    int i;
   
    y = 1;
    int k;
    int linenr;
    linenr = get_nr_of_lines(data);
    while (y < linenr - 2)
    {
        x = 1;
        k = 0;
        while (x < ft_strlen(data->squaremap[k]) - 2)
        {
            current = get_char_at(data, x, y);
            if (current == '0')
                flood_fill(data, x, y);
            x++;
            i = 0;
        }
        k++;
        y++;
    }
}

int is_surrounded(t_data *data)
{
    size_t  player_x;
    size_t  player_y;
    size_t  i;
    size_t  j;

    player_x = data->posX;
    player_y = data->posY;
    complete_flood(data, player_x/50, player_y/50);
    i = 1;
    while (data->squaremap[i])
    {
        j = 1;
        while(j < ft_strlen(data->squaremap[i]) )
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

int is_valid_adjacent(t_data *data, int x, int y)
{
    char    up;
    char    down;
    char    left;
    char    right;
    up = get_char_at(data, x - 1, y);
    down = get_char_at(data, x + 1, y);
    left = get_char_at(data, x, y - 1);
    right = get_char_at(data, x, y + 1);
    if (up == '2' || down == '2' || right == '2' || left == '2')
    {
        return(1);
    }
    return (0);
}

void    restore_map(t_data *data)
{
    int i;
    int k;
    i = 0;
    k = 0;
    while(data->squaremap[i])
    {
        k = 0;
        while (data->squaremap[i][k])
        {
            if (data->squaremap[i][k] == 'F')
                data->squaremap[i][k] = '0';
            k++;
        }
        i++;
    }
}


// 1111
// 10N1001
// 1001
// 1001
// 1001
// 1111
// this still works. thats bad.