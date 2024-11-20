#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
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
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	else
		return (0);
}


int	keypress(int keycode, t_data *data)
{
	if (keycode == K_ARRLFT)
		data->angle_y -= 0.1;
	else if (keycode == K_ARRRGT)
		data->angle_y += 0.1;
	else if (keycode == K_ARRUP)
		data->angle_x -= 0.1;
	else if (keycode == K_ARRDWN)
		data->angle_x += 0.1;
	else if (keycode == K_P)
		data->zoom += 0.1;
	else if (keycode == K_M && data->zoom > 0.2)
		data->zoom -= 0.1;
	else if (keycode == K_M && data->zoom <= 0.2)
		data->zoom -= 0.01;
	else if (keycode == K_W)
		data->offset_y -= 20;
	else if (keycode == K_A)
		data->offset_x -= 20;
	else if (keycode == K_S)
		data->offset_y += 20;
	else if (keycode == K_D)
		data->offset_x += 20;
	// draw_map(data, data->filename);
	return (0);
}
