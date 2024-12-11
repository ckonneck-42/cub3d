/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:40 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/11 17:52:32 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>

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
# define TEXTURE_BRICK "./pic/NO.xpm"
# define TEXTURE_SNOW "./pic/Snow.xpm"
# define TEXTURE_METAL "./pic/Metal.xpm"
# define TEXTURE_LAVA "./pic/Lava.xpm"
# define TEXTURE_BLUE "./pic/Blue.xpm"


typedef struct s_Coordinate
{
	float			x;
	float			y;
	float			z;
    char            map;
}					t_Coordinate;


typedef struct 
{
	char *imgpath;
	int mapX;
	int mapY;
	int height;	
} t_Cube;

typedef struct {
    // Screen dimensions
    int screenWidth; 
    int screenHeight;

    // Player position and direction
    double posX, posY;    // Player's position
    double dirX, dirY;    // Direction vector
    double planeX, planeY; // Camera plane

    // Ray properties
    double cameraX;       // X-coordinate in camera space
    double rayDirX, rayDirY; // Ray direction

    // Map grid position
    int mapX, mapY;       // Current map cell

    // DDA step and distance
    double sideDistX, sideDistY; // Distances to next x or y side
    double deltaDistX, deltaDistY; // Distance increments
    double perpWallDist;  // Perpendicular wall distance
    int stepX, stepY;     // DDA step direction
    int hit;              // Did the ray hit a wall?
    int side;             // Was a NS or EW wall hit?

    // Drawing parameters
    int lineHeight;       // Height of the line to draw
    int drawStart, drawEnd; // Drawing limits for the stripe

    // Texture properties
    int texNum;           // Texture number of the hit wall
    double wallX;         // Exact hit position on the wall
    int texX;             // X-coordinate on the texture
	int texY;  
	int **textures;
    // Texture dimensions (assumed globally consistent)
    int texWidth;         // Width of a texture
    int texHeight;        // Height of a texture
} t_RaycastVars;

typedef struct s_final_point
{
    int x;
    int y;
}   t_final_point;


typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img[3];
	char			*addr;
    char			*addr1;
	int			    line_length;
	int				bits_per_pixel;
	int				endian;
    int             fd;
    char            *map;
    char            raw_map[1024];
    char            **rawmaparray;
    
    int             rows;
    int             coloumns;
    int             **walls;
    int             a;
    int             flag;
    int             playerflag;
    int             floorcolor;
    int             ceilingcolor;
    int             redc;
    int             greenc;
    int             bluec;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
    float           rayAngle;
    float           playerAngle;
	double 			movespeed;
    double          distanceahead[1920];
    t_final_point   final_point[1920];
    double          distanceleft;
    double          distanceright;
    int             screenHeight;
    int             screenWidth;
    float             FOV;
	float			colours;
    float           pre_color;
	const char		*filename;
    char            **fd_parsearray;
	t_Coordinate	**coordinates;
    	// t_RaycastVars	ray;
	t_Cube			cube;
}					t_data;

typedef struct s_walls
{
    int num;
    int **walls;
}               t_walls;

void	redraw_map(t_data *data);
t_data	*base_init(t_data *data, char **argv);
int	keypress(int keycode, t_data *data);
int	ft_close(int keycode, t_data *data);
int	close_window(t_data *data);
void	raycasting(t_data *data);
void	my_mlx_pixel_put(t_data *data, float x, float y, int size);
void parse_map(t_data *data);
void reinit_data(t_data *data);
int get_pixel_color(int x, int y, t_data *data);
int ft_detectpoint(t_data *data, double nextX, double nextY);
void calculatesize(char *map, t_data *data);
void castbeams(t_data *data);
void	render_textures(char target, t_data *data, int x, int y);
t_Coordinate	**allocatecoordinates(int rows, int cols);
void	freecall(t_Coordinate **coordinates, int rows);
void	freedom(t_data *data, char *line);
void render3D(t_data *data, double distance, float cubeHeight, int screenColumn);
void renderScene(t_data *data);
void	parse_everything_else(char *map, t_data *data);
void	copy_map_to_buffer(t_data *data, size_t buffer_size);
void	fd_parse(char *map, t_data *data);
int find_the_map(int i, t_data *data);
void	parse_the_color(t_data *data, char *line, int k);
int ft_isalnumwhole(char *line);
void assign_colors(char **temp, t_data *data);
void	clean_exit(t_data *data, char *errormessage);
int is_surrounded(t_data *data);
int is_valid_adjacent(t_data *data, int x, int y);
void fill_from_zero(t_data *data);
void complete_flood(t_data *data, int x, int y);