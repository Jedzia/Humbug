@echo off
if exist HumbugSprites.dat del HumbugSprites.dat
DAT -a -t BMP -c1 -bpp 16 -s1 HumbugSprites.dat gfx\Tiles1.bmp
DAT -a -t BMP -c1 -bpp 16 -s1 HumbugSprites.dat gfx\BlobberSide.bmp
ren HumbugSprites.dat HumbugSprites.dat