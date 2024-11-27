/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/27 16:14:53 by ckonneck         ###   ########.fr       */
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
	free(data->mlx);
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
		free(data->mlx);
		exit(0);
	}
	else
		return (0);
}

int	ft_detectpoint(t_data *data)
{
	int	a;

	a = 19;
	while (a)
	{
		if (get_pixel_color(data->posX + a, data->posY, data) == 45000)
			return(1);
		a--;
	}
	a = 19;
	while (a)
	{
		if (get_pixel_color(data->posX - a, data->posY, data) == 45000)
			return(2);
		a--;
	}
	a = 19;
	while (a)
	{
		if (get_pixel_color(data->posX, data->posY + a, data) == 45000)
			return(3);
		a--;
	}
	a = 19;
	while (a)
	{
		if (get_pixel_color(data->posX, data->posY - a, data) == 45000)
			return(4);
		a--;
	}
	return(0);
}

int	keypress(int keycode, t_data *data)//facing north set
{
	
	// int color = get_pixel_color(data->posX, data->posY, data);
	int detectpoint = ft_detectpoint(data);
	if (keycode == K_W)
	{
		if (detectpoint != 4)
		{
			data->posX -= data->planeX * data->movespeed;
			data->posY -= data->planeY * data->movespeed;
			printf("X: %f\n", data->posX);
			printf("Y: %f\n", data->posY);
			printf("color: %d\n", get_pixel_color(data->posX, data->posY, data));
		}
		else
			printf("you hit a wall\n");
	}
	else if (keycode == K_A)
	{
		if (detectpoint != 2)
		{
			data->posX -= data->dirX * data->movespeed;
			data->posY -= data->dirY * data->movespeed;
			printf("X: %f\n", data->posX);
			printf("Y: %f\n", data->posY);
			printf("color: %d\n", get_pixel_color(data->posX, data->posY, data));
		}
		else
			printf("you hit a wall\n");
	}
	else if (keycode == K_S)
	{
		if (detectpoint != 3)
		{
			printf("color: %d\n", get_pixel_color(data->posX, data->posY, data));
			data->posX += data->planeX * data->movespeed;
			data->posY += data->planeY * data->movespeed;
			printf("X: %f\n", data->posX);
			printf("Y: %f\n", data->posY);
		}
		else
			printf("you hit a wall\n");
	}
	else if (keycode == K_D)
	{
		if (detectpoint != 1)
		{
			data->posX += data->dirX * data->movespeed;
			data->posY += data->dirY * data->movespeed;
			printf("X: %f\n", data->posX);
			printf("Y: %f\n", data->posY);
			printf("color: %d\n", get_pixel_color(data->posX, data->posY, data));
		}
		else
			printf("you hit a wall\n");
	}
	else if(keycode == K_ARRRGT)
	{
		data->a = (data->a + 1) % 360;
	}
	else if(keycode == K_ARRLFT)
	{
		data->a = (data->a - 1 + 360) % 360;
	}
	redraw_map(data);
	return (0);
}

int get_pixel_color(int x, int y, t_data *data)
{
    char *pixel;

    // Calculate the pixel's memory address
    pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

    // Convert the pixel data to an integer (color)
    return *(int *)pixel;
}

void	redraw_map(t_data *data)
{
	double rad_angle_1 = data->a * (PI / 180.0);
	double rad_angle_2 = (data->a + 45) * (PI / 180.0);
	double rad_angle_3 = (data->a - 45) * (PI / 180.0);
	reinit_data(data);
	data->colours = 16711680;//deep red (player)
	my_mlx_pixel_put(data, data->posX, data->posY, 3);
	// pull the lever kronk
	//*shooting a beam*
	float targetbeam;
	float beamX;
	float beamY;
	float beamX_2;
	float beamY_2;
	float beamX_3;
	float beamY_3;
	beamX = data->posX;
	beamY = data->posY;
	beamX_2 = data->posX;
	beamY_2 = data->posY;
	beamX_3 = data->posX;
	beamY_3 = data->posY;
	// printf("beamX = %f\n", beamX);
	// printf("beamY = %f\n", beamY);
	while ((beamX >= 0 && beamX <= 1920 && beamY >= 0 && beamY <= 1080 && get_pixel_color(beamX, beamY, data) != 45000))// beamX != wallline
	{
		data->colours = 8388736;// purple for beam
		// printf("ima shooting my lazor\n");
		// if (get_pixel_color(beamX, beamY, data) == 45000)//&& get_pixel_color(beamX, beamY, data) == 16711680)
		// 	break;
		my_mlx_pixel_put(data, beamX, beamY, 1);
		beamX += cos(rad_angle_1);
		beamY += sin(rad_angle_1);
	}
	while ((beamX_2 >= 0 && beamX_2 <= 1920 && beamY_2 >= 0 && beamY_2 <= 1080 && get_pixel_color(beamX_2, beamY_2, data) != 45000))// beamX_2 != wallline
	{
		data->colours = 8388736;// purple for beam
		// printf("ima shooting my lazor\n");
		// if (get_pixel_color(beamX_2, beamY_2, data) == 45000)//&& get_pixel_color(beamX_2, beamY_2, data) == 16711680)
		// 	break;
		my_mlx_pixel_put(data, beamX_2, beamY_2, 1);
		beamX_2 += cos(rad_angle_2);
		beamY_2 += sin(rad_angle_2);
	}
	while ((beamX_3 >= 0 && beamX_3 <= 1920 && beamY_3 >= 0 && beamY_3 <= 1080 && get_pixel_color(beamX_3, beamY_3, data) != 45000))// beamX_3 != wallline
	{
		data->colours = 8388736;// purple for beam
		// printf("ima shooting my lazor\n");
		// if (get_pixel_color(beamX_3, beamY_3, data) == 45000)//&& get_pixel_color(beamX_3, beamY_3, data) == 16711680)
		// 	break;
		my_mlx_pixel_put(data, beamX_3, beamY_3, 1);
		beamX_3 += cos(rad_angle_3);
		beamY_3 += sin(rad_angle_3);
	}
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