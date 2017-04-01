/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/

#include "Shaders.h"
#include <stdio.h>

#define STATIC_OBJ(type, name) static type* name = NULL;    \
    if (name == NULL) {                                     \
        name = new type();                                  \
    }

#define STATIC_SHADER(type, source) {                                       \
    STATIC_OBJ(type, obj);                                                  \
    obj->SetSource(source);                                                 \
    if (!obj->Compile()) {                                                  \
        std::string log = obj->GetInfoLog();                                \
        printf("%s failed to compile: %s\n", __FUNCTION__, log.c_str());    \
    }                                                                       \
    return *obj;                                                            \
}

VertexShader& VertexShaders::NoTransform()
{
    STATIC_SHADER(VertexShader, GLSL150(
        in vec3 a_vPosition;
        
        void main(){
            gl_Position = vec4(a_vPosition, 1.0);
        }
    ));
}

FragmentShader& FragmentShaders::RedColor()
{
    STATIC_SHADER(FragmentShader, GLSL150(
        out vec4 f_vColor;

        void main() {
            f_vColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    ));
}
