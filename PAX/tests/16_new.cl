class A inherits IO {
  a : Int <- 11;
  b : Int <- 20;
  test (): Object { 
    { 
      out_int(a);
      out_string("***TEST SUCCESS***\n");
    }
   };
};

class Main {
  a : A <- new A;
  main() : Object { { a.test(); } };
};
