class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  c : C <- new C;
  main (): Object { 
    { 
      c@A.out();
      c@B.out();
      c@C.out();
      (c<- new D).out();
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

class D inherits C {
  dummyc(): Object {1};
  out(): SELF_TYPE { out_string("D\n") };
};

