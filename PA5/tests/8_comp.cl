class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  main (): Object { 
    { 
      x <- a<b;
      if x then out_string("correct\n") else out_string("wrong\n") fi;
    }
   };
};
