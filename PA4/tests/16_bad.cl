Class Case_Test inherits IO {
  myString : String;
  outString: String <- "Hello World\n";
  myNum : Int <- 2;
  myPrint(out1 : Object): Object {
    {
    self.out_string("Invokation\n");
    case out1 of 
      id1 : String => out_string(id1.concat("String\n"));
      id2 : Int    => out_string("Num\n");
      id3 : Object => abort();
      self : SELF_TYPE => x.abort(); 
      y : NO_TYPE => y.abort();
    esac;
    self.out_string("Invokation End\n");
    myString <- case out1 of id1 : Int => id1; 
                             id2 : String => id2;
                             id3 : Int => id3; 
                esac;
    }
  };
  test(): Object {
    {
      if true then myNum <- (3+2)*5
        else myNum <- 1/(2-3)
      fi;
      self.myPrint(outString);
      myPrint(myNum);
    }
  };
};

class Main inherits IO {
  dummy : String;
  caseTester : Case_Test <- new Case_Test;
  main (): Object {
    {
      caseTester.test();
    }
  };
};

