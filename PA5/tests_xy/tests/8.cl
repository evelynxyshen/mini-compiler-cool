class Main inherits IO {
  x : Int <- 0;
  main (): Object {
    { x <- 9; 
      if x=9 then  out_string("Hi\n")
        else  out_string("F\n")
      fi;
    }
  };
};
