class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  main (): Object { 
    { 
      let x : Int <- 1 in { let x: Int <-1+x in out_int(x); out_int(x); };
      out_string("\n****\n");
    }
   };
};
