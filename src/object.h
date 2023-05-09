#pragma once

#include "defines.h"

#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"

class Object
{
public:
    Mesh *mesh = NULL;
    Texture *texture = NULL;
    Shader *shader = NULL;
    Animation *anim = NULL;
    // Constructor
    Object();
    // Destructor
    ~Object();
};