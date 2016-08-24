Class Main inherits IO {
  myString : String;
  outString: String <- "Hello World\n";
  myNum : Int <- 2;
  myPrint(out1 : Object, out2 : Object, out3 : Object): Object {
    {
    self.out_string("Invokation\n");
    case out1 of
      id1 : String => out_string("String\n");
      id2 : Int    => out_string("Num\n");
      id3 : Object => abort(); 
    esac;
    self.out_string("Invokation End\n");
    }
  };
  main(): Object { 
    {
      if true then myNum <- (3+2)*5
        else myNum <- 1/(2-3)
      fi;
      self.myPrint(outString);
      myPrint(myNum);
    } 
  };
};

Class Test inherits IO {
};
