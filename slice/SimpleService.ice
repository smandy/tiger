#pragma once

module argo {
  
  interface SimpleService { 
    string sayHello(string person);

    int add(int x,int y);

    int multiply(int x,int y);
  };
};
