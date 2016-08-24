
(*
class SELF_TYPE {
--  myString : String <- "Hi\n";
  myString(a: String, b: String ):String { myString };
--  myString(): String { 1 };
  myString : String <- "Hi\n";
};

class A inherits SELF_TYPE {
};
*)

class B {
  x : SELF_TYPE;
--  error1(x : SELF_TYPE ) : Object {1};
  right(x : Object ) : SELF_TYPE { self };
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

