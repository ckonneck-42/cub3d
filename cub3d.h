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

# define TEXTURE_BRICK "./pic/NO.xpm"
# define TEXTURE_SNOW "./pic/Snow.xpm"
# define TEXTURE_METAL "./pic/Metal.xpm"
# define TEXTURE_LAVA "./pic/Lava.xpm"
# define TEXTURE_BLUE "./pic/Blue.xpm"


typedef struct t_Coordinate
{
	float			x;
	float			y;
	float			z;
}					t_Coordinate;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img[12];
	char			*addr;

	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	float			x;
	float			y;
	float			z;
	float			x1;
	float			x2;
	float			y1;
	float			y2;
	float			z1;
	float			z2;
	float			line_x;
	float			line_y;
	float			line_z;
	float			line_dx;
	float			line_dy;
	float			colours;
	float			zoom;
	float			angle;
	float			angle_x;
	float			angle_y;
	float			angle_z;
	int				offset_x;
	int				offset_y;
	float			step;
	int				rows;
	int				cols;
	const char		*filename;
	int				check;
	int				mode;
	t_Coordinate	**coordinates;
}					t_data;


void	base_init(t_data *data);
int	keypress(int keycode, t_data *data);
int	ft_close(int keycode, t_data *data);
int	close_window(t_data *data);