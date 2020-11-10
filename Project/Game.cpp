//---------------------------------------------------------------------
//---------------------------------------------------------------------
//  (c) Mikael Fridenfalk
//  Template for use in the course:
//  Linear Algebra, Trigonometry and Geometry, 7.5 c
//  Uppsala University, Sweden
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Game.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

#include "Matrix.h"
Game::Game()
{
	mW = 1280, mH = 720.f;
	player = new Player();

    player->SetPosition(Vector2(mW / 2.0f, mH / 2.0f));

	Matrix m = Matrix(3);
	mMtxFont = new char[128][7][5];
	InitMtxFont();
	mCounter = 0;
	mMouseX = mMouseY = 0;
    mMouseButton = mMouseState = 0;

    mid = Vector2(mW / 2, mH / 2);

    SpawnAsteroids();

	//-------------------------------------------------------------------
	//TEST STUFF
	//-------------------------------------------------------------------

}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::ChangeSize(int w, int h)
{
    mW = w, mH = h;
	glViewport(0,0,mW,mH);                         // Reset Viewport
	glMatrixMode(GL_PROJECTION); glLoadIdentity(); // Reset The Projection Matrix
	glOrtho(0.0f,mW,mH,0.0f,-1.0f,.0f);            // Create Ortho View (0,0 At Top Left)
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();  // Reset The Modelview Matrix
}
void Game::Update()
{
	//player->SetPosition(45.0f, 45.0f);
	//player->SetRotation(mCounter / 1.0f);
	//player->SetScale(Vector2(sinf((float)mCounter / 30.0f), 1.0f));

	mouse.x = mMouseMotionX;
	mouse.y = mMouseMotionY;

    if (!lost)
    {
        player->Update();
        if (player->up)
        {
            particles.push_back(new Bullet(player->GetRotation() + 180.0f + (-22.5f + (float)(rand() % 45)), player->_position, true));
        }
        if (player->GetShoot())
        {
            bullets.push_back(new Bullet(player->GetRotation(), player->GetPosition(), false));
        }
    }

    for (auto a : asteroids)
    {
        a->Update();
    }

    for (auto b : bullets)
    {
        b->Update();
    }

    For(i, particles.size())
    {
        particles[i]->Update();
        if (particles[i]->GetShouldDie())
        {
            *particles[i] = *particles[particles.size() - 1];
            delete particles[particles.size() - 1];
            particles.pop_back();
        }

    }




    //----------------------------------------------------------------
    // Collisions
    //----------------------------------------------------------------

    For(i, bullets.size())
    {
        if (bullets[i]->GetShouldDie())
        {

            *bullets[i] = *bullets[bullets.size() - 1];
            delete bullets[bullets.size() - 1];
            bullets.pop_back();
            break;
        }

        For(j, asteroids.size())
        {
            if (CollisionManager::CheckCollision(bullets[i]->GetPosition(), asteroids[j]->circle))
            {
                score += asteroids[j]->GetPoints();

                Vector2 bulletDir = bullets[i]->direction / bullets[i]->speed;
                for (int k = 0; k < 2; k++)
                {

                    float degrees = (-1 + (2 * k)) * 90.0f;
                    int type = (int)asteroids[j]->size + 1;
                    if (type == (int)Asteroid::NOTHING)
                    {
                        For(w, 10)
                        {
                            particles.push_back(new Bullet(360/10 * w, asteroids[j]->GetPosition(), true));
                        }
                        goto BREAK;
                    }
                    Matrix m = Matrix::GetRotationMatrix(degrees);

                    std::cout << type << std::endl;

                    asteroids.push_back(new Asteroid(asteroids[j]->GetPosition(), m.GetTransformedVector(bulletDir), type));

                }

                BREAK:

                *bullets[i] = *bullets[bullets.size() - 1];
                delete bullets[bullets.size() - 1];
                bullets.pop_back();

                *asteroids[j] = *asteroids[asteroids.size() - 1];
                delete asteroids[asteroids.size() - 1];
                asteroids.pop_back();

                For(k, asteroids.size())
                {
                    asteroids[k]->circle.SetCenter(asteroids[k]->_position);
                }
                goto NEXT;

            }

        }
    NEXT:
        char _;
    }

    for (auto a : asteroids)
    {
        if (CollisionManager::CheckCollision(player->collision, a->circle) && !lost)
        {
            lost = true;

            player->SetScale(Vector2::Zero());

            For(w, 100)
            {
                particles.push_back(new Bullet((360 / 100.0f) * w, player->GetPosition(), false));
            }
        }
    }


    ConstrainStuff();
    if (asteroids.size() < 1) SpawnAsteroids();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Draw(void)
{
    
    //--------------------------------------------Clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    

	renderer.Render(player->GetLinesToRender());
    //renderer.Render(player->collision.GetLinesToRender());





    for (auto a : asteroids)
    {
        renderer.Render(a->GetLinesToRender());
       // renderer.Render(a->circle.GetLinesToRender());
    }

    for (auto b : bullets)
    {
        renderer.Render(b->GetLinesToRender());
        //renderer.Render(b->r.GetLinesToRender());
    }

    for (auto b : particles)
    {
        renderer.Render(b->GetLinesToRender());
        //renderer.Render(b->r.GetLinesToRender());
    }

    if(!lost)Draw_MtxText(mW / 2, 25.0f, std::to_string(score).c_str());
    else
    {
        Draw_MtxText((mW / 2) - 9  * 7.5f,  mH / 2, "GAME OVER");
        Draw_MtxText((mW / 2) - 10 * 7.5f, (mH / 2) + 50.0f, "YOU SCORED");
        Draw_MtxText((mW / 2) - std::to_string(score).length() * 7.5f, (mH / 2) + 100.0f, std::to_string(score).c_str());

        Draw_MtxText(10.0f,10.0f,  "DAN BURT");


    }
    //--------------------------------------------Geometry
//    glLineWidth(3);
//    glPointSize(10);
//
//
//    
//    int method[] = {GL_POINTS,GL_LINES,GL_LINE_STRIP,GL_LINE_LOOP,GL_POLYGON};
//    
//    For (i,5){
//        glBegin(method[i]);
//        float dx = 200 + 220*i;
//        float dy = 350;
//        glColor3ub(255,0,0);   glVertex3f(-50+dx,-50+dy,0);
//        glColor3ub(127,127,0); glVertex3f(-50+dx, 50+dy,0);
//        glColor3ub(0,255,0);   glVertex3f( 50+dx, 50+dy,0);
//        glColor3ub(0,0,255);   glVertex3f( 50+dx,-50+dy,0);
//        glEnd();
//    }
//	//--------------------------------------------Text
//	int a = mW - 300;
//	glColor3ub(255,0,0);
//	Draw_MtxText(a, mH - 4*24, "X = %4d  Y = %4d",
//                 mMouseX,mMouseY);
//	glColor3ub(100,100,220);
//	Draw_MtxText(a, mH - 3*24, "X = %4d  Y = %4d",
//                 mMouseMotionX,mMouseMotionY);
//    Draw_MtxText(a, mH - 2*24, "TIME = %7u",
//                 SDL_GetTicks());
//                 //printf("[ret = %u\n",ret););
//	//--------------------------------------------	
    mCounter++;
//    
//--------------------------------------------	
//	
}
void Game::ConstrainStuff()
{

    {
        if (player->rightMostPoint < 0.0f)
            player->SetPositionX(player->_position.x + mW + 30.0f);
        else if (player->leftMostPoint > mW)
            player->SetPositionX(player->_position.x - mW - 30.0f);

        if (player->lowestPoint < 0.0f)
            player->SetPositionY(player->_position.y + mH + 30.0f);
        else if (player->highestPoint > mH)
            player->SetPositionY(player->_position.y - mH - 30.0f);

    }

    for (auto a : asteroids)
    {
        if (a->rightMostPoint < 0.0f)
            a->SetPositionX(a->_position.x + mW + a->circle.radius * 2);
        else if (a->leftMostPoint > mW)
            a->SetPositionX(a->_position.x - mW - a->circle.radius * 2);

        if (a->lowestPoint < 0.0f)
            a->SetPositionY(a->_position.y + mH + a->circle.radius * 2);
        else if (a->highestPoint > mH)
            a->SetPositionY(a->_position.y - mH - a->circle.radius * 2);
    }

    for (auto a : bullets)
    {
        if (a->_position.x < 0.0f)
            a->SetPositionX(a->_position.x + mW + 30.0f);
        else if (a->_position.x > mW)
            a->SetPositionX(a->_position.x - mW - 30.0f);

        if (a->_position.y < 0.0f)
            a->SetPositionY(a->_position.y + mH + 30.0f);
        else if (a->_position.y > mH)
            a->SetPositionY(a->_position.y - mH - 30.0f);
    }
}
void Game::SpawnAsteroids()
{
    For(i, 10)
    {
        float distance = 250.0f;

        Matrix m = Matrix::GetRotationMatrix(rand() % 360);

        auto dir = m.GetTransformedVector(Vector2::Up());

        asteroids.push_back(new Asteroid(mid + Vector2((float)sin(36 * i), (float)cos(36 * i)) * distance, dir, Asteroid::Sizes::BIG));
    }
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::NormalKeysDown(unsigned char key, int state)
{
    player->OnKeyDown(key);

}
void Game::NormalKeysUp(unsigned char key, int state)
{
    player->OnKeyUp(key);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::SpecialKeysDown(int key, int state)
{
    player->OnKeyDown(key);


 //   if (key == SDLK_LEFT)
	//{
	/////*	renderer.SetDrawColour(255, 255, 255);
	////	Draw_MtxText(10.0f, 10.0f, "I AM HOLDING LEFT");*/
	////	mMouseMotionX = mW / 2;
 //       std::cout << key <<' '<< state << std::endl;
	//}
 //   if (key == SDLK_RIGHT){}
 //   if (key == SDLK_UP){}
 //   if (key == SDLK_DOWN){}
}
void Game::SpecialKeysUp(int key, int state)
{
    player->OnKeyUp((SDL_Keycode)key);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Mouse(int button, int state, int x, int y)
{
	mMouseButton = button;//SDL_BUTTON_LEFT/SDL_BUTTON_MIDDLE/SDL_BUTTON_RIGHT
	mMouseState = state;//SDL_PRESSED/SDL_RELEASED
	mMouseX = x; mMouseY = y;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::MouseMotion(int x, int y)
{
    mMouseMotionX = x; mMouseMotionY = y;
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                              Font
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::InitMtxFont(){
	
	For (i,128) For (j,7) For (k,5) mMtxFont[i][j][k] = 1;
	
    const char F0[] =
    "00000" "00000" "00000" "11111" "00000" "00000" "00000"//-
    "00000" "00000" "00000" "00000" "00000" "01100" "01100"//.
    "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
    "01110" "10001" "10011" "10101" "11001" "10001" "01110"//0
    "00100" "01100" "00100" "00100" "00100" "00100" "01110"//1
    "01110" "10001" "00001" "00010" "00100" "01000" "11111"//2
    "01110" "10001" "00001" "00110" "00001" "10001" "01110"//3
    "00010" "00110" "01010" "10010" "11111" "00010" "00111"//4
    "11111" "10000" "11110" "00001" "00001" "10001" "01110"//5
    "01110" "10001" "10000" "11110" "10001" "10001" "01110"//6
    "11111" "10001" "00010" "00010" "00100" "00100" "00100"//7
    "01110" "10001" "10001" "01110" "10001" "10001" "01110"//8
    "01110" "10001" "10001" "01111" "00001" "00001" "01110"//9
    "00000" "01100" "01100" "00000" "01100" "01100" "00000"//:
    "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
    "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
    "00000" "00000" "11111" "00000" "11111" "00000" "00000"//=
    "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
    "01110" "10001" "10001" "00010" "00100" "00000" "00100"//?
    "11111" "11111" "11111" "11111" "11111" "11111" "11111"//
    "01110" "10001" "10001" "11111" "10001" "10001" "10001"//A
    "11110" "10001" "10001" "11110" "10001" "10001" "11110"//B
    "01110" "10001" "10000" "10000" "10000" "10001" "01110"//C
    "11110" "10001" "10001" "10001" "10001" "10001" "11110"//D
    "11111" "10000" "10000" "11110" "10000" "10000" "11111"//E
    "11111" "10000" "10000" "11110" "10000" "10000" "10000"//F
    "01110" "10001" "10000" "10111" "10001" "10001" "01110"//G
    "10001" "10001" "10001" "11111" "10001" "10001" "10001"//H
    "01110" "00100" "00100" "00100" "00100" "00100" "01110"//I
    "00001" "00001" "00001" "00001" "10001" "10001" "01110"//J
    "10001" "10010" "10100" "11000" "10100" "10010" "10001"//K
    "10000" "10000" "10000" "10000" "10000" "10000" "11111"//L
    "10001" "11011" "10101" "10101" "10001" "10001" "10001"//M
    "10001" "10001" "11001" "10101" "10011" "10001" "10001"//N
    "01110" "10001" "10001" "10001" "10001" "10001" "01110"//O
    "11110" "10001" "10001" "11110" "10000" "10000" "10000"//P
    "01110" "10001" "10001" "10001" "10101" "10010" "01101"//Q
    "11110" "10001" "10001" "11110" "10100" "10010" "10001"//R
    "01111" "10000" "10000" "01110" "00001" "00001" "11110"//S
    "11111" "00100" "00100" "00100" "00100" "00100" "00100"//T
    "10001" "10001" "10001" "10001" "10001" "10001" "01110"//U
    "10001" "10001" "10001" "10001" "10001" "01010" "00100"//V
    "10001" "10001" "10001" "10101" "10101" "10101" "01010"//W
    "10001" "10001" "01010" "00100" "01010" "10001" "10001"//X
    "10001" "10001" "10001" "01010" "00100" "00100" "00100"//Y
    "11111" "00001" "00010" "00100" "01000" "10000" "11111";//Z
	
	For (i,46) For (j,7) For (k,5) mMtxFont[i+45][j][k] = F0[35*i+5*j+k];
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Draw_MtxText(float x, float y, const char *fmt,...)
{
	
	//--------------------
	glPushMatrix();
	glLoadIdentity();
    //--------------------
	char text[256]; va_list	ap;
	if (fmt == NULL) return;
    va_start(ap, fmt); 
#ifdef _WIN32 //32-bit and 64-bit Windows
    vsprintf_s(text, fmt, ap);
#else
    vsprintf(text, fmt, ap);
#endif
    va_end(ap);
	//--------------------
    int n = 0;
	glPointSize(2.f);
    glBegin(GL_POINTS);
	while (text[n] != 0){
		Draw_MtxFont(x+14.f*float(n), y, text[n]);
		n++;
	}
    glEnd();
    //--------------------
	glPopMatrix();
    //--------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void inline Game::Draw_MtxFont(float x, float y, Uint8 c)
{
	if (c == ' ') return;	
    For (m,7) For (n,5)
	{
        if (mMtxFont[c][m][n] == '0') continue;
		glVertex2f(x+2*n,y+2*m);
	}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
