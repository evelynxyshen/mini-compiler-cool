(* This test block expr  *)

Class Main InhEriTs IO {
--  myString3 : Int;
  myString1 : String <- myString;
  myString : String <- "Hello World!\n";

  main(): Object { 
    { 
      out_string("Hello World!\n");
      out_string(myString1) ;
    }
  };
};

class A inherits IO {
  myString1 : String <- myString;
  myString : String <- "Hello World!\n";

  out(): Object {
    {
      out_string("Hello World!\n");
      out_string(myString1) ;
    }
  };
};
