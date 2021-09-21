//
// Created by dezlow on 18.09.2021.
//

#include "VertexBufferLayout.h"

template<>
void VertexBufferLayout::Push<float>(unsigned int id, unsigned int size, unsigned int stride, unsigned int pointer)
{
    glEnableVertexAttribArray(id);
    glVertexAttribPointer(id, (int)size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)pointer);
}