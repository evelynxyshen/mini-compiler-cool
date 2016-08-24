Class Main inherits IO {
  myString : String;
  outString: String <- "Hello World\n";
  myNum : Int <- 2;
  myNum2 : Int;
  myBool1 : Bool;
  myBool2 : Bool;
  myBool3 : Bool;
  myPrint(out1 : String, out2: String, out3: String): Object {
    {
    self.out_string("Invokation\n");
    self.out_string(out1);
    self.out_string(out2);
    self.out_string(out3);
    self.out_string("Invokation End\n");
    }
  };
  main(): Object { 
    {
      if false then myNum <- myNum2 <- (3+2+3+4*(5+6))*5*7*8+4+3
        else {  myNum <- myNum2 <- 1/(2-~3); 
                myBool1 <- 2 < 3;
                myBool2 <- (2 = 4);
                myBool3 <- not not ~~2<3; 
                if myBool1 then out_string("Bool1 test: success\n")
                  else out_string("Bool1 test: fail\n")
                fi;
                if myBool2 then out_string("Bool2 test: fail\n")
                  else out_string("Bool2 test: success\n")
                fi;
                if myBool3 then out_string("Bool3 test: success\n")
                  else out_string("Bool3 test: fail\n")
                fi;
             }
      fi;
      myString <- ("test String assignment success\n");
      out_string(myString);
      self@IO.out_string(outString);
      self.myPrint(outString, outString, outString);
    } 
  };
};

Class Test inherits IO {
};
