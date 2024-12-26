/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:48:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 15:13:12 by ckonneck         ###   ########.fr       */
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

t_texture	ft_load_texture(void *mlx, char *path, t_data *data)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path,
			&texture.width, &texture.height);
	if (!texture.img)
		xpm_clean_exit(data, "Load .xpm img wrong!");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp,
			&texture.line_length, &texture.endian);
	return (texture);
}

int	ft_detectgrid_2(t_data *data, double x, double y)
{
	int	gridx;
	int	gridy;

	gridx = (int)((x + 1) / GRID_SIZE);
	gridy = (int)(y / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	gridx = (int)((x) / GRID_SIZE);
	gridy = (int)((y + 1) / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	gridx = (int)((x - 1) / GRID_SIZE);
	gridy = (int)((y) / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	gridx = (int)((x) / GRID_SIZE);
	gridy = (int)((y - 1) / GRID_SIZE);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	return (0);
}

void	render_textures(char target, t_data *data, int x, int y)
{
	if ((target == 'N' || target == 'W' || target == 'S'
			|| target == 'E') && data->playerflag == 1)
	{
		data->pos_x = x + 25;
		data->pos_y = y + 25;
		if (target == 'N')
			data->a = 230;
		if (target == 'W')
			data->a = 140;
		if (target == 'E')
			data->a = 320;
		if (target == 'S')
			data->a = 50;
		data->playerflag = 9;
	}
}

void	ft_wall_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->wall_texture[i].img = NULL;
		i++;
	}
	data->textureflag = 1;
	data->wall_texture[0] = ft_load_texture(data->mlx, data->easttxt, data);
	data->wall_texture[1] = ft_load_texture(data->mlx, data->westtxt, data);
	data->wall_texture[2] = ft_load_texture(data->mlx, data->southtxt, data);
	data->wall_texture[3] = ft_load_texture(data->mlx, data->northtxt, data);
}

// data->gun[0] = ft_load_texture(data->mlx, "pic/gun/smallgun.xpm", data);
// data->gun[1] = ft_load_texture(data->mlx, 
//"pic/gun/smallgun_shoot.xpm", data);
