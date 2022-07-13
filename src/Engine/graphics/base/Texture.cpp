#include "Texture.h"
#include "../../GR_cross_definitions.h"
#include <iostream>

gr::base::Texture::Texture()
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void gr::base::Texture::Load(const char* path)
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

void gr::base::Texture::setTexParameteri(unsigned int target, unsigned int option, unsigned int param)
{
	glTexParameteri(target, option, param);
}

void gr::base::Texture::Activate(unsigned int TEXTURE)
{
	glActiveTexture(TEXTURE);
}

void gr::base::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void gr::base::Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void gr::base::Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
