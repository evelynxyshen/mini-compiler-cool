
class Fibon {
  x: String; 
--  test: Int;
--  test1: Int <- 1;
  f(n : Int) : Int {
    if n=0 then { (*x <- "b"; test<- 1;*) 1; }
    else
      if n=1 then { (*x <- "b"; test<-1;*) 1; }
      else
       { x <- x.concat("a"); (*test1<- test1+2; test<-test+2;*) (f(n-1)+f(n-2));  }
      fi
    fi
  };
};

class Main inherits IO {
  f : Fibon <- new Fibon;
  x : Int <- 0;
  test() : Object {
    {
      while x < 50 loop {
        out_int(f.f(x));
        out_string("\n");
        x <- x+1;
      } pool;
    }
  };
  main() : Object {
    {
      out_int(f.f(20));
      test();
--      out_int(f.f(1000));
    }
  };
};
