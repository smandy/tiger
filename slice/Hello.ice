#pragma once

module Demo
{

    sequence<string> StringSeq;
    dictionary<int,string> IntStringMap;

    struct TestObject {
        string hello;
        int xs;

        StringSeq strings;
        IntStringMap ints;
    };

    
interface Hello
{
    idempotent string sayHello(string name);
};

};

