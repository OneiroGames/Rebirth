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
};


#endif //REBIRTH_VERTEXBUFFERLAYOUT_H
