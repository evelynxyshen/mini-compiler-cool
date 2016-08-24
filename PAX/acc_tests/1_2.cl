
class Fibon {
  f(n : Int) : Int {
    if n=0 then 1
    else
      if n=1 then {1;}
      else 
        f(n-1)+f(n-2)
        --2-1+1
      fi
    fi
  };
};

class Main inherits IO {
  f : Fibon <- new Fibon;
  x : Int <- 0;
  test() : Object {
    {
      while x < 10 loop {
        out_int(f.f(x));
        out_string("\n");
        x <- x+1;
      } pool;
    }
  };
  main() : Object {
    {
--      out_int(8);
      if(f.f(5) = 8) then out_int(8) else out_string("WRONGXXXX\n") fi;
--      out_int(f.f(15));
--      out_int(f.f(1000));
    }
  };
};
