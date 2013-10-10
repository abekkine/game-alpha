#include <stdlib.h>
#include <string.h>

#include <config.h>

Config* Config::_instance = 0;

Config* Config::Instance()
{
    if( _instance == 0 )
    {
        _instance = new Config();
    }

    return _instance;
}

Config::Config()
{
    puts("Config::Config()");

    Init();
    Defaults();
}

Config::~Config()
{
    puts("Config::~Config()");
}

bool Config::Read( std::string configFile )
{
    bool result = false;

    _configFile = configFile;

    if( config_read_file( &_config, _configFile.c_str() ) )
    {
        ReadDebug();
        ReadApplication();
        ReadBackground();
        ReadLayer();
        ReadForeground();
        ReadDisplay();
        ReadEvent();
        ReadPanel();
        ReadFont();

        config_destroy( &_config );

        result = true;
    }
    else
    {
        config_error_t error_type;
        error_type = config_error_type( &_config );

        if( error_type == CONFIG_ERR_FILE_IO )
        {
            fprintf( stderr, "\nConfig File Error.\n\n" );
        }
        else
        {
            fprintf( stderr, "%s:%d - %s\n",
                config_error_file( &_config ),
                config_error_line( &_config ),
                config_error_text( &_config ) );
        }

        config_destroy( &_config );

        exit( 1 );
    }

    return result;
}

void Config::Init()
{
    config_init( &_config );
}

void Config::Defaults()
{
// TODO : [COMMENT] Explain default values by comments. Also, constants/defines can be used here.

    // Debug
    debug = 0;

    // Application
    application_frequency = 20;
    application_timestep = 1.0;

    // Background
    background_tile_size = 0.1;
    background_tile_delta = 0.01;
    
    // Background Offsets
    background_offset_delta = 0.01;
    background_red_offset = 0.0;
    background_green_offset = 0.0;
    background_blue_offset = 0.0;

    // Display Screen
    screen_width = 512;
    screen_height = 512;

    // Display World
    world_width = 1.0;
    world_height = 1.0;

    // Display Clear Color
    clear_color_red = 0.0;
    clear_color_green = 0.0;
    clear_color_blue = 0.0;

    // Zoom and Pan
    layer_zoom_factor = 0.002;
    layer_pan_factor = 1.0;
    foreground_zoom_factor = 0.002;
    foreground_pan_factor = 1.0;
    bg_zoom_factor = 0.002;
    bg_pan_factor = 1.0;

    // Octave counts
    bg_octaves = 4;

    // Event
    // Speed factor
    speed_factor_min = 1;
    speed_factor_max = 2;
    // Zoom limits
    zoom_limit_min = -250;
    zoom_limit_max = 1250;
    // Wheel zoom step value
    wheel_step = 10;

    // Panel
    // Frame width
    frame_width = 1.0;
    // Frame color
    frame_color_red = 1.0;
    frame_color_green = 1.0;
    frame_color_blue = 1.0;
    frame_color_alpha = 1.0;
    // Panel color
    panel_color_red = 0.0;
    panel_color_green = 0.0;
    panel_color_blue = 0.5;
    panel_color_alpha = 0.5;
    // Font color
    font_color_red = 1.0;
    font_color_green = 1.0;
    font_color_blue = 1.0;
    font_color_alpha = 1.0;
    // Panel margin
    panel_margin = 10;
    panel_percent = 20;

    // Font
    font_name = "freemono.ttf";
    font_folder = "../fonts/";
    font_size = 12;
}

void Config::ReadDebug()
{
    config_lookup_int( &_config, "config.debug", &debug );
}

void Config::ReadApplication()
{
    _setting = config_lookup( &_config, "config.application" );
    if( _setting != 0 )
    {
        config_setting_lookup_float( _setting, "frequency", &application_frequency );
        config_setting_lookup_float( _setting, "timestep", &application_timestep );
    }
}

void Config::ReadLayer() {

    _setting = config_lookup( &_config, "config.layer" );
    if( _setting != 0 ) {
        
        config_setting_lookup_float( _setting, "zoom_factor", &layer_zoom_factor );
        config_setting_lookup_float( _setting, "pan_factor", &layer_pan_factor );
    }
}

void Config::ReadFont() {

    _setting = config_lookup( &_config, "config.font" );
    if( _setting != 0 ) {
        const char* name;
        const char* folder;

        config_setting_lookup_string( _setting, "name", &name );
        font_name = std::string( name );
        config_setting_lookup_string( _setting, "folder", &folder );
        font_folder = std::string( folder );
        config_setting_lookup_int( _setting, "size", &font_size );
    }
}

void Config::ReadForeground() {

    _setting = config_lookup( &_config, "config.foreground" );
    if( _setting != 0 ) {

        config_setting_lookup_float( _setting, "zoom_factor", &foreground_zoom_factor );
        config_setting_lookup_float( _setting, "pan_factor", &foreground_pan_factor );
    }
}

void Config::ReadEvent() {

    _setting = config_lookup( &_config, "config.event" );
    if( _setting != 0 ) {
        
        config_setting_lookup_int( _setting, "speed_factor_min", &speed_factor_min );
        config_setting_lookup_int( _setting, "speed_factor_max", &speed_factor_max );
        config_setting_lookup_int( _setting, "zoom_limit_min", &zoom_limit_min );
        config_setting_lookup_int( _setting, "zoom_limit_max", &zoom_limit_max );
        config_setting_lookup_int( _setting, "wheel_step", &wheel_step );
    }
}

void Config::ReadPanel() {

    _setting = config_lookup( &_config, "config.panel" );
    if( _setting != 0 ) {

        config_setting_lookup_float( _setting, "frame_width", &frame_width );
        config_setting_lookup_int( _setting, "margin", &panel_margin );
        config_setting_lookup_int( _setting, "percent", &panel_percent );

        ReadPanelColor();
        ReadPanelFontColor();
        ReadPanelFrameColor();
    }
}

void Config::ReadPanelColor() {

    _setting = config_lookup( &_config, "config.panel.bg_color" );
    if( _setting != 0 ) {
        config_setting_lookup_float( _setting, "red", &panel_color_red );
        config_setting_lookup_float( _setting, "green", &panel_color_green );
        config_setting_lookup_float( _setting, "blue", &panel_color_blue );
        config_setting_lookup_float( _setting, "alpha", &panel_color_alpha );
    }
}

void Config::ReadPanelFontColor() {

    _setting = config_lookup( &_config, "config.panel.font_color" );
    if( _setting != 0 ) {
        config_setting_lookup_float( _setting, "red", &font_color_red );
        config_setting_lookup_float( _setting, "green", &font_color_green );
        config_setting_lookup_float( _setting, "blue", &font_color_blue );
        config_setting_lookup_float( _setting, "alpha", &font_color_alpha );
    } 
}

void Config::ReadPanelFrameColor() {

    _setting = config_lookup( &_config, "config.panel.frame_color" );
    if( _setting != 0 ) {
        config_setting_lookup_float( _setting, "red", &frame_color_red );
        config_setting_lookup_float( _setting, "green", &frame_color_green );
        config_setting_lookup_float( _setting, "blue", &frame_color_blue );
        config_setting_lookup_float( _setting, "alpha", &frame_color_alpha );
    }
}

void Config::ReadBackground()
{
    _setting = config_lookup( &_config, "config.background" );
    if( _setting != 0 )
    {
        config_setting_lookup_float( _setting, "size", &background_tile_size );
        config_setting_lookup_float( _setting, "size_delta", &background_tile_delta );

        config_setting_lookup_float( _setting, "zoom_factor", &bg_zoom_factor );
        config_setting_lookup_float( _setting, "pan_factor", &bg_pan_factor );
        config_setting_lookup_int( _setting, "octaves", &bg_octaves );

        ReadBackgroundOffsets();
    }
}

void Config::ReadBackgroundOffsets()
{
    _setting = config_lookup( &_config, "config.background.offset" );
    if( _setting != 0 )
    {
        config_setting_lookup_float( _setting, "delta", &background_offset_delta );
        config_setting_lookup_float( _setting, "red", &background_red_offset );
        config_setting_lookup_float( _setting, "green", &background_green_offset );
        config_setting_lookup_float( _setting, "blue", &background_blue_offset );
    }
}

void Config::ReadDisplay()
{
    _setting = config_lookup( &_config, "config.display" );
    if( _setting != 0 )
    {
        ReadDisplayScreen();
        ReadDisplayWorld();
        ReadDisplayColor();
    }
}

void Config::ReadDisplayScreen()
{
    _setting = config_lookup( &_config, "config.display.screen" );
    if( _setting != 0 )
    {
        config_setting_lookup_int( _setting, "width", &screen_width );
        config_setting_lookup_int( _setting, "height", &screen_height );
    }
}

void Config::ReadDisplayWorld()
{
    _setting = config_lookup( &_config, "config.display.world" );
    if( _setting != 0 )
    {
        config_setting_lookup_float( _setting, "width", &world_width );
        config_setting_lookup_float( _setting, "height", &world_height );
    }
}

void Config::ReadDisplayColor()
{
    _setting = config_lookup( &_config, "config.display.clear" );
    if( _setting != 0 )
    {
        config_setting_lookup_float( _setting, "red", &clear_color_red );
        config_setting_lookup_float( _setting, "green", &clear_color_green );
        config_setting_lookup_float( _setting, "blue", &clear_color_blue );
    }
}
