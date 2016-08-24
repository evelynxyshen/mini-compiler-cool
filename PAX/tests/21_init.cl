class A inherits IO {
  a : Int <-21;
};

class Main inherits A {
  c : Int;
  b : Int <- 2+ 
              let a : Int <- 1+2+a in 
                        1+ 
                          let b: Int <- a in 3 * b + a + c; 
  x : Bool;
  s : String;
  a_obj : A;
  main (): Object { 
    { 
      x <- 99 = b;
      if x  then out_string("correct\n") 
            else { out_int(b); out_string("wrong\n"); } fi; 
      out_string(s.concat("empty\n"));
      out_string(x.type_name().concat("\n"));
      out_string((a_obj<-new A).type_name().concat("\n"));
    }
   };
};
