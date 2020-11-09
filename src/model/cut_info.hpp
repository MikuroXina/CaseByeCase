#ifndef CUT_INFO_HPP
#define CUT_INFO_HPP

#include "./direction.hpp"

class CutInfo {
  class Case const &original;

  friend class Case;

public:
  bool isCutOn(Dir edge) const;

  CutInfo operator+(CutInfo const &) const;
};

#endif // CUT_INFO_HPP
