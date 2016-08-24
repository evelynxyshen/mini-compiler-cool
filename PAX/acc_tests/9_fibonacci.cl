
class Fibon {
  x: String;
  a1: Int;
  a2: Int;
  r : Int; 
  c : Int;
--  test: Int;
--  test1: Int <- 1;
  f(n : Int) : Int {
  {
    a1 <- 0;
    a2 <- 0;
    r <- 1;
    c <- 0;
    while c < n loop { a2 <- a1; a1 <- r; r <- a1 + a2; c <- c+1; } pool;
    r;
  }
  };
};

class Main inherits IO {
  f : Fibon <- new Fibon;
  x : Int <- 0;
  test() : Object {
    {
      while x < 40 loop {
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
