#include "shader_cache.h"
#include "OpenGL_Internal.h"

namespace kawaii {

void ShaderCache::LoadDefaultShaders() {
    shared_ptr<GLProgram> p;

    p.reset(new GLProgram);
    p->LoadShaderFiles("position_ucolor.vert", "position_ucolor.frag");
    p->AddAttribute(kVertexAttrib_Position);
    CHECK_GL_ERROR_DEBUG();
    shaders_[kShader_Position_uColor] = p;

    p.reset(new GLProgram);
    p->LoadShaderFiles("position_color.vert", "position_color.frag");
    p->AddAttribute(kVertexAttrib_Position);
    p->AddAttribute(kVertexAttrib_Color);
    CHECK_GL_ERROR_DEBUG();
    shaders_[kShader_PositionColor] = p;

    p.reset(new GLProgram);
    p->LoadShaderFiles("position_texture.vert", "position_texture.frag");
    p->AddAttribute(kVertexAttrib_Position);
    p->AddAttribute(kVertexAttrib_TexCoords);
    CHECK_GL_ERROR_DEBUG();
    shaders_[kShader_PositionTexture] = p;

    p.reset(new GLProgram);;
    p->LoadShaderFiles("position_texture_color.vert", "position_texture_color.frag");
    p->AddAttribute(kVertexAttrib_Position);
    p->AddAttribute(kVertexAttrib_Color);
    p->AddAttribute(kVertexAttrib_TexCoords);
    CHECK_GL_ERROR_DEBUG();
    shaders_[kShader_PositionTextureColor] = p;
}

}
