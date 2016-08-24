class Let_Test inherits IO {
  myNum1 : Int  <- 3 ;
  myNum2 : Int  <- 2 ;
  myNum3 : Int;
  let_test (): Object {
    let hello: String <- "Hello ",
        world: String <- "World!",
        newline: String <- "\n",
        no_init: String, 
        nested_let : Int <- let temp: Bool <- true,
                                temp2: Int,
                                temp3: String <- "HI" 
                            in myNum3 <- myNum1 + myNum2
    in
    {
      out_string(hello.concat(world.concat(newline)));
      if nested_let = (myNum1 + myNum2) then out_string("Nested let success\n")
      else  { out_string("Nested let fail\n"); abort(); }
      fi;
    }
  };
};
class Main inherits IO {
  dummy : String;
  letTester : Let_Test <- new Let_Test;
  main (): Object {
    {
      letTester.let_test();
    }
  };
};

