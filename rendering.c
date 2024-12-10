/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:48:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/10 11:56:52 by ckonneck         ###   ########.fr       */
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
	int i;
	 if (screenColumn < 0 || screenColumn > data->screenWidth) {
        printf("Error: screenColumn (%d) out of bounds!\n", screenColumn);
        // return;
    }
	float projPlaneDist = (data->screenWidth / 2) / tan(data->FOV / 2);
    float projectedHeight = (cubeHeight * projPlaneDist) / distance;
	// printf(" Projectedplanedist %f\n", projPlaneDist);
    // Calculate start and end Y positions for the wall slice
    int wallStartY = (data->screenHeight / 2) - (projectedHeight / 2);
    int wallEndY = (data->screenHeight / 2) + (projectedHeight / 2);

	// printf("wallStartY: %d, wallEndY: %d\n", wallStartY, wallEndY);
    // Ensure wall slice is within screen bounds
    if (wallStartY < 0)
		wallStartY = 0;
    if (wallEndY > data->screenHeight)
		wallEndY = data->screenHeight - 1;
	// printf("test");
    // Draw the vertical slice
	if ((data->final_point[screenColumn].x % 50 == 49 || data->final_point[screenColumn].x % 50 == 0) && data->final_point[screenColumn].x > data->posX)	//east wall
		data->colours = 9000000;
	else if ((data->final_point[screenColumn].x % 50 == 49 || data->final_point[screenColumn].x % 50 == 0) && data->final_point[screenColumn].x < data->posX)	//west wall
		data->colours = 7000000;
	else if ((data->final_point[screenColumn].y % 50 == 49 || data->final_point[screenColumn].y % 50 == 0) && data->final_point[screenColumn].y > data->posY)	//north wall
		data->colours = 5000000;
	else if ((data->final_point[screenColumn].y % 50 == 49 || data->final_point[screenColumn].y % 50 == 0) && data->final_point[screenColumn].y < data->posY)	//south wall
		data->colours = 3000000;
	else
		data->colours = 6666666;
	// * distance* 0.0000001;
	for (int y = wallStartY; y <= wallEndY; y++)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		// printf("putting pixels");
	}
	data->colours = 2222222;
	for (int y = wallEndY; y < 1080; y++)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		// printf("putting pixels");
	}
	data->colours = 8888888;
	for (int y = wallStartY; y > 0; y--)
	{
		my_mlx_pixel_put(data, screenColumn, y, 1);
		// printf("putting pixels");
	}
	// printf("screenheight: %d\n", data->screenHeight);
	// 	printf("screenwidth: %d\n", data->screenWidth);
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
	int nr;
	nr = 0;
	// if (!data->img[1])
	// 	data->img[1] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &cube.height, &cube.height);
	// if (!data->img[2])
	// 	data->img[2] = mlx_xpm_file_to_image(data->mlx, TEXTURE_SNOW, &cube.height, &cube.height);
	// 	data->img[3] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &img_width, &img_height);
	if (target == '1')
	{
		draw_cube(data, x, y);
		// savecoords(x, y, nr++);
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