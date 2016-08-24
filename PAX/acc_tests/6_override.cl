
class IO_child inherits IO {
  io : IO <- new IO;
  out_int(n : Int) : SELF_TYPE {
    {
      io.out_int((n-1)*n);
      self;
    }
  };
};


class Main inherits IO {
  x : Int <- 0;
  io : IO_child <- new IO_child;
  test() : Object {
    {
      while x < 10 loop {
        x <- x+1;
      } pool;
    }
  };
  main() : Object {
    {
      out_int(3);
      out_string("\n");
      io.out_int(3);
      out_string("\nOverride result \n");
    }
  };
};
