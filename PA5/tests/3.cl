
class A {
--  myString : String <- "Hi\n";
  myString(a: String, b: String ):String { myString };
--  myString(): String { 1 };
  myString : String <- "Hi\n";
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

