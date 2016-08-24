
class A {
  myString(a: String, b: String ):String { myString };
  myString : String <- "Hi\n";
};

class B inherits A {
  a : String ;
  test(): Object { a <- myString };
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

