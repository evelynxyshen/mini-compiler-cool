class Main inherits IO {
  a : String <- "Hi";
  b : String <- "How";
  c : String;
  main (): Object { 
    { c <- b <- a <- "Hello\n";
      c <- "c Test\t";
      c <- c.concat("Test Overide\t");
      c <- c.concat("Test overide second\n");
      out_string(a); out_string(b); out_string(c);  
      out_string(c.substr(0, 10));
    }
  };
};
