class A {
};

class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  a_obj : A;
  main (): Object { 
    { 
      if isvoid(a_obj) = true then out_string("correct\n") else out_string("wrong\n") fi;
      if isvoid(x) then out_string("F\n") else out_string("correct\n") fi;
      
      if isvoid while a < 10 loop { out_int(a <- 1+a); out_string("\n");} pool
         then out_string("correct\n") 
         else out_string("wrong\n")
      fi;
    }
   };
};
