/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:40 by ckonneck          #+#    #+#             */
/*   Updated: 2025/01/02 11:23:14 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include "minilibx_linux/mlx.h"
#include <stdio.h>
#include <stdbool.h>

#define CENTER_X 960
#define CENTER_Y 540
#define PI 3.14159265
#define K_L 108
#define K_M 109
#define K_P 112
#define K_ALT 65513
#define K_ARRUP 65362
#define K_ARRDWN 65364
#define K_ARRLFT 65361
#define K_ARRRGT 65363
#define K_ESC 65307
#define K_W 119
#define K_A 97
#define K_S 115
#define K_D 100
#define GRID_SIZE 50
#define TEXTURE_BRICK "./pic/NO.xpm"
#define TEXTURE_SNOW "./pic/Snow.xpm"
#define TEXTURE_METAL "./pic/Metal.xpm"
#define TEXTURE_LAVA "./pic/Lava.xpm"
#define TEXTURE_BLUE "./pic/Blue.xpm"

typedef struct s_Coordinate
{
	float			x;
	float			y;
	char			map;
}					t_Coordinate;

typedef struct s_final_point
{
	int	x;
	int	y;
}	t_final_point;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_data
{
	char			*northtxt;
	char			*easttxt;
	char			*westtxt;
	char			*southtxt;
	void			*mlx;
	void			*win;
	void			*img[3];
	char			*addr;
	char			*addr1;
	int				line_length;
	int				bits_per_pixel;
	int				endian;
	int				fd;
	char			*map;
	char			raw_map[99999];
	char			*rawmaparray[1024];
	char			**squaremap;
	int				rows;
	int				coloumns;
	int				**walls;
	int				a;
	int				flag;
	int				playerflag;
	int				floorcolor;
	int				ceilingcolor;
	int				redc;
	int				greenc;
	int				bluec;
	int				northflag;
	int				southflag;
	int				eastflag;
	int				westflag;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	float			ray_angle;
	float			player_angle;
	double			movespeed;
	double			distanceahead[1920];
	t_final_point	final_point[1920];
	double			beamx;
	double			beamy;
	t_texture		wall_texture[4];
	t_texture		gun[2];
	double			distanceleft;
	double			distanceright;
	int				screen_height;
	int				screen_width;
	int				check_x;
	int				check_y;
	int				clear;
	float			fov;
	float			colours;
	float			pre_color;
	const char		*filename;
	char			**fd_parsearray;
	int				textureflag;
	bool			fire;
	double			wallstarty;
	double			wallendy;
	double			walltotal;
	double			wall_true_start_y;
	bool			move_w;
	bool			move_s;
	bool			move_a;
	bool			move_d;
	bool			clearadd;
	bool			clearmin;
	bool			look_right;
	bool			look_left;
	t_Coordinate	**coordinates;
}					t_data;

void			redraw_map(t_data *data);
t_data			*base_init(t_data *data, char **argv);
int				keypress(int keycode, t_data *data);
int				ft_close(int keycode, t_data *data);
int				close_window(t_data *data);
void			my_mlx_pixel_put(t_data *data, float x, float y, int size);
void			parse_map(t_data *data);
void			reinit_data(t_data *data);
int				get_pixel_color(int x, int y, t_data *data);
int				ft_detectpoint(t_data *data, double nextx, double nexty);
void			calculatesize(t_data *data);
void			castbeams(t_data *data);
void			render_textures(char target, t_data *data, int x, int y);
t_Coordinate	**alloco(int rows, int cols);
void			freecall(t_Coordinate **coordinates, int rows);
void			freedom(t_data *data, char *errormessage);
void			render3d(t_data *data, double distance,
					double cubeHeight, int screenColumn);
void			renderscene(t_data *data);
void			parse_everything_else(t_data *data);
void			copy_map_to_buffer(t_data *data, size_t buffer_size);
void			fd_parse(char *map, t_data *data);
int				find_the_map(int i, t_data *data);
void			parse_the_color(t_data *data, char *line, int k, char **temp);
int				ft_isalnumwhole(char *line);
int				assign_colors(char **temp, t_data *data);
void			clean_exit(t_data *data, char *errormessage);
int				is_surrounded(t_data *data);
int				is_valid_adjacent(t_data *data, int x, int y);
void			fill_from_zero(t_data *data);
void			complete_flood(t_data *data, int x, int y);
t_texture		ft_load_texture(void *mlx, char *path, t_data *data);
void			make_btwo(t_data *data);
void			make_a_square(t_data *data);
void			restore_map(t_data *data);
void			parse_the_texturepath(t_data *data,
					char *line, int k, char *ttf);
void			ft_wall_texture(t_data *data);
void			freetextures(t_data *data);
void			checkfilename(t_data *data, char *map);
void			checktheplayer(t_data *data);
void			smallmap(t_data *data);
int				ft_detectgrid(t_data *data, double x, double y);

int				mousemovement(int x, int y, t_data *data);

void			drawgun(t_data *data, int i);
void			draw_cross(t_data *data);
int				mouse_release(int button, t_data *data);
int				mouse_press(int button, t_data *data);
void			base_init2(t_data *data);
int				get_nr_of_lines(t_data *data);
void			set_char_at(t_data *data, int x, int y, char new);
char			get_char_at(t_data *data, int x, int y);
void			flood_fill(t_data *data, int x, int y);
void			pressw(t_data *data);
void			presss(t_data *data);
void			pressa(t_data *data);
void			pressd(t_data *data);
int				parse_map2(t_data *data, char *line, int x, int y);
void			parse_map3(t_data *data, int i, char *line);
void			parse_north(t_data *data, char *line, int k, int i);
void			parse_east(t_data *data, char *line, int k, int i);
void			parse_west(t_data *data, char *line, int k, int i);
void			parse_south(t_data *data, char *line, int k, int i);
void			seperate_clean_exit(t_data *data, char *errormessage);
char			*get_next_line_from_memory(const char *buffer, size_t *offset);
int				find_colors(char *ttf, t_data *data);
void			free_array(t_data *data, char **temp);
void			checkforduplicates(t_data *data);
void			draw_middle(t_data *data, int screenColumn);
void			ft_draw_wall_2(t_data *data,
					int screenColumn, int i);
void			ft_draw_wall(t_data *data,
					int screenColumn, int i);
int				ft_detectgrid_2(t_data *data, double x, double y);
void			xpm_clean_exit(t_data *data, char *errormessage);
void			tex_clean_exit(t_data *data, char *errormessage);
void			checkiftheresanother(t_data *data, int i, char *ttf);
void			checkiftheresanothercolor(t_data *data, int i, char *ttf);
void			parse_calc_dupes(t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				move(t_data *data);
void			base_init3(t_data *data);
void			main_exit(t_data *data, char *errormessage);