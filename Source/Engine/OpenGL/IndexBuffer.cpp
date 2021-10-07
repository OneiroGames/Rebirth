//
// Created by dezlow on 25.09.2021.
//

#include "IndexBuffer.h"
#include "glad/glad.h"

IndexBuffer::IndexBuffer(const uint32_t& size, const uint32_t *pIndices)
{
    glGenBuffers(1, &mIndexBufferID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pIndices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &mIndexBufferID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Create(const uint32_t& size, const uint32_t* pIndices)
{
    glGenBuffers(1, &mIndexBufferID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pIndices, GL_STATIC_DRAW);
}
