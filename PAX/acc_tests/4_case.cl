Class Case_Test inherits IO {
  myString : String;
  outString: String <- "Hello World";
  myNum : Int <- 2;
  myPrint(out1 : Object): Object {
    {
    case out1 of 
      id1 : String => out_string(id1.concat(" is String in CASE ****\n"));
      id2 : Int    => {out_int(id2); out_string(" is Num in CASE ****\n");};
      id3 : Object => abort(); 
    esac;
    }
  };
  test(): Object {
    {
--      out_int(myNum);
--      out_string("Init Correct\n");
      if true then myNum <- (3+2)*5
        else myNum <- 1/(2-3)
      fi;
--      out_int(myNum);
--      out_string("Assignment Correct\n");
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

