
class A {
--  myString : String <- "Hi\n";
  myString(a: String, b: String ):String { myString };
--  myString(): String { 1 };
  myString : String <- "Hi\n";
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";
  a : A;
  myInt : Int;
  main(): Object {
--    out_string("Hello World!\n")
    a.myString(myString, myString, myString)
  };
  error1(): Int {
    a.myString(myString)
  };
  error2(): Object {
    a.myString(myString, myInt)
  };
  error3(): Int {
    a.myString1(myString)
  };
  error4(): String {
    b.myString(myString)
  };
  error5(): String {
    a.myString(myString1)
  };

};

