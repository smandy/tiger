#pragma once

module argo {
  interface Foo {
    ["amd"] string doit();

    ["amd"] string doitAgain();
  };
};
