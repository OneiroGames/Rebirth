//
// Created by dezlow on 25.09.2021.
//

#include "VertexArray.h"
#include "glad/glad.h"

void VertexArray::Init()
{
    glGenVertexArrays(1, &mVertexArrayID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(mVertexArrayID);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}
