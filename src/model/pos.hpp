#ifndef POS_HPP
#define POS_HPP

class Pos {
  int _x, _y;

public:
  static Pos Up() { return Pos(0, 1); }
  static Pos Left() { return Pos(-1, 0); }
  static Pos Right() { return Pos(1, 0); }
  static Pos Down() { return Pos(0, -1); }

  Pos(int x, int y) : _x(x), _y(y) {}

  int x() const { return _x; }
  int y() const { return _y; }

  Pos invX() const { return Pos(-_x, _y); }
  Pos invY() const { return Pos(_x, -_y); }
  Pos invXY() const { return Pos(-_x, -_y); }

  Pos operator+(Pos const &pos) const { return Pos(_x + pos._x, _y + pos._y); }
  Pos &operator+=(Pos const &pos) {
    _x += pos._x;
    _y += pos._y;
    return *this;
  }
};

#endif // POS_HPP
