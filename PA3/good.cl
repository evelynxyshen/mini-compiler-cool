
class A {
ana(): Int {
(let x:Int <- 1, y:Int <-3 in 2)+3
};
};

Class BB__ inherits A {
};

(* Test let expression, nested let expression, let expression without 
  ambiguity*)

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

class Loop_Test inherits IO {
  myNum : Int <- 10;
  myCounter : Int <- 0;
  test ():Object {
  
  {  while 0 < myNum loop { myNum <- myNum -1; myCounter <- myCounter + 1;}
    pool;
    if myCounter = 10 then out_string ("Loop test success\n")
      else out_string("Loop test fail\n")
    fi;
  }
  };
};

(** Test case expression *)
Class Case_Test inherits IO {
  myString : String;
  outString: String <- "Hello World\n";
  myNum : Int <- 2;
  myPrint(out1 : Object): Object {
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


(* Test multiple features, test assignment expressions, assignment expression
   with right association, test methods and attribute features,
   nested if then else fi expression,
   test dispatch expression, test inverse integer, bool compliment operator,
   isvoid keywords
   compare operator, add/sub/mult/divide operators. 
   Test precedence of those arithmatic operators *)
Class Many_Test inherits IO {
  myString : String;
  outString: String <- "Hello World\n";
  myNum : Int <- 2;
  myNum2 : Int;
  myBool1 : Bool;
  myBool2 : Bool;
  myBool3 : Bool;
  myBool4 : Bool;
  myPrint(out1 : String, out2: String, out3: String): Object {
    {
    self.out_string("Invokation\n");
    self.out_string(out1);
    self.out_string(out2);
    self.out_string(out3);
    self.out_string("Invokation End\n");
    }
  };
  test(): Object { 
    {
      if false then myNum <- myNum2 <- (3+2+3+4*(5+6))*5*7*8+4+3
        else {  myNum <- myNum2 <- 1/(2-~3); 
                myBool1 <- 2 < 3;
                myBool2 <- (2 = 4);
                myBool3 <- not not ~~2<=3; 
                myBool4 <- isvoid isvoid ~2 = isvoid self;
                if myNum = 1/(2+3) then out_string("Arithmatic test: success\n")
                  else { out_string("Arithmatic fail\n"); abort(); }
                fi;
                if myBool1 then out_string("Bool1 LESS test: success\n")
                  else out_string("Bool1 LESS test: fail\n")
                fi;
                if myBool2 then out_string("Bool2 EQUAL test: fail\n")
                  else out_string("Bool2 EQUAL test: success\n")
                fi;
                if myBool3 then 
                      out_string("Bool3 LE, INT_INV, BOOL_COMP test: success\n")
                  else out_string("Bool3 test: fail\n")
                fi;
                if myBool4 then out_string("Bool4 ISVOID test: success\n")
                   else {out_string("Bool4 ISVOID test: fail\n"); abort();}
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

(* Test static dispatch expression, test expression precedence *)
class Static_Dispatch_Parent inherits IO {
  a(): Int { 1+2 };
};
class Static_Dispatch_Test inherits Static_Dispatch_Parent {
  a(): Int { 1-2 };
  test(): Object {
    {
      if 1-2 = a() then out_string("Dispatch success\n")
      else  { out_string ("Dispatch fail\n");  abort();  }
      fi;
      if 1+2 = self@Static_Dispatch_Parent.a() 
          then out_string("Static Dispatch Success\n")
      else {  out_string ("Static Dispatch fail\n");  abort();  }
      fi;
      if ~(1+2) = ~self@Static_Dispatch_Parent.a() 
          then out_string("Static Dispatch With Negative Sign Success\n")
      else {  out_string ("Static Dispatch With Negative Sign fail\n");  
              abort();  }
      fi;

    }
  };
};

class Main inherits IO {
  dummy : String;
  letTester : Let_Test <- new Let_Test;
  loopTester: Loop_Test <- new Loop_Test;
  caseTester : Case_Test <- new Case_Test;
  manyTester : Many_Test <- new Many_Test;
  dispatchTester : Static_Dispatch_Test <- new Static_Dispatch_Test;
  main (): Object {
    {
      letTester.let_test();
      loopTester.test();
      caseTester.test();
      manyTester.test();
      dispatchTester.test();
    }
  };
};

