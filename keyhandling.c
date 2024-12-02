/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/29 15:58:05 by ckonneck         ###   ########.fr       */
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
		exit(0);
	}
	else
		return (0);
}

int	ft_detectpoint(t_data *data, int flag)
{
	int gridX; 
	int gridY;
	if (flag == 4)
	{
		gridX = (int)((data->posX - data->planeX * data->movespeed)/ GRID_SIZE);
		gridY = (int)((data->posY - data->planeY * data->movespeed) / GRID_SIZE);
	}
	if (flag == 3)
	{
		gridX = (int)((data->posX - data->dirX * data->movespeed)/ GRID_SIZE);
		gridY = (int)((data->posY - data->dirY * data->movespeed) / GRID_SIZE);
	}
	if (flag == 2)
	{
		gridX = (int)((data->posX + data->planeX * data->movespeed)/ GRID_SIZE);
		gridY = (int)((data->posY + data->planeY * data->movespeed) / GRID_SIZE);
	}
	if (flag == 1)
	{
		gridX = (int)((data->posX + data->dirX * data->movespeed)/ GRID_SIZE);
		gridY = (int)((data->posY + data->dirY * data->movespeed) / GRID_SIZE);
	}
	if (data->coordinates[gridX][gridY].map == '1')
   		return(1);
	return(0);
}

void pressW(t_data *data)
{
	if (ft_detectpoint(data, 4) != 1)
	{
		data->posX -= data->planeX * data->movespeed;
		data->posY -= data->planeY * data->movespeed;
		printf("X: %f\n", data->posX);
		printf("Y: %f\n", data->posY);
	}
	else
		printf("you hit a wall\n");
}

void pressA(t_data *data)
{
	if (ft_detectpoint(data, 3) != 1)
	{
		data->posX -= data->dirX * data->movespeed;
		data->posY -= data->dirY * data->movespeed;
		printf("X: %f\n", data->posX);
		printf("Y: %f\n", data->posY);
	}
	else
		printf("you hit a wall\n");
}

void pressS(t_data *data)
{
	if (ft_detectpoint(data, 2) != 1)
	{
		data->posX += data->planeX * data->movespeed;
		data->posY += data->planeY * data->movespeed;
		printf("X: %f\n", data->posX);
		printf("Y: %f\n", data->posY);
	}
	else
		printf("you hit a wall\n");
}
void pressD(t_data *data)
{
	if (ft_detectpoint(data, 1) != 1)
	{
		data->posX += data->dirX * data->movespeed;
		data->posY += data->dirY * data->movespeed;
		printf("X: %f\n", data->posX);
		printf("Y: %f\n", data->posY);
	}
	else
		printf("you hit a wall\n");
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
		data->a = (data->a + 1) % 360;
	else if(keycode == K_ARRLFT)
		data->a = (data->a - 1 + 360) % 360;
	redraw_map(data);
	return (0);
}

void	redraw_map(t_data *data)
{
	reinit_data(data);
	data->colours = 16711680;//deep red (player)
	my_mlx_pixel_put(data, data->posX, data->posY, 5);
	castbeams(data);
	
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	data->colours = 45000;//normalize for walls
}

void reinit_data(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img[0]);
	data->img[0] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img[0], &data->bits_per_pixel,
			&data->line_length, &data->endian);
	parse_map(data->map, data);
	// free(data);
	// data = base_init(data);
	// parse_map(data->map, data);
}
