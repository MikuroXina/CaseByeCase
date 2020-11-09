#ifndef CASE_HPP
#define CASE_HPP

#include "./cut_info.hpp"
#include "./direction.hpp"
#include "./pos.hpp"

class Case {
  Pos _pos;
  Dir _dir;
  bool _withLock;

public:
  Case(Dir direction, bool withLock);

  CutInfo cutInfo() const;
};

#endif // CASE_HPP
