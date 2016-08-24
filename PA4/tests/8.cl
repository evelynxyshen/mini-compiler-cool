
class A {
--  myString : String <- "Hi\n";
--  myString(a: String, b: String ):String { myString };
--  myString(): String { 1 };
--  myString : String <- "Hi\n";
--  myLoop1(): Object {while true loop 1 pool};
--  myLoop2(): Object {while 1 loop 1 pool};
  myvoid1(): Bool{isvoid(false )};
  myvoid2(): Bool{isvoid(2)};
  self : SELF_TYPE;
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

