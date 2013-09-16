#ifndef STARBUILDER_H
#define STARBUILDER_H

#include <vector.h>
#include <definitions.h>
#include <generator.h>

class StarBuilder {

    private:
        const double WIRE_COLOR;

    public:
        StarBuilder();
        ~StarBuilder();
        bool Init();
        void Reset();
        void SetSizeFactor( double value );
        void Render( Vector2d& position, bool wireframe );

    private:
        void Defaults();
        bool PrepareFeatures();
        void RenderSingleStar();
        void ComputeDistribution();
        double CalculateRadius( int index );

    private:
        Generator* _existence;
        Generator* _feature;
        Vector2d _position;

        double _size_factor;
        double _exist_offset;
        double _exist_min;
        double _exist_max;
        double _dx_offset;
        double _dy_offset;
        double _d_factor;

        // Raw display position and color.
        double _x;
        double _y;
        double _radius;
        double* _color;
        double _wire_color[4];
        double _color_class[7][4];
        double _color_anomaly[4];
        double _radius_min[7];
        double _radius_range[7];
        int _class_index;
        bool _wireframe;

        // Distribution indicators.
        int _anomaly_count;
        int _c0_count;
        int _c1_count;
        int _c2_count;
        int _c3_count;
};

#endif
