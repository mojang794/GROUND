#include "Texture.h"
#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

engine::Texture::Texture()
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void engine::Texture::Load(const char* path)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void engine::Texture::setTexParameteri(unsigned int target, unsigned int option, unsigned int param)
{
	glTexParameteri(target, option, param);
}

void engine::Texture::Activate(unsigned int TEXTURE)
{
	glActiveTexture(TEXTURE);
}

void engine::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void engine::Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void engine::Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
