
class Exp {
  f(n : Int) : Int {
    if n=0 then 1
    else
       2*f(n-1)
    fi
  };
};

class Main inherits IO {
  f : Exp <- new Exp;
  x : Int <- 0;
  test() : Object {
    {
      while x < 20 loop {
        out_int(f.f(x));
        out_string("\n");
        x <- x+1;
      } pool;
    }
  };
  main() : Object {
    {
      test();
      x <-1 ;
      while x < 10 loop {
        f.f(20);
        x <- x+1;
      } pool; 
--      if(f.f(3) = 8) then out_int(8) else out_string("WRONGXXXX\n") fi;
--      out_int(f.f(15));
    }
  };
};
