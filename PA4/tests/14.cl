
class A {
--  myString : String <- "Hi\n";
  myString(a: String, b: String ):String { myString };
--  myString(): String { 1 };
  myString : String <- "Hi\n";
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";
  myIO : IO;
  main(): SELF_TYPE {
    out_string("Hello World!\n")
  };
  testDispatchSelf(a : IO): String {"Hi"};
  test():Object { testDispatchSelf(self) };
};

