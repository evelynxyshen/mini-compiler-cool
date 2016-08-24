
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
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";
  myIO : IO;
  c : C;
  e: E;
  main(): SELF_TYPE {
    out_string(c@SELF_TYPE.myString("dummy", 1))
  };
  testStatic(): Object {
    out_string(c@B.myString1("dummmy", 1))
  };
  testStatic_TYPE(): Object {
    out_string(e@B.myString1("dummmy", 1))
  };
  testStatic_TYPE(): SELF_TYPE {
    c@C.mySelf("dummy")
  };
};

