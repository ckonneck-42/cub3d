#include "cub3d.h"


void	render_textures(char target, t_data *data, int x, int y)
{
	int img_width, img_height;

	if (!data->img[1])
		data->img[1] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &img_width, &img_height);
	if (!data->img[2])
		data->img[2] = mlx_xpm_file_to_image(data->mlx, TEXTURE_SNOW, &img_width, &img_height);
	// if (!data->img[3])
	// 	data->img[3] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &img_width, &img_height);
	if (target == '1')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img[1],
			x, y);
		printf("put 1\n");
	}
	else if (target == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->img[2],
			x, y);
	// else if (target == 'N')
	// 	mlx_put_image_to_window(data->mlx, data->win, data->img[3],
	// 		x, y);
	// else if (target == 'N')
	// 	render_player(data, x, y);
	// else if (target == 'Z')
	// 	render_enemy(game, x, y);
	// else if (target == 'C')
	// 	render_collectible(game, x, y);
	// else if (target == 'E')
	// 	render_exit(game, x, y);
}



void parse_map(char **argv, t_data *data)
{
	int fd;
	fd = open(argv[1], O_RDONLY);
	char *line;
	int i;
	line = get_next_line(fd);
	int x;
	int y = 0;
	while (line != NULL)
	{
		x = 0;
		while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == ' ')
		{
			render_textures(line[i], data, x, y);
			i++;
			x += 50;
		}
		if(line[i+1] == '\0')
		{
			printf("reached end of line\n");
		}
		else
		{
			printf("found irregularity: %c\n", line[i]);
			exit(1);
		}
		i = 0;
		free(line);
		printf("getting next line\n");
		line = get_next_line(fd);
		y += 50;
	}
	printf("finished parsing\n");
}


int main(int argc, char **argv)
{
	t_data data;
	base_init(&data);
	if (argc != 2)
	{
		printf("give map plx\n");
		exit(1);
	}
	else
		parse_map(argv, &data);
		
	// mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, ft_close, &data);
	mlx_key_hook(data.win, keypress, &data);
	mlx_loop(data.mlx);

}



void	base_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
	data->img[0] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);

}


