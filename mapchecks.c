/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:04:48 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/11 17:49:21 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    get_char_at(t_data *data, int x, int y)
{
    // printf("x %d and y %d\n", x, y);
    return(data->rawmaparray[y][x]);
}

void    set_char_at(t_data *data, int x, int y, char new)
{
    data->rawmaparray[y][x] = new;// might have leaks if i am overwriting it;
    printf("set char\n");
}

void    flood_fill(t_data *data, int x, int y)// do a seperate data rows and coloyumns also git gud
{
    size_t  width;
    size_t  height;
    char    current_char;
    printf("entered flood fill\n");
    printf("x = %d , y = %d\n", x, y);
     printf("string is %zu long\n",ft_strlen(data->rawmaparray[y]));
     printf("string is %s\n",data->rawmaparray[y]);
    if (x > data->coloumns || y > ft_strlen(data->rawmaparray[y]))//shit fucked yo
    {
        printf("error at floodfill width and height");
        return ;
    }
    int i = 0;
    while(data->rawmaparray[i])
    {
        printf("current array is %s\n", data->rawmaparray[i++]);
    }
    printf("getting char\n");
    current_char = get_char_at(data, x, y);
    printf("got char\n");
    if (current_char == '1' || current_char == 'F' || current_char == ' ')
        return;
    set_char_at(data, x, y, 'F');
    flood_fill(data, x + 1, y);
    flood_fill(data, x - 1, y);
    flood_fill(data, x, y + 1);
    flood_fill(data, x, y - 1);
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
    x = 1;
    printf("entered fill\n");
    printf("coloumns = %d\n", data->coloumns);
    printf("rows = %d\n", data->rows);
    while (x < data->rows + 1)
    {
        y = 1;
        while (y < data->coloumns)
        {
            printf("y is currently %d", y);
            printf("trying to access char at x %d and y %d\n", x, y);
            current = get_char_at(data, x, y);
            if (current == '0')
                flood_fill(data, x, y);
            y++;
            i = 0;
            while(data->rawmaparray[i])
            {
                printf("current array is %s\n", data->rawmaparray[i++]);
            }
        }
        x++;
    }
      printf("coloumns = %d\n", data->coloumns);
    printf("rows = %d\n", data->rows);
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
    while (data->rawmaparray[i])
    {
        j = 1;
        while(j < ft_strlen(data->rawmaparray[i]))
        {
            if (data->rawmaparray[i][j] == 'F')
            {
                if (is_valid_adjacent(data, i, j) == 1)
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
    if ((up == ' '|| down == ' ' || left == ' ' || right == ' '))
    {
        return (1);
        printf("error hassei\n");
    }
    return (0);
}