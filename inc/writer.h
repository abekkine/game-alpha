#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>

#include <vector.h>
#include <font.h>

#define MSG_TEXT_ONLY 'T'
#define MSG_INTEGER 'I'
#define MSG_DOUBLE 'D'
#define BUFFER_SIZE 256

class Writer
{
    private:
        // Types and members.
        typedef struct {
            int x;
            int y;
            char type;
            std::string format;
            void * value;
        } MessageDisplayType;

    private:
        static Writer* _instance;
        Writer();

    public:
        static Writer* Instance();
        ~Writer();
        bool Init();
        void SetColor( double* color );
        void UpdateOrigin( Vector2i& p );
        void Render();
        void Add( std::string text );
        void Add( std::string format, int* value );
        void Add( std::string format, double* value );
        
    private:
        // Methods.
        void Defaults();

    private:
        // Members.
        Vector2i _origin;
        Vector2i _cursor;
        char _text_buffer[BUFFER_SIZE];
        Font* _font;
        int _font_height;
        std::vector< MessageDisplayType* > _message_list;
};

#endif
