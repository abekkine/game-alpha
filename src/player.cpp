#include <math.h>
#include <GL/gl.h>

#include <gamestate.h>
#include <player.h>
#include <config.h>

Player::Player(double x, double y)
{
    _life = 1.0;
    _position.x = x;
    _position.y = y;
    _size = 0.05;
    _group = 0;
    _type = objPlayer;
}

Player::~Player()
{
    GameState::Instance()->State(GameState::gsGAMEOVER);
}

void Player::Render()
{
    RenderV2();
}

void Player::RenderV1()
{
    static double w = 0.02;
    static double h = 0.06;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _position.x, _position.y, 0.0 );
    // Ship
    glColor3d( 1.0, 1.0, 1.0 );
    glBegin( GL_TRIANGLES );
    glVertex2d( 0.0, h );
    glVertex2d(  w, 0.0 );
    glVertex2d( -w, 0.0 );
    glEnd();
    // Shadow
    glColor3d( 0.3, 0.3, 0.3 );
    glBegin( GL_QUADS );
    glVertex2d( -w, -0.01 );
    glVertex2d( -w, -0.02 );
    glVertex2d(  w, -0.02 );
    glVertex2d(  w, -0.01 );
    glEnd();
    glPopMatrix();
}

Bullet* Player::Fire()
{
    Bullet* bullet = new Bullet(_position.x, _position.y+0.06);
    bullet->Group(0);
    bullet->Velocity(0.0, 0.00075);

    return bullet;
}

void Player::MoveLeft()
{
    if( _position.x > -0.48 * Config::Instance()->world_width ) {
        _position.x -= 0.005; 
    }
}

void Player::MoveRight()
{
    if( _position.x < 0.48 * Config::Instance()->world_width ) {
        _position.x += 0.005;
    }
}
 
bool Player::CollisionWith(Object* object)
{
    object = object;

    return false;
}

void Player::RenderV2()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslated(_position.x, _position.y, 0.0);
    glScaled(0.0001, 0.0001, 1.0);
    glRotated(180.0, 0.0, 0.0, 1.0);
   
    {
        const double x1 = 15.0;
        const double x2 = 20.0;
        const double x3 = 65.0;
        static double alpha = 0.0;

        glColor3ub(0xec, 0x5e, 0xc8);
        glBegin(GL_POLYGON);
            glVertex2d(x2 * cos(alpha), -330.0);
            glVertex2d(x3 * cos(alpha), -210.0);
            glVertex2d(x1 * cos(alpha), -210.0);
        glEnd();

        glColor3ub(0xec, 0x5e, 0xc8);
        glBegin(GL_POLYGON);
            glVertex2d(-x2 * cos(alpha), -330.0);
            glVertex2d(-x3 * cos(alpha), -210.0);
            glVertex2d(-x1 * cos(alpha), -210.0);
        glEnd();
        alpha += 0.05;
    }

    glColor3ub(0x50, 0xce, 0x80);
    glBegin(GL_POLYGON);
        glVertex2d(-295.0, 120.0);
        glVertex2d(-95.0, 115.0);
        glVertex2d(-80.0, -240.0);
        glVertex2d(-295.0, 120.0);
    glEnd();

    glColor3ub(0xfb, 0x26, 0x2d);
    glBegin(GL_POLYGON);
        glVertex2d(-170.0, -205.0);
        glVertex2d(-105.0, -245.0);
        glVertex2d(-115.0, -90.0);
        glVertex2d(-170.0, -205.0);
    glEnd();

    glColor3ub(0x25, 0x43, 0xc6);
    glBegin(GL_POLYGON);
        glVertex2d(-95.0, 40.0);
        glVertex2d(-95.0, 120.0);
        glVertex2d(95.0, 120.0);
        glVertex2d(95.0, 40.0);
        glVertex2d(-95.0, 40.0);
    glEnd();

    glColor3ub(0x12, 0x69, 0x46);
    glBegin(GL_POLYGON);
        glVertex2d(-10.0, -145.0);
        glVertex2d(-10.0, -135.0);
        glVertex2d(-100.0, 45.0);
        glVertex2d(100.0, 45.0);
        glVertex2d(10.0, -135.0);
        glVertex2d(10.0, -145.0);
        glVertex2d(-10.0, -145.0);
    glEnd();

    glColor3ub(0xf7, 0xf0, 0xb5);
    glBegin(GL_POLYGON);
        glVertex2d(-85.0, -305.0);
        glVertex2d(-95.0, 30.0);
        glVertex2d(-85.0, 30.0);
        glVertex2d(-5.0, -130.0);
        glVertex2d(-5.0, -150.0);
        glVertex2d(-85.0, -305.0);
    glEnd();

    glColor3ub(0x50, 0xce, 0x80);
    glBegin(GL_POLYGON);
        glVertex2d(295.0, 120.0);
        glVertex2d(95.0, 115.0);
        glVertex2d(80.0, -240.0);
        glVertex2d(295.0, 120.0);
    glEnd();

    glColor3ub(0xfb, 0x26, 0x2d);
    glBegin(GL_POLYGON);
        glVertex2d(170.0, -205.0);
        glVertex2d(105.0, -245.0);
        glVertex2d(115.0, -90.0);
        glVertex2d(170.0, -205.0);
    glEnd();

    glColor3ub(0xf7, 0xf0, 0xb5);
    glBegin(GL_POLYGON);
        glVertex2d(85.0, -305.0);
        glVertex2d(95.0, 30.0);
        glVertex2d(85.0, 30.0);
        glVertex2d(5.0, -130.0);
        glVertex2d(5.0, -150.0);
        glVertex2d(85.0, -305.0);
    glEnd();

    glColor3ub(0x33, 0xc3, 0xfe);
    glBegin(GL_POLYGON);
        glVertex2d(-65.0, 70.0);
        glVertex2d(-69.7, 93.4);
        glVertex2d(-82.6, 112.4);
        glVertex2d(-101.6, 125.3);
        glVertex2d(-125.0, 130.0);
        glVertex2d(-148.4, 125.3);
        glVertex2d(-167.4, 112.4);
        glVertex2d(-180.3, 93.4);
        glVertex2d(-185.0, 70.0);
        glVertex2d(-180.3, 46.6);
        glVertex2d(-167.4, 27.6);
        glVertex2d(-148.4, 14.7);
        glVertex2d(-125.0, 10.0);
        glVertex2d(-101.6, 14.7);
        glVertex2d(-82.6, 27.6);
        glVertex2d(-69.7, 46.6);
        glVertex2d(-65.0, 70.0);
    glEnd(); 

    glColor3ub(0xfc, 0x42, 0x83);
    glBegin(GL_POLYGON);
        glVertex2d(59.7, -180.3);
        glVertex2d(42.2, -138.1);
        glVertex2d(-0.0, -120.6);
        glVertex2d(-42.2, -138.1);
        glVertex2d(-59.7, -180.3);
        glVertex2d(-42.2, -222.5);
        glVertex2d(-0.0, -240.0);
        glVertex2d(42.2, -222.5);
        glVertex2d(59.7, -180.3);
    glEnd();

    glColor3ub(0x37, 0x3f, 0xbb);
    glBegin(GL_POLYGON);
        glVertex2d(-42.0, -222.0);
        glVertex2d(-59.4, -180.0);
        glVertex2d(-41.9, -137.8);
        glVertex2d(-7.7, -123.6);
        glVertex2d(-5.0, -130.0);
        glVertex2d(-5.0, -150.0);
        glVertex2d(-42.0, -222.0);
    glEnd();
    glColor3ub(0x37, 0x3f, 0xbb);
    glBegin(GL_POLYGON);
        glVertex2d(42.6, -222.0);
        glVertex2d(5.0, -150.0);
        glVertex2d(5.0, -130.0);
        glVertex2d(8.3, -123.6);
        glVertex2d(42.5, -137.8);
        glVertex2d(60.0, -180.0);
        glVertex2d(42.6, -222.0);
    glEnd();

    glColor3ub(0x33, 0xc3, 0xfe);
    glBegin(GL_POLYGON);
        glVertex2d(184.5, 69.5);
        glVertex2d(179.8, 92.9);
        glVertex2d(166.9, 111.9);
        glVertex2d(147.9, 124.8);
        glVertex2d(124.5, 129.5);
        glVertex2d(101.1, 124.8);
        glVertex2d(82.1, 111.9);
        glVertex2d(69.2, 92.9);
        glVertex2d(64.5, 69.5);
        glVertex2d(69.2, 46.1);
        glVertex2d(82.1, 27.1);
        glVertex2d(101.1, 14.2);
        glVertex2d(124.5, 9.5);
        glVertex2d(147.9, 14.2);
        glVertex2d(166.9, 27.1);
        glVertex2d(179.8, 46.1);
        glVertex2d(184.5, 69.5);
    glEnd();

    glPopMatrix();
}

