/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:48:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/20 16:19:49 by ckonneck         ###   ########.fr       */
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

//The essence is to place the pixels on the .xpm in proportion on the wall.
t_texture	ft_load_texture(void *mlx, char *path, t_data *data)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	if (!texture.img)
		clean_exit(data, "Load .xpm img wrong!");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_length, &texture.endian);
	return (texture);
}

void	ft_wall_texture(t_data *data)
{
	data->wall_texture[0] = ft_load_texture(data->mlx, data->easttxt, data);//east
	data->wall_texture[1] = ft_load_texture(data->mlx, data->westtxt, data);//west
	data->wall_texture[2] = ft_load_texture(data->mlx, data->southtxt, data);//south
	data->wall_texture[3] = ft_load_texture(data->mlx, data->northtxt, data);//north
}

void renderScene(t_data *data)
{
    // Loop through each column on the screen
    for (int screenColumn = 0; screenColumn < data->screenWidth; screenColumn++)
    {
        render3D(data, data->distanceahead[screenColumn], GRID_SIZE * 4 / 5, screenColumn); // 50 is the cube height, change as needed
    }
    // parse_map(data->map, data);
    smallmap(data);
}

void    ft_draw_wall(t_data *data, float wallStartY, float wallEndY, double wall_true_start_y, int screenColumn, double distance, float walltotal, int i)
{
    double  tex_x = fmod(data->final_point[screenColumn].y, GRID_SIZE);
        double  tex_y;
        // printf("this is x: %f\n", tex_x);
        data->colours = 9000000;
        if (distance == 999999)
        {
            data->colours = 0;
            for (float y = 0; y < data->screenHeight; y++)
                my_mlx_pixel_put(data, screenColumn, y, 1);
        }
        else
        {
            for (float y = wallStartY; y <= wallEndY; y++)
            {
                int tex_y = (y - wall_true_start_y) * data->wall_texture[i].height / walltotal;
        // printf("tex_y is: %d, tex_x is: %d, y is: %d\n", tex_y, tex_x, data->final_point[screenColumn].y);
                data->colours = *(int *)(data->wall_texture[i].addr + ((int)tex_y * data->wall_texture[i].line_length + (int)tex_x * (data->wall_texture[i].bpp / 8)));
                my_mlx_pixel_put(data, screenColumn, y, 1);
            }
            data->colours = 2222222;
            for (float y = wallEndY; y < 1080; y++)
                my_mlx_pixel_put(data, screenColumn, y, 1);
            data->colours = 8888888;
            for (float y = wallStartY; y > 0; y--)
            {
                if (screenColumn < 500 && y < 300)
                    data->colours = 0000000;
                my_mlx_pixel_put(data, screenColumn, y, 1);
            }
            data->colours = 0;
        }
        data->pre_color = *(int *)(data->wall_texture[i].addr + ((int)tex_y * data->wall_texture[i].line_length + (int)tex_x * (data->wall_texture[i].bpp / 8)));
}
//this function is for the north and south wall
void    ft_draw_wall_2(t_data *data, float wallStartY, float wallEndY, double wall_true_start_y, int screenColumn, double distance, float walltotal, int i)
{
    double  tex_x = fmod(data->final_point[screenColumn].x, GRID_SIZE);
    double  tex_y;
    // printf("this is x: %f\n", tex_x);
    data->colours = 9000000;
    if (distance == 999999)
    {
        data->colours = 0;
        for (float y = 0; y < data->screenHeight; y++)
            my_mlx_pixel_put(data, screenColumn, y, 1);
    }
    else
    {
        for (float y = wallStartY; y <= wallEndY; y++)
        {
            int tex_y = (y - wall_true_start_y) * data->wall_texture[i].height / walltotal;
    // printf("tex_y is: %d, tex_x is: %d, y is: %d\n", tex_y, tex_x, data->final_point[screenColumn].y);
            data->colours = *(int *)(data->wall_texture[i].addr + ((int)tex_y * data->wall_texture[i].line_length + (int)tex_x * (data->wall_texture[i].bpp / 8)));
            my_mlx_pixel_put(data, screenColumn, y, 1);
        }
        data->colours = 2222222;
        for (float y = wallEndY; y < 1080; y++)
            my_mlx_pixel_put(data, screenColumn, y, 1);
        data->colours = 8888888;
        for (float y = wallStartY; y > 0; y--)
        {
            if (screenColumn < 500 && y < 300)
                data->colours = 0000000;
            my_mlx_pixel_put(data, screenColumn, y, 1);
        }
        data->colours = 0;
    }
    data->pre_color = *(int *)(data->wall_texture[i].addr + ((int)tex_y * data->wall_texture[i].line_length + (int)tex_x * (data->wall_texture[i].bpp / 8)));
}
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
    float walltotal = wallEndY - wallStartY;
    float wall_true_start_y = wallStartY;
    if (screenColumn < 500)
        if (wallStartY < 300)
            wallStartY = 300;
    // printf("wallStartY: %d, wallEndY: %d\n", wallStartY, wallEndY);
    // Ensure wall slice is within screen bounds
    if (wallStartY < 0)
        wallStartY = 0;
    if (wallEndY > data->screenHeight)
        wallEndY = data->screenHeight - 1;
    // printf("this is the start y: %f, this is the end y: %f,  this is the distance: %f\n", wallStartY, wallEndY, distance);
    // printf("this is x: %d,   this is y: %d\n", data->final_point[screenColumn].x, data->final_point[screenColumn].y);
    if ((int)data->final_point[screenColumn].x % GRID_SIZE == 0 && (int)data->final_point[screenColumn].y % GRID_SIZE == 0)
    {
        data->colours = data->pre_color;
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
            {
                if (screenColumn < 500 && y < 300)
                    data->colours = 0000000;
                my_mlx_pixel_put(data, screenColumn, y, 1);
            }
            data->colours = 0;
        }
    }
    else if (((int)data->final_point[screenColumn].x % GRID_SIZE == 0) && data->final_point[screenColumn].x > data->posX)   //east wall
    {
        ft_draw_wall(data, wallStartY, wallEndY, wall_true_start_y, screenColumn, distance, walltotal, 0);
    }
    else if (((int)data->final_point[screenColumn].x % GRID_SIZE == 0) && data->final_point[screenColumn].x < data->posX)   //west wall
    {
        ft_draw_wall(data, wallStartY, wallEndY, wall_true_start_y, screenColumn, distance, walltotal, 1);
    }
    else if (((int)data->final_point[screenColumn].y % GRID_SIZE == 0) && data->final_point[screenColumn].y > data->posY)   //south wall
    {
        ft_draw_wall_2(data, wallStartY, wallEndY, wall_true_start_y, screenColumn, distance, walltotal, 2);
    }
    else if (((int)data->final_point[screenColumn].y % GRID_SIZE == 0) && data->final_point[screenColumn].y < data->posY)   //north wall
    {
        ft_draw_wall_2(data, wallStartY, wallEndY, wall_true_start_y, screenColumn, distance, walltotal, 3);
    }
    else
    {
        data->colours = 6666666;
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
            {
                if (screenColumn < 500 && y < 300)
                    data->colours = 0000000;
                my_mlx_pixel_put(data, screenColumn, y, 1);
            }
            data->colours = 0;
        }
    }
}

int ft_detectgrid(t_data *data, double x, double y)
{
    if (data->check_x && data->check_y && (int)x == data->check_x && (int)y == data->check_y)
        return (0);
    int gridX = (int)((x) / GRID_SIZE);
    int gridY = (int)((y) / GRID_SIZE);
    // printf("this is x: %f, this is y: %f, this is gridX: %d, this is gridY: %d, this is the number: %c\n", x, y, gridX, gridY, data->coordinates[gridX][gridY].map);
    if (gridX < 0 || gridY < 0)
        return 0;
    if (gridX >= data->rows || gridY >= data->coloumns || !data->coordinates[gridX])
        return (1);
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;
    gridX = (int)((x + 1) / GRID_SIZE);
    gridY = (int)(y / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;
    gridX = (int)((x) / GRID_SIZE);
    gridY = (int)((y + 1) / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;
    gridX = (int)((x - 1) / GRID_SIZE);
    gridY = (int)((y) / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;
    gridX = (int)((x) / GRID_SIZE);
    gridY = (int)((y - 1) / GRID_SIZE);
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;
    data->check_x = (int)x;
    data->check_y = (int)y;
    return 0;
}
void    smallmap(t_data *data)
{
    double  start_x = data->posX - 250;
    double  end_x = data->posX + 250;
    double  start_y = data->posY - 150;
    double  end_y = data->posY + 150;
    double  x = start_x;
    double  a = 0;
    double  y = start_y;
    double  b = 0;
    data->colours = 6666666;
    while (x <= end_x)
    {
        y = start_y;
        b = 0;
        while (y <= end_y)
        {
            if (ft_detectgrid(data, x, y))
                my_mlx_pixel_put(data, a, b, 1);
            y += 1;
            b += 1;
        }
        x += 1;
        a += 1;
    }
    data->colours = 9999999;
    my_mlx_pixel_put(data, 250, 150, 10);
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

	if (target == '1' || target == '\n' || target == '\0')
	{
		// printf("drawing cube for x: %d, and y: %d\n", x/50, y/50);
		draw_cube(data, x, y);
	}
	else if (target == 'N' && data->playerflag == 0)
	{
		data->posX = x+25;
		data->posY = y+25;
		data->playerflag = 1;
		data->a = 230;
		checktheplayer(data);
	}
	else if (target == 'W' && data->playerflag == 0)
	{
		data->posX = x+25;
		data->posY = y+25;
		data->playerflag = 1;
		data->a = 140;
		checktheplayer(data);
	}
	else if (target == 'S' && data->playerflag == 0)
	{
		data->posX = x+25;
		data->posY = y+25;
		data->playerflag = 1;
		data->a = 50;
		checktheplayer(data);
	}
	else if (target == 'E' && data->playerflag == 0)
	{
		data->posX = x+25;
		data->posY = y+25;
		data->playerflag = 1;
		data->a = 320;
		checktheplayer(data);
	}
	else if ((target == 'E' || target == 'W' || target == 'N' || target == 'S') && data->playerflag == 1)
		clean_exit(data, "duplicate found");
}
