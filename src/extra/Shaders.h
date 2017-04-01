/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include "core/Shader.h"

/// Library of common vertex shaders
class VertexShaders
{
public:
    /// Copy position attribute without any transformation
    static VertexShader& NoTransform();
};

/// Library of common fragment shaders
class FragmentShaders
{
public:
    /// Output red pixel colors
    static FragmentShader& RedColor();
};
