//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_INDEXBUFFER_H
#define REBIRTH_INDEXBUFFER_H

#include <cstdint>

class IndexBuffer
{
public:
    IndexBuffer() = default;
    void Create(const uint32_t& size, const uint32_t *pIndices);
    IndexBuffer(const uint32_t& size, const uint32_t *pIndices);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;
private:
    uint32_t mIndexBufferID{};
};


#endif //REBIRTH_INDEXBUFFER_H
