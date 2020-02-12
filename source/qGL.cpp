/*!
 * \file borealisGL.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2019/12/18
 */

#include "pch.h"
#include "qGL.h"

void setViewport(unsigned xPos, unsigned yPos, unsigned width, unsigned height)
{
  glViewport(xPos, yPos, width, height);
}

void createBuffer(unsigned &buffer)
{
  glCreateBuffers(1, &buffer);
}

void deleteBuffer(unsigned &buffer)
{
  glDeleteBuffers(1, &buffer);
}

void bindBuffer(GLenum target, const unsigned &buffer)
{
  glBindBuffer(target, buffer);
}

void setBufferData(const unsigned &buffer, unsigned sizeInBytes, const void *data, GLenum drawHint)
{
  glNamedBufferData(buffer, sizeInBytes, data, drawHint);
}

void createVertexArray(unsigned &arrayObject)
{
  glCreateVertexArrays(1, &arrayObject);
}

void deleteVertexArray(unsigned &buffer)
{
  glDeleteVertexArrays(1, &buffer);
}

void bindVertexArray(const unsigned &vertexArray)
{
  glBindVertexArray(vertexArray);
}

void enableVertexAttribArray(unsigned index)
{
  glEnableVertexAttribArray(index);
}

void setVertexAttribPointer(unsigned index, unsigned numberOfComponents, GLenum componentType, bool normalized, unsigned vertexStride, unsigned offsetInStride)
{
  glVertexAttribPointer(index, numberOfComponents, componentType, normalized, vertexStride, (void *)uintptr_t(offsetInStride));
}

void drawElements(GLenum drawMode, unsigned indicesCount, GLenum indicesType, const void *indicesOffsetPointer)
{
  glDrawElements(drawMode, indicesCount, indicesType, indicesOffsetPointer);
}

void bindFramebuffer(GLenum target, unsigned framebuffer)
{
  glBindFramebuffer(target, framebuffer);
}

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
    GLenum filter)
{
  glBlitNamedFramebuffer(readBuffer, writeBuffer, readX0, readY0, readX1, readY1, writeX0, writeY0, writeX1, writeY1, mask, filter);
}

void enable(GLenum property)
{
  glEnable(property);
}

void disable(GLenum property)
{
  glDisable(property);
}

void bindBufferBase(GLenum target, unsigned index, unsigned buffer)
{
  glBindBufferBase(target, index, buffer);
}

void setBufferSubData(const unsigned &target, unsigned offset, unsigned sizeInBytes, const void *data)
{
  glNamedBufferSubData(target, offset, sizeInBytes, data);
}

void drawArrays(GLenum drawMode, unsigned startingIndex, unsigned count)
{
  glDrawArrays(drawMode, startingIndex, count);
}

void primitiveRestartIndex(unsigned restartIndex)
{
  glPrimitiveRestartIndex(restartIndex);
}

void setVertexAttribIntPointer(unsigned index, unsigned numberOfComponents, GLenum componentType, unsigned vertexStride, unsigned offsetInStride)
{
  glVertexAttribIPointer(index, numberOfComponents, componentType, vertexStride, (void *)uintptr_t(offsetInStride));
}

void setVertexInstanceDivisor(unsigned index, unsigned divisor)
{
  glVertexAttribDivisor(index, divisor);
}