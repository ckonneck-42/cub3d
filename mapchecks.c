/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:04:48 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/12 17:04:00 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    get_char_at(t_data *data, int x, int y)
{
    printf("x %d and y %d\n", x, y);
    // printf("char at those coords is %c\n", data->rawmaparray[y][x]);
    return(data->rawmaparray[y][x]);
}

void    set_char_at(t_data *data, int x, int y, char new)
{
    data->rawmaparray[y][x] = new;// might have leaks if i am overwriting it;
}

int     get_nr_of_lines(t_data *data)
{
    int i;
    
    i = 0;
    while (data->rawmaparray[i])
    {
        i++;
    }
    // printf("returning i - 1 : %d\n", i -1 );
    return(i - 1);
}

void    flood_fill(t_data *data, int x, int y)// do a seperate data rows and coloyumns also git gud
{
    size_t  width;
    size_t  height;
    char    current_char;
    int linenr;
    if(y == -1)
        y = 0;
    // printf("entered flood fill\n");
    // printf("x = %d , y = %d\n", x, y);
    // printf("hello\n");
    //  printf("string is %zu long\n",ft_strlen(data->rawmaparray[y]));
    //  printf("string is %s\n",data->rawmaparray[y]);
    linenr = get_nr_of_lines(data);
    // if (y > linenr || (x > ft_strlen(data->rawmaparray[y]) - 2 ) || (x < 0 || y < 0))//shit fucked yo
    if (!data->rawmaparray[y][x])
        return ;
    if (y > linenr || data->rawmaparray[y][x] == '\n' || data->rawmaparray[y][x] == '\0' || (x <= 0 || y <= 0))
    {
        printf("error at floodfill width and height");
        return ;
    }
    int i = 0;
    // while(data->rawmaparray[i])
    // {
    //     printf("current array is %s\n", data->rawmaparray[i++]);
    // }
    if (x != 0)
    {
        current_char = get_char_at(data, x, y);
        if (current_char == '1' || current_char == 'F' || current_char == ' ')
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
    fill_from_zero(data); // implement bzero to put null everywhere after \n to make mapchecks viable for nullcheck, 
    //do it based on maximum length of the line + 1;
}

void fill_from_zero(t_data *data)
{
    size_t  width, height;
    int  x, y;
    char    current;
    int i;
    x = 1;
    int k;
    int linenr;
    linenr = get_nr_of_lines(data);
    printf("entered fill\n");
    // printf("coloumns = %d\n", data->coloumns);
    // printf("linenr = %d\n", linenr);
    k = 0;
    while (x < linenr)
    {
        y = 1;
        while (y < ft_strlen(data->rawmaparray[k]) - 1)
        {
            // printf("y is currently %d", y);
            // printf("trying to access char at x %d and y %d\n", x, y);
            current = get_char_at(data, x, y);
            printf("current char is in fill from zero %c\n", current);
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
        k++;
    }
    //   printf("coloumns = %d\n", data->coloumns);
    // printf("rows = %d\n", data->rows);
}
int is_surrounded(t_data *data)
{
    size_t  player_x;
    size_t  player_y;
    size_t  i;
    size_t  j;
    player_x = data->posX;
    player_y = data->posY;
    

    
    // i = 0;
    // while (data->rawmaparray[i])
    // {
    //     j = 0;
    //     while (data->rawmaparray[i][j])
    //     {
    //         printf("this is data->rawmaparray[%zu][%zu]: %c\n", i, j, data->rawmaparray[i][j]);
    //         j++;
    //     }
    //     i++;
    // }
    

    
    complete_flood(data, player_x/50, player_y/50);
    i = 1;
    while (data->rawmaparray[i])
    {
        j = 1;
        while(j < ft_strlen(data->rawmaparray[i]) )
        {
            if (data->rawmaparray[i][j] == 'F')
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
    printf("we in is valid adjacent\n");
    up = get_char_at(data, x - 1, y);
    printf("the char is %c\n", up);
    down = get_char_at(data, x + 1, y);
    printf("the char is %c\n", down);
    left = get_char_at(data, x, y - 1);
    printf("the char is %c\n", left);
    right = get_char_at(data, x, y + 1);
    printf("the char is %c\n", right);
    if ((up != 'F' && up != '1' && up != 'N') || 
    (down != 'F' && down != '1' && down != 'N') || 
    (left != 'F' && left != '1' && left != 'N') || 
    (right != 'F' && right != '1' && right != 'N'))
    {
        printf("error hassei\n");
        return (1);
    }
    return (0);
}


// 1111
// 10N1001
// 1001
// 1001
// 1001
// 1111
// this still works. thats bad.