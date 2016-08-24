
Class Main InhEriTs IO {
  myString1 : String1 <- myString;
  myString : String1 <- "Hello World!\n";

  main(): Object { 
    { 
      out_string("Hello World!\n");
      out_string(myString1) ;
    }
  };
};

class A inherits IO {
  myString1 : String1 <- myString;
  myString : String <- "Hello World!\n";

  out(): Object {
    {
      out_string("Hello World!\n");
      out_string(myString1) ;
    }
  };
};
