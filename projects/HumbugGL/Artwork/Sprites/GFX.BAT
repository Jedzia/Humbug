@echo off
if exist HumbugGLSprites.dat del HumbugGLSprites.dat
DAT -a -t BMP -c1 -bpp 16 -s1 HumbugGLSprites.dat gfx\Tiles1.bmp
DAT -a -t BMP -c1 -bpp 16 -s1 HumbugGLSprites.dat gfx\BlobberSide.bmp
ren HumbugGLSprites.dat HumbugGLSprites.dat