
class A {
  myString : String <- "Hi\n";
  myString1 : String <- "Hi String1\n";
  myString1 : String <- "Hi String1 Overide\n";
  myWrong : Wrongtype;
  myWrong : Wrongtype1;
  b(a: String, b: Int ) : Object { myString <- a };
  self : SELF_TYPE;
};

class B inherits A {
  myString : String <- "Child's Hi\n";
  myString1 : String <- "Hi String1 inherit overide\n";
  myString1 : String <- "Hi String1 inherit second time\n";
  myWrong : String <- "Could overide wrong type\n";
  b() : Int {1};
  self : SELF_TYPE;
};

class C inherits A {
  b(a: Int) : Object {1};
  b() : Int {1};
  b(a: String, b: Int ) : Object {1};
  b(a: String, b: Int ) : Object {2}; 
};

class D inherits A {
  b(a: Int, b: String) : Object {1};
};


Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

