//
// Created by dezlow on 18.09.2021.
//

#ifndef REBIRTH_VERTEXARRAY_H
#define REBIRTH_VERTEXARRAY_H


class VertexArray
{
public:
    VertexArray() {}
    ~VertexArray();

    void Init();

    void Bind() const;
    void UnBind() const;
private:
    unsigned int mVertexArrayID;
};


#endif //REBIRTH_VERTEXARRAY_H
