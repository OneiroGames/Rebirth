//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_VERTEXBUFFER_H
#define REBIRTH_VERTEXBUFFER_H


class VertexBuffer
{
public:
    VertexBuffer() {}
    VertexBuffer(unsigned int size, const float* pVertices, bool dynamic_draw = false);
    void Create(unsigned int size, const float* pVertices, bool dynamic_draw = false);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
private:
    unsigned int mVertexBufferID;
};


#endif //REBIRTH_VERTEXBUFFER_H
