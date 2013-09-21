#include <GL/gl.h>
#include <math.h>

#include <enemy.h>
#include <config.h>

Enemy::Enemy(double x, double y)
{
    _x = x;
    _y = y;
    _x0 = _x;
    _y0 = _y;
    _alpha = 0.0;
    _span = 0.02;
}

Enemy::~Enemy()
{
}

void Enemy::Render()
{
    static double w = 0.02;
    static double h = 0.02;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _x, _y, 0.0 );

    glColor3d(1.0, 1.0, 1.0);
    glBegin( GL_QUADS );
    glVertex2d( -w, -h );
    glVertex2d( -w,  h );
    glVertex2d(  w,  h );
    glVertex2d(  w, -h );
    glEnd();
    glPopMatrix();

    _alpha += 0.01;
    _x = _x0 + _span * sin(_alpha);
    _y = _y0 + 0.005 * sin(_alpha*4.0);
}
