//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_VERTEXBUFFERLAYOUT_H
#define REBIRTH_VERTEXBUFFERLAYOUT_H

#include <cstdint>

class VertexBufferLayout
{
public:
    template<class T>
    static void Push(const uint32_t& id, const uint32_t& size, const uint32_t& stride, const uint32_t& pointer) {}

#ifdef _MSC_BUILD
    template<>
    static void Push<float>(const uint32_t& id, const uint32_t& size, const uint32_t& stride, const uint32_t& pointer)
    {
        glEnableVertexAttribArray(id);
        glVertexAttribPointer(id, (int)size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)pointer);
    }
#endif
};


#endif //REBIRTH_VERTEXBUFFERLAYOUT_H
