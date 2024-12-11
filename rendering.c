/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:48:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/11 17:56:01 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, float x, float y, int size)
{
	char	*dst;
	int		i;
	int		j;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && x + i < 1920 && y + j >= 0 && y + j < 1080)
			{
				dst = data->addr + ((int)(y + j) *data->line_length + (int)(x
							+ i) *(data->bits_per_pixel / 8));
				*(unsigned int *)dst = data->colours;
			}
			j++;
		}
		i++;
	}
}
void renderScene(t_data *data)
{
	
    // Loop through each column on the screen
    for (int screenColumn = 0; screenColumn < data->screenWidth; screenColumn++)
	{
		// data->playerAngle =
		// data->rayAngle = data->playerAngle - (data->FOV / 2) + (screenColumn * (data->FOV / data->screenWidth));
        // Calculate the distance to the wall, and then render the 3D projection for each column
         // Assuming you have this function to calculate the distance
        render3D(data, data->distanceahead[screenColumn], 20, screenColumn); // 50 is the cube height, change as needed
    }
	// parse_map(data->map, data);
}


// 1920 / 61
// 160
// 150
// i = 150
// i++;
void render3D(t_data *data, double distance, float cubeHeight, int screenColumn)
{
    if (screenColumn < 0 || screenColumn > data->screenWidth) {
        printf("Error: screenColumn (%d) out of bounds!\n", screenColumn);
        // return;
    }
    float projPlaneDist = (data->screenWidth / 2) / tan(data->FOV / 2);
    float projectedHeight = (cubeHeight * projPlaneDist) / distance;
    // printf(" Projectedplanedist %f\n", projPlaneDist);
    // Calculate start and end Y positions for the wall slice
    float wallStartY = (data->screenHeight / 2) - (projectedHeight / 2);
    float wallEndY = (data->screenHeight / 2) + (projectedHeight / 2);
    // printf("wallStartY: %d, wallEndY: %d\n", wallStartY, wallEndY);
    // Ensure wall slice is within screen bounds
    if (wallStartY < 0)
        wallStartY = 0;
    if (wallEndY > data->screenHeight)
        wallEndY = data->screenHeight - 1;
    // printf("this is the start y: %f, this is the end y: %f,  this is the distance: %f\n", wallStartY, wallEndY, distance);
    // printf("test");
    // Draw the vertical slice
    // printf("this is x: %d,  this is y: %d\n", data->final_point[screenColumn].x, data->final_point[screenColumn].y);
    if (data->final_point[screenColumn].x % 50 == 0 && data->final_point[screenColumn].y % 50 == 0)
        data->colours = data->pre_color;
    else if ((data->final_point[screenColumn].x % 50 == 0) && data->final_point[screenColumn].x > data->posX)   //east wall
    {
        data->colours = 9000000;
        data->pre_color = 9000000;
    }
    else if ((data->final_point[screenColumn].x % 50 == 0) && data->final_point[screenColumn].x < data->posX)   //west wall
    {
        data->colours = 7000000;
        data->pre_color = 7000000;
    }
    else if ((data->final_point[screenColumn].y % 50 == 0) && data->final_point[screenColumn].y > data->posY)   //south wall
    {
        data->colours = 5000000;
        data->pre_color = 5000000;
    }
    else if ((data->final_point[screenColumn].y % 50 == 0) && data->final_point[screenColumn].y < data->posY)   //north wall
    {
        data->colours = 3000000;
        data->pre_color = 3000000;
    }
    else
        data->colours = 6666666;
    // * distance* 0.0000001;
    if (distance == 999999)
    {
        data->colours = 0;
        for (float y = 0; y < data->screenHeight; y++)
            my_mlx_pixel_put(data, screenColumn, y, 1);
    }
    else
    {
        for (float y = wallStartY; y <= wallEndY; y++)
            my_mlx_pixel_put(data, screenColumn, y, 1);
        data->colours = 2222222;
        for (float y = wallEndY; y < 1080; y++)
            my_mlx_pixel_put(data, screenColumn, y, 1);
        data->colours = 8888888;
        for (float y = wallStartY; y > 0; y--)
            my_mlx_pixel_put(data, screenColumn, y, 1);
        data->colours = 0;
    }
    // printf("this is screencolumn: %d, this is the starty: %f, this is the endy: %f, this is the distance: %f\n", screenColumn, wallStartY, wallEndY, distance);
    // printf("screenheight: %d\n", data->screenHeight);
    //  printf("screenwidth: %d\n", data->screenWidth);
    // printf("FOV radians: %f\n", data->FOV);
}

void draw_cube(t_data *data, float x, float y)
{
	float targetx;
	float targety;
	float targetz;
	int i;
	data->colours = 500000;
	targetx = x + 50;
	while(x <= targetx)
	{
		my_mlx_pixel_put(data, x, y, 1);
		x++;
	}
	targety = y + 50;
	while(y <= targety)
	{	
		my_mlx_pixel_put(data, x, y, 1);
		y++;
	}
	targetx = x - 50;
	while(x >= targetx)
	{
		my_mlx_pixel_put(data, x, y, 1);
		x--;
	}
	targety = y - 50;
	while(y >= targety)
	{
		my_mlx_pixel_put(data, x, y, 1);
		y--;
	}
}

void	render_textures(char target, t_data *data, int x, int y)
{
	t_Cube cube;
	t_RaycastVars ray;
	cube.height = 256;

	if (target == '1' || target == '\n' || target == '\0')
	{
		// printf("drawing cube for x: %d, and y: %d\n", x/50, y/50);
		draw_cube(data, x, y);
	}
	// else if (target == '0')
	// 	my_mlx_pixel_put(data, x, y, 10);
	// 	// mlx_put_image_to_window(data->mlx, data->win, data->img[2],
	// 	// 	x, y);
	else if (target == 'N' && data->playerflag == 0)
	{
		// printf("saving player coords");
		data->posX = x+25;
		data->posY = y+25;
		data->playerflag = 1;
		// mlx_put_image_to_window(data->mlx, data->win, data->img[0],  if i dont update the screen it doesnt show
		// 	x, y);
	}
	//instead of doing prev_x, we just go square, we go up down left right, whatever, set amount of pixels
		 // Draw a white dot for the player
		//putplayer/camera here facing the right way ofc
	//also give 4 sets based on the NO SO WE shit orientation so that i load images based off of that.
	
	// else if (target == 'N')
	// 	render_player(data, x, y);
	// else if (target == 'Z')
	// 	render_enemy(game, x, y);
	// else if (target == 'C')
	// 	render_collectible(game, x, y);
	// else if (target == 'E')
	// 	render_exit(game, x, y);
}