class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  main (): Object { 
    { 
      x <- a+20 = b+1;
      if x = true then out_string("correct\n") else out_string("wrong\n") fi;
      if x = false then out_string("F\n") else out_string("correct\n") fi;
    }
   };
};
