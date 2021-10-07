//
// Created by dezlow on 18.09.2021.
//

#include "VertexBuffer.h"
#include "glad/glad.h"

VertexBuffer::VertexBuffer(const uint32_t& size, const float* pVertices, bool dynamic_draw) : mVertexBufferID(0)
{
    glGenBuffers(1, &mVertexBufferID);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, pVertices, dynamic_draw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
void VertexBuffer::Create(const uint32_t& size, const float* pVertices, bool dynamic_draw)
{
    glGenBuffers(1, &mVertexBufferID);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, pVertices, dynamic_draw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
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
