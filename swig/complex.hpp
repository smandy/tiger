#pragma once

#include <iostream>
#include <sstream>

struct  Complex {
  int x;
  int y;

public:
  inline int getX() const { return x; }
  inline int getY() const { return y; }

  explicit Complex( int x_ = 0, int y_ = 0) : x(x_), y(y_) {};

  inline Complex operator+( const Complex &rhs ) {
    return Complex(x + rhs.x, y + rhs.y);
  };

  inline Complex operator-( const Complex &rhs ) {
    return Complex( x - rhs.x, y - rhs.y);
  };

  std::string toString() const;

  friend std::ostream &operator<<( std::ostream &os, const Complex &rhs);

private:
  void append( std::ostream &os) const;
};

std::ostream &operator<<( std::ostream &os, const Complex &rhs);
