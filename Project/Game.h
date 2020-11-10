//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
#include <cmath>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Rectangle.h"
#include "Renderer.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Bullet.h"

#include "Asteroid.h"
//---------------------------------------------------------------------
#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)
//---------------------------------------------------------------------
class Game 
{
public:
    //-------------------------------------------------------
    Game(void);
    //-------------------------------------------------------

	//-------------------------------------------------------
	//TEST
    
    
    
    Vector2 mouse;
    Vector2 mid;

    int score = 0;
    bool lost = false;


	//-------------------------------------------------------
	



    std::vector<Asteroid*> asteroids;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> particles;


	Player* player;
	Renderer renderer;



    void  ChangeSize(int w, int h);
	void Update();
    void  Draw();
    void ConstrainStuff();

    void SpawnAsteroids();
    //-------------------------------------------------------
    void  NormalKeysDown(unsigned char key, int state);
    void  NormalKeysUp(unsigned char key, int state);
    void  SpecialKeysDown(int key, int state);
    void  SpecialKeysUp(int key, int state);
    void  Mouse(int button, int state, int x, int y);
    void  MouseMotion(int x, int y);
    //-------------------------------------------------------
	void  InitMtxFont();
	void  Draw_MtxText(float x, float y, const char *fmt,...);
	void  Draw_MtxFont(float x, float y, Uint8 c);
    //-------------------------------------------------------
    float mW, mH;
    int   mCounter;
    int   mMouseX, mMouseY, mMouseMotionX, mMouseMotionY;
    int   mMouseButton, mMouseState;
    //-------------------------------------------------------
    char  (*mMtxFont)[7][5];

    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
