class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  c : A;
  main (): Object { 
    { 
      c <- new A;
      c.out();
      c <- new B;
      c.out();
      c <- new C;
      c.out();
    }
   };
};

class A inherits IO {
  out(): SELF_TYPE { out_string("A\n") };
};

class B inherits A {
  dummy() : Object {1};
  out(): SELF_TYPE { out_string("B\n") };
};

class C inherits B {
  dummyc(): Object {2};
  out(): SELF_TYPE { out_string("C\n") };
};
