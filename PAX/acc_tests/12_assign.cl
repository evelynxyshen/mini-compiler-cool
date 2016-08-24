class Main inherits IO {
  a : String <- "Hi";
  b : String <- "How";
  c : String;
  x : Int <- 1;
  y : Int <- 8;
  z : Object;
  main (): Object { 
    { c <- b <- a <- "Hello\n";
      c <- "c Test\t";
      c <- c.concat("Test Overide\t");
      c <- c.concat("Test overide second\n");
      out_string(a); out_string(b); out_string(c); 
      out_string(c@String.substr(1+x, 2+y).concat("\n"));
      z <- x+y;
      out_string(z.type_name().concat("\n"));
    }
  };
};
