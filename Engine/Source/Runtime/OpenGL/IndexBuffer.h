//
// Created by Dezlow on 18.09.2021.
// Copyright (c) 2021 Oneiro Games. All rights reserved.
//

#pragma once

#ifndef REBIRTH_INDEXBUFFER_H
#define REBIRTH_INDEXBUFFER_H

#include <cstdint>
#include "OpenGL/ogl4.5.hpp"

class IndexBuffer
{
public:
    IndexBuffer() = default;
    ~IndexBuffer() { gl::DeleteBuffers(1, &mIndexBufferID); }

    void Create(const uint32_t size, const uint32_t *pIndices)
    {
        gl::GenBuffers(1, &mIndexBufferID);
        Bind();
        gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, size, pIndices, gl::STATIC_DRAW);
    }

    void Bind() const { gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, mIndexBufferID); }
    void UnBind() const { gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0); }
private:
    uint32_t mIndexBufferID{};
};


#endif //REBIRTH_INDEXBUFFER_H
