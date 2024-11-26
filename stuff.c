
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
