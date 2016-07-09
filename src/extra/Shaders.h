#pragma once

#include "core/Shader.h"

class VertexShaders
{
public:
    /// Copy position attribute without any transformation
    static VertexShader& NoTransform();
};

class PixelShaders
{
public:
    /// Output red pixel colors
    static FragmentShader& RedColor();
};