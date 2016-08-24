
class Main inherits IO {
  myNum1 : Int  <- 3 ;
  myNum2 : Int  <- 2 ;
  main (): Object {
    let hello: String <- "Hello ",
        world: String <- "World!",
        newline: String <- "\n",
        no_init: String,
        nested_let : Int <- let temp: Bool <- true in myNum1 + myNum2
    in
    {
      out_string(hello.concat(world.concat(newline)));
      if nested_let = (myNum1 + myNum2) then out_string("Nested let success\n")
      else  out_string("Nested let fail\n")
      fi;
    }
  };
};
