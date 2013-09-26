#include <GL/gl.h>

#include <player.h>
#include <config.h>

Player::Player(double x, double y)
{
    _position.x = x;
    _position.y = y;
    _size = 0.05;
    _group = 0;
    _type = objPlayer;
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
 
bool Player::Alive()
{
    // TODO : implement
    return true;
}

bool Player::CollisionWith(Object* object)
{
    object = object;

    return false;
}
 
