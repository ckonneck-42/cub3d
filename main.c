/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:37 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 17:07:03 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_functions(t_data *data)
{
	data->colours = 45000;
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, ft_close, data);
	mlx_key_hook(data->win, keypress, data);
	mlx_loop(data->mlx);
}
	// mlx_hook(data->win, 4, 0, mouse_press, data);
	// mlx_hook(data->win, 5, 0, mouse_release, data);
	// mlx_hook(data->win, 6, 0, mousemovement, data);
	// mlx_mouse_hook(data->win, mousemovement, data);

int	main(int argc, char **argv)
{
	t_data	*data;

	data = 0;
	data = base_init(data, argv);
	base_init2(data);
	if (argc != 2)
	{
		printf("give map plx\n");
		exit(1);
	}
	else
	{
		parse_calc_dupes(data);
		if (is_surrounded(data) == 1)
			clean_exit(data, "invalid map");
		restore_map(data);
		castbeams(data);
		renderscene(data);
	}
	mlx_functions(data);
}

void	parse_calc_dupes(t_data *data)
{
	fd_parse(data->map, data);
	parse_everything_else(data);
	calculatesize(data);
	make_a_square(data);
	checkforduplicates(data);
	data->coordinates = alloco(data->rows + 3, data->coloumns + 1);
	parse_map(data);
}

t_data	*base_init(t_data *data, char **argv)
{
	data = malloc(sizeof(t_data));
	data->map = argv[1];
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
	data->img[0] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img[0], &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (data);
}

void	base_init2(t_data *data)
{
	data->colours = 45000;
	data->pos_x = 960;
	data->pos_y = 540;
	data->dir_x = 1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 1.0;
	data->movespeed = 10.0;
	data->playerflag = 0;
	data->a = 0;
	data->player_angle = 0;
	data->flag = 0;
	data->coloumns = 0;
	data->check_x = 0;
	data->check_y = 0;
	data->rows = 0;
	data->fov = 60 * PI / 180;
	data->screen_height = 1080;
	data->screen_width = 1920;
	data->clear = 2;
	data->textureflag = 0;
	data->westflag = 0;
	data->eastflag = 0;
	data->southflag = 0;
	data->northflag = 0;
}
