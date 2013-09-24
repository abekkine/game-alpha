#include <GL/gl.h>

#include <bullet.h>
#include <config.h>

Bullet::Bullet(double x, double y)
{
    _x = x;
    _y = y;
    _vx = 0.0;
    _vy = 0.0;
    _owner = 0;
}

Bullet::~Bullet()
{
}

void Bullet::Owner(int owner)
{
    _owner = owner;
}

void Bullet::Velocity(double vx, double vy)
{
    _vx = vx;
    _vy = vy;
}

void Bullet::Render()
{
    const double w = 0.002;
    const double h = 0.005;

    glPushMatrix();
    glLoadIdentity();
    glTranslated(_x, _y, 0.0);

    glColor3d(0.8, 0.8, 0.8);

    glBegin(GL_QUADS);
    glVertex2d( -w, -h );
    glVertex2d( -w,  h );
    glVertex2d(  w,  h );
    glVertex2d(  w, -h );
    glEnd();

    glPopMatrix();

    _x += _vx;
    _y += _vy;
}

