#ifndef _SPRITES_H
#define _SPRITES_H

#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "graphics.h"
using namespace std;
/** inspred by ****************
http://www.psp-programming.com
******************************/


 #define RGB(r, g, b) (0xFF000000 | ((b)<<16) | ((g)<<8) | (r))
// #define topBound    0;
// #define bottomBound 272;
// #define leftBound   0;
// #define rightBound  480;
// int imageSize = 32;
// int dir = 0;
// int go = 0;
// int speed = 10;
// int trail = 0;

class Sprite
{
	public:
	Sprite(string imgFileName,int bufferSize, int width, int height);
	Sprite();
	void loadSprite(string imgFileName,int bufferSize,int width, int height);
	Image* m_image;
	char* m_buffer;
	int w;
	int h;
	

};

#endif
