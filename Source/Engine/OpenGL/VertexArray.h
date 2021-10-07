//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_VERTEXARRAY_H
#define REBIRTH_VERTEXARRAY_H


#include <cstdint>

class VertexArray
{
public:
    VertexArray() = default;
    ~VertexArray();

    void Init();

    void Bind() const;
    void UnBind() const;
private:
    uint32_t mVertexArrayID{};
};


#endif //REBIRTH_VERTEXARRAY_H
