
// 	int texWidth = 64;  // Texture dimensions
// int texHeight = 64;

// // For each face, calculate texX and texY
// double wallX; // Where the ray hits the wall (0.0 to 1.0)
// if (ray.side == 0) wallX = ray.posY + ray.perpWallDist * ray.rayDirY; // NS wall
// else           wallX = ray.posX + ray.perpWallDist * ray.rayDirX; // EW wall

// wallX -= floor(wallX);
// int texX = (int)(wallX * (double)texWidth);
// if (ray.side == 0 && ray.rayDirX > 0) ray.texX = ray.texWidth - ray.texX - 1;
// if (ray.side == 1 && ray.rayDirY < 0) ray.texX = ray.texWidth - ray.texX - 1;

// // Loop through vertical pixels to sample texY
// for (int y = ray.drawStart; y < ray.drawEnd; y++) {
//     int d = y * 256 - ray.screenHeight * 128 + ray.lineHeight * 128; // 256 and 128 are scaling constants
//     int texY = ((d * ray.texHeight) / ray.lineHeight) / 256;
//     int color = ray.textures[ray.texNum][ray.texY * ray.texWidth + ray.texX]; // Sample color
//     my_mlx_pixel_put(data, texX, texY, 1); // Render pixel
//}



//yao version

// void draw_cube(t_data *data, float x, float y)
// {
// 	float targetx;
// 	float targety;
// 	float targetz;
// 	float tempx;
// 	float tempy;
// 	int i;
// 	tempx = x;
// 	tempy = y;
// 	targetx = tempx + 50;
// 	while(tempx <= targetx)
// 	{
// 		if(get_pixel_color(targetx + 10, tempy, data) == 45000)
// 			break;
// 		my_mlx_pixel_put(data, tempx, tempy, 1);
// 		tempx++;
// 	}
// 	targety = tempy + 50;
// 	while(tempy <= targety)
// 	{	
// 		if(get_pixel_color(tempx, targety + 10, data) == 45000)
// 			break;
// 		my_mlx_pixel_put(data, tempx, tempy, 1);
// 		tempy++;
// 	}
// 	targetx = tempx - 50;
// 	while(tempx >= targetx)
// 	{
// 		if (x)
// 			if(get_pixel_color(targetx - 10, tempy, data) == 45000)
// 				break;
// 		my_mlx_pixel_put(data, tempx, tempx, 1);
// 		tempx--;
// 	}
// 	targety = tempy - 50;
// 	while(tempy >= targety)
// 	{
// 		if (y)
// 			if(get_pixel_color(tempx, targety-10, data) == 45000)
// 				break;
// 		my_mlx_pixel_put(data, tempx, tempy, 1);
// 		tempy--;
// 	}
// }




//chris version


// void draw_cube(t_data *data, float x, float y)
// {
// 	float targetx;
// 	float targety;
// 	float targetz;
// 	int i;
// 	targetx = x + 50;
// 	while(x <= targetx)
// 	{
// 		// if(get_pixel_color(x+10, y, data) == 45000)
// 		// 	break;
// 		my_mlx_pixel_put(data, x, y, 1);
// 		x++;
// 	}
// 	targety = y + 50;
// 	while(y <= targety)
// 	{	
// 		// if(get_pixel_color(x, y+10, data) == 45000)
// 		// 	break;
// 		my_mlx_pixel_put(data, x, y, 1);
// 		y++;
// 	}
// 	targetx = x - 50;
// 	while(x >= targetx)
// 	{
// 		// if(get_pixel_color(targetx-10, y, data) == 45000)
// 		// 	break;
// 		my_mlx_pixel_put(data, x, y, 1);
// 		x--;
// 	}
// 	targety = y - 50;
// 	while(y >= targety)
// 	{
// 		// if(get_pixel_color(x, targety-10, data) == 45000)
// 		// 	break;
// 		my_mlx_pixel_put(data, x, y, 1);
// 		y--;
// 	}
// }






// int	ft_detectpoint(t_data *data)
// {
// 	int	a;

// 	a = 19;
// 	while (a)
// 	{
// 		if (get_pixel_color(data->posX + a, data->posY, data) == 45000)
// 			return(1);
// 		a--;
// 	}
// 	a = 19;
// 	while (a)
// 	{
// 		if (get_pixel_color(data->posX - a, data->posY, data) == 45000)
// 			return(2);
// 		a--;
// 	}
// 	a = 19;
// 	while (a)
// 	{
// 		if (get_pixel_color(data->posX, data->posY + a, data) == 45000)
// 			return(3);
// 		a--;
// 	}
// 	a = 19;
// 	while (a)
// 	{
// 		if (get_pixel_color(data->posX, data->posY - a, data) == 45000)
// 			return(4);
// 		a--;
// 	}
// 	return(0);
// }

// int get_pixel_color(int x, int y, t_data *data)obsolete
// {
//     char *pixel;

//     // Calculate the pixel's memory address
//     pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

//     // Convert the pixel data to an integer (color)
//     return *(int *)pixel;
// }