class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  main (): Object { 
    { 
      let x : Int <- 1, y: Int <-1+x+1 in out_int(a+x+y);
      out_string("\n****\n");
    }
   };
};
