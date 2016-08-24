
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
      x <- 1;
      1.copy();
      (1+1).type_name();
      x.type_name();
      1+x.copy();
      out_int(1+x.copy());
      out_string((1+x).type_name());
    }
  };
};
