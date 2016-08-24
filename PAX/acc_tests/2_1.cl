
class Comp {
  less(a : Int, b : Int) : Bool {
    if a < b then true
    else
      false
    fi
  };
  leq(a: Int, b : Int) : Bool {
    if a <= b then true
    else false
    fi
  };
};

class Main inherits IO {
  c : Comp <- new Comp;
  x : Int <- 0;
  test() : Object {
    {
      while x < 10 loop {
        out_string("\n");
        x <- x+1;
      } pool;
    }
  };
  main() : Object {
    {
      if c.less(1, 2) then out_string("True\n") else out_string("WRONG\n") fi;
      if c.less(3, 2) then out_string("WRONG\n") else out_string("True\n") fi;
      if c.leq(2,2 ) then out_string("True\n") else out_string("WRONG\n") fi;
    }
  };
};
