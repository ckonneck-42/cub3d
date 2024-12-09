/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/09 12:49:36 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img[0]);
	// mlx_destroy_image(data->mlx, data->img[1]);
	// mlx_destroy_image(data->mlx, data->img[2]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_destroy_display(data->mlx);
	freecall(data->coordinates, data->rows);
	free(data->mlx);
	free(data);
	unlink("tempfilemap");
	exit(0);
}


int	ft_close(int keycode, t_data *data)
{
	int	i;

	if (keycode == K_ALT)
	{
		i = 0;
		while (i < 10)
		{
			ft_printf("i love tudor\n");
			i++;
		}
	}
	if (keycode == K_ESC)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img[0]);
		// mlx_destroy_image(data->mlx, data->img[1]);
		// mlx_destroy_image(data->mlx, data->img[2]);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		freecall(data->coordinates, data->rows);
		free(data->mlx);
		free(data);
		unlink("tempfilemap");
		exit(0);
	}
	else
		return (0);
}

int ft_detectpoint(t_data *data, double nextX, double nextY)
{
    int gridX = (int)(nextX / GRID_SIZE); // Map grid X
    int gridY = (int)(nextY / GRID_SIZE); // Map grid Y

    // Check if the grid position is a wall ('1')
    if (data->coordinates[gridX][gridY].map == '1')
        return 1;

    return 0; // No wall
}
void pressW(t_data *data)  // Move Forward
{
	double	ang = data->a + 1920 * 0.02;
    double nextX = data->posX + cos(ang * (PI / 180.0)) * data->movespeed;
    double nextY = data->posY + sin(ang * (PI / 180.0)) * data->movespeed;

    if (ft_detectpoint(data, nextX, nextY) != 1 )  // Check if there's no wall ahead
    {
        data->posX = nextX;  // Update position
        data->posY = nextY;  // Update position
    }
    else
        printf("You hit a wall\n");  // Handle wall collision
}

void pressS(t_data *data)  // Move Backward
{
	double	ang = data->a + 1920 * 0.02;
    double nextX = data->posX - cos(ang * (PI / 180.0)) * data->movespeed;
    double nextY = data->posY - sin(ang * (PI / 180.0)) * data->movespeed;

    if (ft_detectpoint(data, nextX, nextY) != 1)
    {
        data->posX = nextX;
        data->posY = nextY;
    }
    else
        printf("You hit a wall\n");
}

void pressA(t_data *data)  // Move Left
{
	double	ang = data->a + 1920 * 0.02;
 	double nextX = data->posX + sin(ang * (PI / 180.0)) * data->movespeed;  // Use sin for X (opposite direction)
    double nextY = data->posY - cos(ang * (PI / 180.0)) * data->movespeed;  // Use cos for Y (normal direction)
    if (ft_detectpoint(data, nextX, nextY) != 1)
    {
        data->posX = nextX;
        data->posY = nextY;
    }
    else
        printf("You hit a wall\n");
}

void pressD(t_data *data)  // Move Right
{
	double	ang = data->a + 1920 * 0.02;
     double nextX = data->posX - sin(ang * (PI / 180.0)) * data->movespeed;  // Use sin for X (normal direction)
    double nextY = data->posY + cos(ang * (PI / 180.0)) * data->movespeed;  // Use cos for Y (opposite direction)
    if (ft_detectpoint(data, nextX, nextY) != 1)
    {
        data->posX = nextX;
        data->posY = nextY;
    }
    else
        printf("You hit a wall\n");
}

int	keypress(int keycode, t_data *data)//facing north set
{
	if (keycode == K_W)
		pressW(data);
	else if (keycode == K_A)
		pressA(data);
	else if (keycode == K_S)
		pressS(data);
	else if (keycode == K_D)
		pressD(data);
	else if(keycode == K_ARRRGT)
	{
		data->a = fmod(data->a + 5.0, 360.0); 
	}
	else if(keycode == K_ARRLFT)
	{
		data->a = fmod(data->a - 5.0 + 360.0, 360.0);
	}
	redraw_map(data);
	return (0);
}

void	redraw_map(t_data *data)
{
	reinit_data(data);
	data->colours = 16711680;//deep red (player)
	my_mlx_pixel_put(data, data->posX, data->posY, 5);
	renderScene(data);
	castbeams(data);
	parse_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	data->colours = 45000;//normalize for walls
}

void reinit_data(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img[0]);
	data->img[0] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img[0], &data->bits_per_pixel,
			&data->line_length, &data->endian);
	// parse_map(data->map, data);
	// free(data);
	// data = base_init(data);
	// parse_map(data->map, data);
}
