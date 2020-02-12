/*!
 * \file qGL.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#ifndef QGL_H
#define QGL_H

void setViewport(unsigned xPos, unsigned yPos, unsigned width, unsigned height);
void createBuffer(unsigned &buffer);
void deleteBuffer(unsigned &buffer);
void bindBuffer(GLenum target, const unsigned &buffer);
void setBufferData(const unsigned& target, unsigned sizeInBytes, const void *data, GLenum drawHint);
void setBufferSubData(const unsigned& target, unsigned offset, unsigned sizeInBytes, const void* data);

void createVertexArray(unsigned &arrayObject);
void deleteVertexArray(unsigned &buffer);
void bindVertexArray(const unsigned &vertexArray);

void enableVertexAttribArray(unsigned index);
void setVertexAttribPointer(unsigned index, unsigned numberOfComponents, GLenum componentType, bool normalized, unsigned vertexStride, unsigned offsetInStride);
void setVertexAttribIntPointer(unsigned index, unsigned numberOfComponents, GLenum componentType, unsigned vertexStride, unsigned offsetInStride);
void setVertexInstanceDivisor(unsigned index, unsigned divisor);

void drawArrays(GLenum drawMode, unsigned startingIndex, unsigned count);
void drawElements(GLenum drawMode, unsigned indicesCount, GLenum indicesType, const void *indicesOffsetPointer);

void bindFramebuffer(GLenum target, unsigned framebuffer);
void blitFramebuffer(
    unsigned readBuffer,
    unsigned writeBuffer,
    unsigned readX0,
    unsigned readY0, 
    unsigned readX1,
    unsigned readY1,
    unsigned writeX0,
    unsigned writeY0,
    unsigned writeX1,
    unsigned writeY1,
    GLbitfield mask,
    GLenum filter);

void enable(GLenum property);
void disable(GLenum property);

void bindBufferBase(GLenum target, unsigned index, unsigned buffer);

void primitiveRestartIndex(unsigned restartIndex);

#endif