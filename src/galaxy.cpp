#include <stdio.h>
//#include <GL/gl.h>

#include <vector.h>
#include <config.h>
#include <writer.h>
#include <galaxy.h>

Galaxy::Galaxy()
{
    puts("Galaxy::Galaxy()");

    Defaults();
}

Galaxy::~Galaxy()
{
    puts("Galaxy::~Galaxy()");

    delete _starbuilder;
}

void Galaxy::Defaults()
{
    _visible = true;
    _wireframe = false;

    _zoom_factor = 0.0;
    _pan_factor = 0.0;
}

bool Galaxy::Init( Volume& viewport )
{
    bool result = true;

    Layer::Init( viewport );
   
    _zoom_factor = Config::Instance()->galaxy_zoom_factor;
    _pan_factor = Config::Instance()->galaxy_pan_factor;
    _step_delta = Config::Instance()->galaxy_step_delta;

    _starbuilder = new StarBuilder();
    _starbuilder->Init();
    _starbuilder->SetSizeFactor( Config::Instance()->galaxy_size_factor );

    Writer::Instance()->Add("X( %f )", &_viewport.left );
    Writer::Instance()->Add("Y( %f )", &_viewport.bottom );

    return result;
}

void Galaxy::Toggle() {

    _visible = not _visible;
}

void Galaxy::ToggleWireframe() {

    _wireframe = not _wireframe;
}

void Galaxy::Render()
{

    if( _visible ) {

        PreRender();
        RenderGalaxyLayer();
        PostRender();
    }
}

void Galaxy::RenderGalaxyLayer()
{
    Vector2d begin;
    Vector2d end;
    Vector2d step;
    Vector2d begin_rounded;

    begin.x = _viewport.left;
    begin.y = _viewport.bottom;

    begin_rounded.x = floor( begin.x );
    begin_rounded.y = floor( begin.y );

    end.x = _viewport.right;
    end.y = _viewport.top;

    _starbuilder->Reset();
    for( step.x = begin_rounded.x; step.x < (end.x+_step_delta); step.x += _step_delta ) {

        for( step.y = begin_rounded.y; step.y < (end.y+_step_delta); step.y += _step_delta ) {

            _starbuilder->Render( step, _wireframe );

        }
    }
}

