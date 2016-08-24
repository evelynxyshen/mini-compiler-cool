class Main inherits IO {
  x:Int <- 0;
  main (): Object {
    {
    while x<7 loop {
     x <- x + 1;
     out_string("cnt.\n");} pool;
  
    if x = 7 then out_string("Hi.\n")
            else out_string("F.\n") fi;
    }
  };
};
