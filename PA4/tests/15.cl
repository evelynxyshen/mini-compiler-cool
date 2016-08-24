
class A {
  myString(a: String, b: Int ):String { myString };
  myString : String <- "Hi\n";
};

class B inherits A {
  myStringB : String <- "Hi Overide\n";
  myString(a: String, b: Int ): String { myStringB };
  mySelf(a: String): SELF_TYPE { self };
};

class C inherits B {
  myStringC : String <- "Hi Second Overide\n";
  myString(a : String, b : Int ): String { myStringC };
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";
  myIO : IO;
  c : C <- new C;
  main(): SELF_TYPE {
    out_string(c.myString("dummy", 1))
  };
  testStatic(): Object {
    out_string(c@B.myString("dummmy", 2))
  };
};

