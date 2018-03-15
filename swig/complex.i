%module complexmodule

%{

#include "sstream"

#include <string>

#include "complex.hpp"
%}

%include "std_string.i"

%include "stl.i"

%include "complex.hpp"

%feature("python:slot", "tp_repr", functype="reprfunc") Complex::toString;

%rename(__repr__)  Complex::toString() const;
%rename(__str__)  Complex::toString() const;

%extend Complex {
  std::string __repr__()
    {  return self->toString(); }
 }
