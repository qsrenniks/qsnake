/*!
 * \file SnakeTail.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/13
 */

#ifndef SNAKETAIL_H
#define SNAKETAIL_H

#include "Object.h"

class SnakeObject;

class SnakeTail : public Object
{
public:
  virtual void render() override;

  SnakeTail *getNext() const { return m_nextTail; };
  void setNext(SnakeTail *tail) { m_nextTail = tail; };

  void setHead(SnakeObject *head) { m_head = head; };

private:
  SnakeTail *m_nextTail = nullptr;
  SnakeObject *m_head = nullptr;
};

#endif