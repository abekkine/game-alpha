#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <libconfig.h>

// TODO : [DOCUMENT] Use doxygen documentation in all headers.
//! @brief Configuration class to handle config files.
class Config
{
    private:
        static Config* _instance;
        Config();

    public:
        //! @brief Returns instance of configuration class.
        static Config* Instance();
        //! @brief Desctructor.
        ~Config();
        //! @brief Read and parse contents of the given config file.
        //! TBD :
        //! @param[in] configFile String configuration file name.
        bool Read( std::string configFile );

    private:
        // Methods
        void Defaults();
        void Init();
        void ReadDebug();
        void ReadApplication();
        void ReadBackground();
        void ReadBackgroundOffsets();
        void ReadLayer();
        void ReadForeground();
        void ReadPlayer();
        void ReadBullet();
        void ReadEnemy();
        void ReadDisplay();
        void ReadEvent();
        void ReadFont();
        void ReadPanel();
        void ReadPanelColor();
        void ReadPanelFrameColor();
        void ReadPanelFontColor();
        void ReadDisplayScreen();
        void ReadDisplayWorld();
        void ReadDisplayColor();

    private:
        // Members
        std::string _configFile;
        config_t _config;
        config_setting_t* _setting;

    public:
        // Configuration items.
        // Debug settings.
        int debug;
        // Application settings.
        //! Application running frequency.
        double application_frequency;
        //! Execution step length of application.
        double application_timestep;
        // Background settings.
        //! Unit size for background triangular mesh.
        double background_tile_size;
        //! Background tile increment/decrement step size.
        double background_tile_delta;
        //! Background color red offset value for perlin noise generation.
        double background_red_offset;
        //! Background color green offset value for perlin noise generation.
        double background_green_offset;
        //! Background color blue offset value for perlin noise generation.
        double background_blue_offset;
        //! Increment/Decrement delta value for color offsets.
        double background_offset_delta;

        // Display settings.
        //! Display screen width.
        int screen_width;
        //! Display screen height.
        int screen_height;
        //! Width of the world projected to screen.
        double world_width;
        //! Height of the world projected to screen.
        double world_height;
        //! Ground level in world.
        double ground_level;
        //! Clear color red component.
        double clear_color_red;
        //! Clear color green component.
        double clear_color_green;
        //! Clear color blue component.
        double clear_color_blue;

        //! Player Settings.
        double player_speed;
        double player_bullet_speed;

        //! Enemy settings.
        double enemy_width;
        double enemy_height;
        double enemy_reload_time;
        double enemy_bullet_speed;
        double enemy_c1;
        double enemy_c2;
        double enemy_c3;
        double enemy_c4;

        //! Bullet settings.
        double max_bullet_life;
        double bullet_decay_rate;
        double bullet_width;
        double bullet_height;
        double bullet_damage;

        //! Zoom and pan parameters.
        double layer_zoom_factor;
        double layer_pan_factor;
        double foreground_zoom_factor;
        double foreground_pan_factor;
        double bg_zoom_factor;
        double bg_pan_factor;

        //! Octave counts.
        int bg_octaves;

        //! Event parameters
        int speed_factor_min;
        int speed_factor_max;
        int zoom_limit_min;
        int zoom_limit_max;
        int wheel_step;

        //! Panel parameters
        double frame_width;

        double frame_color_red;
        double frame_color_green;
        double frame_color_blue;
        double frame_color_alpha;

        double panel_color_red;
        double panel_color_green;
        double panel_color_blue;
        double panel_color_alpha;

        double font_color_red;
        double font_color_green;
        double font_color_blue;
        double font_color_alpha;        

        int panel_margin;
        int panel_percent;

        //! Font parameters
        std::string font_name;
        std::string font_folder;
        int font_size;
};

#endif

