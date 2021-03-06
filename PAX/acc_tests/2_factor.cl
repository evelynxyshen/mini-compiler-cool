
class Factor {
  f(n : Int) : Int {
    if n=0 then 1
    else
      if n=1 then {1;}
      else 
        n*f(n-1)
      fi
    fi
  };
};

class Main inherits IO {
  f : Factor <- new Factor;
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
--      if(f.f(3) = 6) then out_int(6) else out_string("WRONGXXXX\n") fi;
--      out_int(f.f(15));
--      out_int(f.f(1000));
    }
  };
};
