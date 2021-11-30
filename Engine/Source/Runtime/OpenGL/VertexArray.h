//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_VERTEXARRAY_H
#define REBIRTH_VERTEXARRAY_H


#include <cstdint>
#include "OpenGL/ogl4.5.hpp"

class VertexArray
{
public:
    VertexArray() = default;
    ~VertexArray() { gl::DeleteVertexArrays(1, &mVertexArrayID); }

    void Init() { gl::GenVertexArrays(1, &mVertexArrayID); }

    void Bind() const { gl::BindVertexArray(mVertexArrayID); }
    void UnBind() { gl::BindVertexArray(0); }
private:
    uint32_t mVertexArrayID{};
};


#endif //REBIRTH_VERTEXARRAY_H
