//
// Created by dezlow on 18.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const uint32_t size, const float* pVertices, bool dynamic_draw) : mVertexBufferID(0)
{
    gl::GenBuffers(1, &mVertexBufferID);
    Bind();

    gl::BufferData(gl::ARRAY_BUFFER, size, pVertices, dynamic_draw ? gl::DYNAMIC_DRAW : gl::STATIC_DRAW);
}
void VertexBuffer::Create(const uint32_t size, const float* pVertices, bool dynamic_draw)
{
    gl::GenBuffers(1, &mVertexBufferID);
    Bind();

    gl::BufferData(gl::ARRAY_BUFFER, size, pVertices, dynamic_draw ? gl::DYNAMIC_DRAW : gl::STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
    gl::DeleteBuffers(1, &mVertexBufferID);
}

void VertexBuffer::Bind() const
{
    gl::BindBuffer(gl::ARRAY_BUFFER, mVertexBufferID);
}

void VertexBuffer::UnBind()
{
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
}
