#include <GL/gl.h>

#include <config.h>
#include <event.h>

#include <layer.h>

Layer::Layer() {

    puts("Layer::Layer()");

    Defaults();
}

Layer::~Layer() {

    puts("Layer::~Layer()");
}

void Layer::Defaults() {

    _use_screen_coords = false;

    // Default zoom is no zoom (1.0).
    _zoom_level = 1.0;
    // And center is the world origin (0.0, 0.0).
    _center.x = 0.0;
    _center.y = 0.0;
    // And no scale applied (1.0, 1.0), everything in original sizes.
    _scale.x = 1.0;
    _scale.y = 1.0;

    // Read zoom and pan factor defaults.
    _zoom_factor = Config::Instance()->layer_zoom_factor;
    _pan_factor = Config::Instance()->layer_pan_factor;
}

void Layer::PreRender() {

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho(
        _viewport.left, _viewport.right,
        _viewport.bottom, _viewport.top,
        _viewport.near, _viewport.far );
    glMatrixMode( GL_MODELVIEW );
}

void Layer::PostRender() {

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
}

bool Layer::Init( Volume& viewport ) {

    if( _use_screen_coords ) {
        _viewport.left = 0.0;
        _viewport.right = Config::Instance()->screen_width;
        _viewport.bottom = Config::Instance()->screen_height;
        _viewport.top = 0.0;
        _viewport.near = -1.0;
        _viewport.far = 1.0;
    } else {
        _viewport = viewport;
    }

    return true;
}

void Layer::Resize(int width, int height) {

    width = width;
    height = height;

// TODO : [COMMENT] Add comment to explain what's going on here.
    if( ! _use_screen_coords ) {
        UpdateViewport();
    }
}

void Layer::UpdateViewport() {

    double zoomed_width, zoomed_height;

// TODO : [COMMENT] And some comments here would be fine.
    _zoom_level += (Event::_zoom_delta) * _zoom_factor;

    _center.x -= _scale.x * (Event::_pan_delta.x) * _pan_factor;
    _center.y -= _scale.y * (Event::_pan_delta.y) * _pan_factor;

    zoomed_width = 0.5 * Config::Instance()->world_width * _zoom_level;
    zoomed_height = 0.5 * Config::Instance()->world_height * _zoom_level;

    _scale.x = (_viewport.right - _viewport.left) / (Config::Instance()->world_width * Config::Instance()->screen_width);
    _scale.y = (_viewport.bottom - _viewport.top) / (Config::Instance()->world_height * Config::Instance()->screen_height);

    _viewport.left = _center.x - zoomed_width;
    _viewport.right = _center.x + zoomed_width;
    _viewport.top = _center.y + zoomed_height;
    _viewport.bottom = _center.y - zoomed_height;
}

