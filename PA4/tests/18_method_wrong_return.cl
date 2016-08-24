class B {
  m1 () : Wrong_Type1 { 1 };
  m2 () : Wrong_Type2 { 2 };
  m3 () : SELF_TYPE { self };
};

class A {
  if_error1(): String
      { if myString then myObj.m1() else myObj@B.m2() fi };
  if_error2(a: String, b: String ):String 
      { if myString then myString else myInt fi };
  if_correct(): B { if true then myObj.m3() else myObj.m3() fi };
--  myString(): String { 1 };
  myString : String <- "Hi\n";
  myInt : Int <- 1;
  myObj : B <- new B;
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

