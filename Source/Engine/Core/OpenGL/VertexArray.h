//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_VERTEXARRAY_H
#define REBIRTH_VERTEXARRAY_H


#include "glad/glad.h"

class VertexArray
{
public:
    VertexArray() : mVertexArrayID(0) { glGenVertexArrays(1, &mVertexArrayID); }
    ~VertexArray() { glDeleteVertexArrays(1, &mVertexArrayID); }

    void Bind() const { glBindVertexArray(mVertexArrayID); }
    void UnBind() const { glBindVertexArray(0); }
private:
    unsigned int mVertexArrayID;
};


#endif //REBIRTH_VERTEXARRAY_H
