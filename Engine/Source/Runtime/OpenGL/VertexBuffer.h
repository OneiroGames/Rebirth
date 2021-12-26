//
// Created by dezlow on 18.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef REBIRTH_VERTEXBUFFER_H
#define REBIRTH_VERTEXBUFFER_H

#include <cstdint>
#include "OpenGL/ogl4.5.hpp"

class VertexBuffer
{
public:
    VertexBuffer() = default;
    VertexBuffer(uint32_t size, const float* pVertices, bool dynamic_draw = false);
    void Create(uint32_t size, const float* pVertices, bool dynamic_draw = false);
    ~VertexBuffer();

    void Bind() const;
    void UnBind();

    template<class T>
    void PushLayout(const uint32_t id, const uint32_t size, const uint32_t stride, const uint32_t pointer) {}

    template<>
    void PushLayout<float>(const uint32_t id, const uint32_t size, const uint32_t stride, const uint32_t pointer)
    {
        gl::EnableVertexAttribArray(id);
        gl::VertexAttribPointer(id, (int)size, gl::FLOAT, gl::FALSE_, stride * sizeof(float), (void*)pointer);
    }
private:
    unsigned int mVertexBufferID{};
};


#endif //REBIRTH_VERTEXBUFFER_H
