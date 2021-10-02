//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_INDEXBUFFER_H
#define REBIRTH_INDEXBUFFER_H

class IndexBuffer
{
public:
    IndexBuffer() {}
    void Create(unsigned int size, const unsigned int *pIndices);
    IndexBuffer(unsigned int size, const unsigned int *pIndices);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;
private:
    unsigned int mIndexBufferID;
};


#endif //REBIRTH_INDEXBUFFER_H
