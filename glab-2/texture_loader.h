#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "windows.h"
#include "glut.h"

#define ALPHA_VALUE 255

int LoadTexture(const std::string& filename)
{
	int textureID = -1;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;
	byte* texture;

	std::ifstream file(filename);
	if(file.is_open()){

		if(!file.read(reinterpret_cast<char*>(&infoheader), sizeof(BITMAPFILEHEADER))){
			std::cout << "error read bitmap file header" << std::endl;
			return textureID;
		}
		if(!file.read(reinterpret_cast<char*>(&infoheader), sizeof(BITMAPFILEHEADER))){
			std::cout << "error read bitmap info header" << std::endl;
			return textureID;
		}

		texture = static_cast<byte*>(std::malloc(infoheader.biWidth * infoheader.biHeight * 4));
		std::memset(texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

		for(int i = 0, j = 0; i < infoheader.biWidth * infoheader.biHeight; ++i, ++j){
			
			if(!file.read(reinterpret_cast<char*>(&rgb), sizeof(RGBTRIPLE))){
				std::cout << "error read rgb" << std::endl;
				return textureID;
			}

			texture[j] = rgb.rgbtRed;
			texture[++j] = rgb.rgbtGreen;
			texture[++j] = rgb.rgbtBlue;
			texture[++j] = ALPHA_VALUE;
		}
		file.close();

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, texture);

		std::free(texture);
	}
	else{
		std::cout << "error open file" << std::endl;
	}
	return textureID;
}