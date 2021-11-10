//
// Created by dezlow on 18.09.2021.
//

#ifndef _MSC_BUILD

#include "VertexBufferLayout.h"
#include "glad/glad.h"

template<>
void VertexBufferLayout::Push<float>(const uint32_t& id, const uint32_t& size, const uint32_t& stride, const uint32_t& pointer)
{
    glEnableVertexAttribArray(id);
    glVertexAttribPointer(id, (int)size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)pointer);
}

#endif