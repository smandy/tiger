#pragma once

module argo {
  interface Foo {
    ["amd"] string doit();

    ["amd"] string doitAgain();

    ["amd", "ami"] int add(int a, int b);
  };
};
