class Main inherits IO {
  a : String <- "Hi";
  b : String <- "How";
  c : String <- "Hello World\n";
  main (): Object { 
    { 
      out_string(c.substr(10, 2));
    }
  };
};
