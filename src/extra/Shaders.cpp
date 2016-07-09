
#include "Shaders.h"

#define STATIC_OBJ(type, name) static type* name = NULL; \
    if (name == NULL) { \
        name = new type(); \
    }

#define STATIC_SHADER(type, source) { \
    vs->SetSource(source); \
 \
}

VertexShader& VertexShaders::NoTransform()
{
    STATIC_OBJ(VertexShader, vs);
    vs->SetSource(<#std::string str#>);
}

FragmentShader& FragmentShaders::RedColor()
{
    
}