


class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  main (): Object { 
    { 
      x <- a+20 = b+1;
      while a < 10000 loop { out_int(a); out_string("\n"); a<-1+a; } pool;
    }
   };
};
