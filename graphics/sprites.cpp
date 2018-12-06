#include "sprites.h"

/** inspred by ****************
http://www.psp-programming.com
******************************/



Sprite::Sprite(string imgFileName,int bufferSize,int width, int height)
{
	m_buffer = (char*)malloc(sizeof(char)*bufferSize);
	sprintf(m_buffer,imgFileName.c_str());
	m_image = loadImage(m_buffer);
	w = width;
	h = height;
}

Sprite::Sprite(){};

void Sprite::loadSprite(string imgFileName,int bufferSize,int width, int height)
{
	m_buffer = (char*)malloc(sizeof(char)*bufferSize);
	sprintf(m_buffer,imgFileName.c_str());
	m_image = loadImage(m_buffer);
	w = width;
	h = height;
}