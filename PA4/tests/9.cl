
class A {
  myString : String <- "Hi\n";
  myvoid1(): Bool{isvoid(false )};
  myvoid2(): Bool{isvoid(2)};
  mySelf(self: Object) : Object {1};
  self : SELF_TYPE;
  self(a: String) : Object { self <- 2};
  a(a: String) : String { myString <- 2};
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

