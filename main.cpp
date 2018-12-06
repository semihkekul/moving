#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "graphics/graphics.h"
#include "graphics/Sprites.h"
#include "Giresun/precision.h"
#include "Giresun/Vector2D.h"
#include "Giresun/pfgen.h"

using namespace std;
using namespace Giresun;

#define printf pspDebugScreenPrintf

/*** grafik************************************/
Sprite* sprites;
#define SAHA_INDEX 0
#define BALL_INDEX 1
#define FIREBALL_INDEX 4
/*** karakterler***/
#define ANGRY_INDEX 2
#define BAD_EGG_INDEX 3
/*** karakterler***/
#define ALL_SPRITES 5
/**********************************************/




/*******************fizik***********************/
Particle* particles;
#define ALL_PARTICLES 3
#define PARTICLE_BALL_INDEX 0
#define PARTICLE_ANGRY_INDEX 1
#define PARTICLE_BAD_EGG_INDEX 2
#define DURATION 0.01
/**********************************************/

/*** GLOBALS***********************************/
int P1_x;
int P1_y;
/**********************************************/
PSP_MODULE_INFO("Move Me", 0, 1, 1);

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
}
void loadSprites()
{
	sprites = (Sprite*)malloc(sizeof(Sprite)*ALL_SPRITES);
	sprites[SAHA_INDEX].loadSprite("saha.png",2000,500,300);
	sprites[BALL_INDEX].loadSprite("football.png",100,15,15);
	sprites[ANGRY_INDEX].loadSprite("angry.png",100,32,32);
	sprites[BAD_EGG_INDEX].loadSprite("bad_egg.png",100,32,32);
	sprites[FIREBALL_INDEX].loadSprite("fireball.png",100,32,32);
}

void loadParticles() // ballistics
{
	particles=(Particle*)malloc(sizeof(Particle)*ALL_PARTICLES);
	particles[PARTICLE_BALL_INDEX].setMass(999999.0f); // 2.0kg
	particles[PARTICLE_BALL_INDEX].setVelocity(5.0f, 5.0f); 
	particles[PARTICLE_BALL_INDEX].setAcceleration(0.0f, 0.0f);
	particles[PARTICLE_BALL_INDEX].setDamping(0.99f);
	particles[PARTICLE_BALL_INDEX].setPosition(.0f,.0f);
	particles[PARTICLE_BALL_INDEX].clearAccumulator();
	
	particles[PARTICLE_ANGRY_INDEX].setMass(2.0f); // 2.0kg
	particles[PARTICLE_ANGRY_INDEX].setVelocity(0.0f, 0.0f); 
	particles[PARTICLE_ANGRY_INDEX].setAcceleration(0.0f, 0.0f);
	particles[PARTICLE_ANGRY_INDEX].setDamping(0.99f);
	particles[PARTICLE_ANGRY_INDEX].setPosition(.0f,.0f);
	particles[PARTICLE_ANGRY_INDEX].clearAccumulator();
	
	
}


void doControls()
{
	int topBound    = 0;
	int bottomBound = 272;
	int leftBound   = 0;
	int rightBound  = 480;
	int speed 		= 5;
	
	SceCtrlData pad;
	sceCtrlReadBufferPositive(&pad, 1);
	
	if(pad.Buttons & PSP_CTRL_UP) 
	{	
		if(P1_y >= topBound + speed) 
			{
				P1_y-= speed;
			}
	} 
	else if(pad.Buttons & PSP_CTRL_RIGHT) 
	{
		if(P1_x <= rightBound - speed - sprites[ANGRY_INDEX].w) 
			{
				P1_x+= speed;
			}
	} 
	else if(pad.Buttons & PSP_CTRL_DOWN) 
		{
			if(P1_y <= bottomBound - speed - sprites[ANGRY_INDEX].h) 
				{
					P1_y+= speed;
				}
		} 
	else if(pad.Buttons & PSP_CTRL_LEFT) 
	{
		if(P1_x >= leftBound + speed) 
			{
				P1_x-= speed;
			}
	}
}

void drawScene()
{
	blitAlphaImageToScreen(0, 0, 500, 300, sprites[SAHA_INDEX].m_image, 0, -10); 
	blitAlphaImageToScreen(0 , 0, 
			sprites[BALL_INDEX].w,sprites[BALL_INDEX].h, 
			sprites[BALL_INDEX].m_image, 
			particles[PARTICLE_BALL_INDEX].getPosition().m_x, 
			particles[PARTICLE_BALL_INDEX].getPosition().m_y); 
	blitAlphaImageToScreen(0 , 0, 
			sprites[ANGRY_INDEX].w,sprites[ANGRY_INDEX].h, 
			sprites[ANGRY_INDEX].m_image, 
			particles[PARTICLE_ANGRY_INDEX].getPosition().m_x, 
			particles[PARTICLE_ANGRY_INDEX].getPosition().m_y); 
	blitAlphaImageToScreen(0 , 0, 
			sprites[BAD_EGG_INDEX].w,sprites[BAD_EGG_INDEX].h, 
			sprites[BAD_EGG_INDEX].m_image, P1_x ,P1_y);
}
void init()
{
	pspDebugScreenInit();
	SetupCallbacks();
	initGraphics();
	loadSprites();
	loadParticles();
}
ParticleForceRegistry registry;
void step()
{
	registry.updateForces(DURATION);
	particles[PARTICLE_BALL_INDEX].integrate(DURATION);
	particles[PARTICLE_ANGRY_INDEX].integrate(DURATION);

}
int main() 
{
	init();
	
	ParticleSpring ps(&particles[PARTICLE_BALL_INDEX],1.0f,2.0f);
	registry.add(&particles[PARTICLE_ANGRY_INDEX], &ps);
		
	while(1) 
	{
		doControls();	
		step();
		pspDebugScreenSetXY(10, 2);
		clearScreen(RGB(0, 0, 0));
		drawScene();
		flipScreen();
	}
	sceKernelSleepThread();
	return 0;
}
