#ifndef INCLUDED_RENDER_MOVE_RECOGNIZER_H
#define INCLUDED_RENDER_MOVE_RECOGNIZER_H
#include "platform/i_platform.h"
#include "render/recognizer.h"
namespace render {

class MoveRecognizer: public Recognizer
{
public:
    MoveRecognizer( int32_t Id );
    virtual bool Recognize( Actor const& ) const;
};

} // namespace render

#endif //INCLUDED_RENDER_MOVE_RECOGNIZER_H
