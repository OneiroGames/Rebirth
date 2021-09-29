//
// Created by dezlow on 18.09.2021.
//

#include "VertexBuffer.h"
#include "glad/glad.h"

VertexBuffer::VertexBuffer(unsigned int size, const float* pVertices) : mVertexBufferID(0)
{
    glGenBuffers(1, &mVertexBufferID);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, pVertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &mVertexBufferID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}