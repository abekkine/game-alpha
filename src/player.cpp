#include <GL/gl.h>

#include <player.h>
#include <config.h>

Player::Player(double x, double y)
{
    _x = x;
    _y = y;
}

Player::~Player()
{
}

void Player::Render()
{
    static double w = 0.02;
    static double h = 0.06;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _x, _y, 0.0 );
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
    Bullet* bullet = new Bullet(_x, _y+0.06);
    bullet->Owner(0);
    bullet->Velocity(0.0, 0.00075);

    return bullet;
}

void Player::MoveLeft()
{
    if( _x > -0.48 * Config::Instance()->world_width ) {
        _x -= 0.005; 
    }
}

void Player::MoveRight()
{
    if( _x < 0.48 * Config::Instance()->world_width ) {
        _x += 0.005;
    }
}
 
bool Player::Alive()
{
    // TODO : implement
    return true;
}
