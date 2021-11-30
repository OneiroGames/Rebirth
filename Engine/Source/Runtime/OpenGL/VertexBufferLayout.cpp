//
// Created by dezlow on 18.09.2021.
//

#include "VertexBufferLayout.h"
#include "OpenGL/ogl4.5.hpp"

template<>
void VertexBufferLayout::Push<float>(const uint32_t id, const uint32_t size, const uint32_t stride, const uint32_t pointer)
{
    gl::EnableVertexAttribArray(id);
    gl::VertexAttribPointer(id, (int)size, gl::FLOAT, gl::FALSE_, stride * sizeof(float), (void*)pointer);
}