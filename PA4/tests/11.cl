
class A {
  if_error1(a: String, b: String ):String 
      { if myString then myString else myString fi };
  if_error2(a: String, b: String ):String 
      { if myString then myString else myInt fi };
  myString : String <- "Hi\n";
  myInt : Int <- 1;
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

