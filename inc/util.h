#ifndef UTIL_H
#define UTIL_H

class Util
{
    private:
        static Util* _instance;
        Util();

    public:
        static Util* Instance();
        ~Util();

    public:
        double RandomValue(double min, double max);
};

#endif

