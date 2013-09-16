#include <stdio.h>
#include <GL/gl.h>

#include <config.h>
#include <writer.h>
#include <starbuilder.h>

StarBuilder::StarBuilder()
:WIRE_COLOR(0.25) {
    
    puts("StarBuilder::StarBuilder()");

    Defaults();
}

StarBuilder::~StarBuilder() {

    puts("StarBuilder::~StarBuilder()");

    delete _existence;
    delete _feature;
}

void StarBuilder::Defaults() {

    _wireframe = false;

    _size_factor = 1.0;
    _existence = 0;
    _feature = 0;
    
    _x = 0.0;
    _y = 0.0;
    _color = 0;

    _wire_color[0] = WIRE_COLOR;
    _wire_color[1] = WIRE_COLOR;
    _wire_color[2] = WIRE_COLOR;
    _wire_color[3] = 1.0;

    _color_anomaly[0] = 1.0;
    _color_anomaly[1] = 0.0;
    _color_anomaly[2] = 0.0;
    _color_anomaly[3] = 1.0;

    _class_index = 0;

    // Class parameters
    _color_class[0][0] = 0.375;
    _color_class[0][1] = 0.5;
    _color_class[0][2] = 1.0;
    _color_class[0][3] = 1.0;
    _radius_min[0] = 6.0;
    _radius_range[0] = 3.0;

    _color_class[1][0] = 0.75;
    _color_class[1][1] = 0.75;
    _color_class[1][2] = 1.0;
    _color_class[1][3] = 1.0;
    _radius_min[1] = 2.0;
    _radius_range[1] = 4.0;

    _color_class[2][0] = 0.875;
    _color_class[2][1] = 0.875;
    _color_class[2][2] = 1.0;
    _color_class[2][3] = 1.0;
    _radius_min[2] = 1.5;
    _radius_range[2] = 0.5;

    _color_class[3][0] = 1.0;
    _color_class[3][1] = 1.0;
    _color_class[3][2] = 1.0;
    _color_class[3][3] = 1.0;
    _radius_min[3] = 1.0;
    _radius_range[3] = 0.5;

    _color_class[4][0] = 1.0;
    _color_class[4][1] = 1.0;
    _color_class[4][2] = 0.5;
    _color_class[4][3] = 1.0;
    _radius_min[4] = 0.9;
    _radius_range[4] = 0.1;

    _color_class[5][0] = 1.0;
    _color_class[5][1] = 0.75;
    _color_class[5][2] = 0.5;
    _color_class[5][3] = 1.0;
    _radius_min[5] = 0.65;
    _radius_range[5] = 0.25;

    _color_class[6][0] = 1.0;
    _color_class[6][1] = 0.625;
    _color_class[6][2] = 0.5;
    _color_class[6][3] = 1.0;
    _radius_min[6] = 0.40;
    _radius_range[6] = 0.25;

    _anomaly_count = 0;
    _c0_count = 0;
    _c1_count = 0;
    _c2_count = 0;
    _c3_count = 0;

    Writer::Instance()->Add( "anomaly(%d)", &_anomaly_count );
    Writer::Instance()->Add( "C0(%d)", &_c0_count );
    Writer::Instance()->Add( "C1(%d)", &_c1_count );
    Writer::Instance()->Add( "C2(%d)", &_c2_count );
    Writer::Instance()->Add( "C3(%d)", &_c3_count );
}

void StarBuilder::SetSizeFactor( double value ) {

    _size_factor = value;
}

bool StarBuilder::Init() {

    _existence = new Generator();
    _existence->SetOctaves( Config::Instance()->galaxy_octaves );

    _feature = new Generator();
    _feature->SetOctaves( 1 );
    _feature->SetFrequency( 8.0 );

    _exist_offset = Config::Instance()->star_exist_offset;
    _exist_min = Config::Instance()->star_exist_min;
    _exist_max = Config::Instance()->star_exist_max;
    _dx_offset = Config::Instance()->star_dx_offset;
    _dy_offset = Config::Instance()->star_dy_offset;
    _d_factor = Config::Instance()->star_d_factor;

    return true;
}

void StarBuilder::ComputeDistribution() {

    double d_value;

    // TODO : Magic number
    d_value = fabs( _feature->GetValue( _position, 91.83 ) );
    if( d_value > 0.2447 ) {
        _class_index = 6;
    } else if( d_value > 0.1167 ) {
        _class_index = 5;
    } else if( d_value > 0.0417 ) {
        _class_index = 4;
    } else if( d_value > 0.0092 ) {
        _c3_count++;
        _class_index = 3;
    } else if( d_value > 0.0017 ) {
        _c2_count++;
        _class_index = 2;
    } else if( d_value > 0.0002 ) {
        _c1_count++;
        _class_index = 1;
    } else if( d_value > 0.00005 ) {
        _c0_count++;
        _class_index = 0;
    } else {
        _anomaly_count++;
        _class_index = -1;
    }
}

void StarBuilder::Reset() {

    _anomaly_count = 0;
    _c0_count = 0;
    _c1_count = 0;
    _c2_count = 0;
    _c3_count = 0;
}

void StarBuilder::Render( Vector2d& position, bool wireframe ) {

    bool exist;

    _position = position;
    _wireframe = wireframe;

    exist = PrepareFeatures();
    if( exist ) {

        ComputeDistribution();

        if( _class_index != -1 ) {
            _color = _color_class[_class_index];
            _radius = CalculateRadius( _class_index );
        } else {
            _color = _color_anomaly;
        }
    
        if( wireframe ) {
            _color = _wire_color;
        } 

        RenderSingleStar();
    }
}

double StarBuilder::CalculateRadius( int index ) {

    double radius_min = _radius_min[index];
    double radius_range = _radius_range[index];
    double radius;

    radius = radius_min + radius_range * fabs(_feature->GetValue( _position, 88.15 ));

    return radius;
}
 
bool StarBuilder::PrepareFeatures() {

    double s_value;
    Vector2d offset;

    s_value = _existence->GetValue( _position, _exist_offset );

    if( s_value > _exist_min && s_value < _exist_max ) {

        offset.x = _existence->GetValue( _position, _dx_offset ) * _d_factor;
        offset.y = _existence->GetValue( _position, _dy_offset ) * _d_factor;

        _x = _position.x + offset.x;
        _y = _position.y + offset.y;

        return true;
    } else {

        return false;
    }
}

void StarBuilder::RenderSingleStar() {

    double alpha;
    int render_mode;

    if( _wireframe ) {
        render_mode = GL_LINE_LOOP;
    } else {
        render_mode = GL_POLYGON;
    }

    glColor4dv( _color );
    glBegin( render_mode );
    for( alpha = 0.0; alpha < 2.0*M_PI; alpha += 0.1*M_PI ) {
        glVertex3d( _x + _size_factor * _radius * cos(alpha), _y + _size_factor * _radius * sin(alpha), 0.0 );
    }
    glEnd();
}


