(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)
class IntTest inherits IO {
  int1 : Int <- 5;
  int2 : Int <- 10;
  int3 : Int;  
  res : Bool;

  test():Object {
    {
      int3 <- int1 + int2;
      out_string("T8: "); out_int(int3); out_string(" ");
      int3 <- int2 - int1; out_int(int3); out_string(" ");
      res <- int1 < int2; 
      if res then out_string("correct\n") else out_string("wrong\n") fi;
      
      out_string("T9: ");
      res <- int1 + 15 = int2 + 10;
      if res = true then out_string("correct\n") else out_string("wrong\n") fi;
      out_string("T10: ");
      res <- int1 + 15 = int2 + int2;
      if res = true then out_string("correct\n") else out_string("wrong\n") fi;
      out_string("T12: ");
      int3 <- int2 / int1;
      out_int(int3);
      
    }
  };  
};

class BoolTest {};
class IoTest inherits IO {
  str1 : String <- "Hello World!\n";
  str2 : String;
  str3 : String <- "concat string. ";
  str4 : String;

  test():Object { 
    {
      out_string("T1: Hello World!\n");
      out_string("T2: "); out_string(str1); 
      out_string("T3: "); out_string(str2); out_string("\n");
      out_string("T4: "); out_string( str3.concat("concat test. \n") ); 
      out_string("T6: "); out_string( str3.substr(0, 5) ); out_string("\n");
      out_string("T13: "); out_string( str3.substr(5, 5) ); out_string("\n");
      out_string("T7: ");
      str4 <- str1 <- str3 <- "Assign Test.\n";
      out_string(str4);
      out_string(str3);
    }
  };
};

class A inherits IO {
  myString(a: String, b: String ):String { myString };
  myString : String <- "Str1\n";
};

class DomainTest inherits A {
  myPrint(s: String, s1: String): Object { { out_string(s1); out_string(s);} };
  test(): Object {
    {
      out_string("T5: "); myPrint(myString, myString2);
      
    }
  };
  myString2 : String <- "Str2\n";
};

class Dis_A inherits IO {
  out(): SELF_TYPE { out_string("A\n") };
};

class Dis_B inherits Dis_A {
  dummy() : Object {1};
  out(): SELF_TYPE { out_string("B\n") };
};

class Dis_C inherits Dis_B {
  dummyc(): Object {2};
  out(): SELF_TYPE { out_string("C\n") };
};

class SD_A inherits IO {
  out(): SELF_TYPE { out_string("A\n") };
};

class SD_B inherits SD_A {
  dummy() : Object {1};
  out(): SELF_TYPE { out_string("B\n") };
};

class SD_C inherits SD_B {
  dummyc(): Object {2};
  out(): SELF_TYPE { out_string("C\n") };
};

class SD_D inherits SD_C {
  dummyc(): Object {1};
  out(): SELF_TYPE { out_string("D\n") };
};

class Static_DispatchTest inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  c : SD_C <- new SD_C;
  test (): Object {
    {
      out_string("T20: \n");
      c@SD_A.out();
      c@SD_B.out();
      c@SD_C.out();
      (c<- new SD_D).out();
    }
  };
};

class DispatchTest inherits IO {
  y : Int <- 15;
  c : Dis_A;

  fun(f1: Int, f2: Int, f3:Int) : Object { {
    if y= 18 then out_string("y is 18\n") else out_string("F\n") fi;
    if f1 = 16 then out_string("f1 is 16\n") else out_int(f1) fi;
    if f2 = 17 then out_string("f2 is 17\n") else out_int(f2) fi;
    if f3 = 18 then out_string("f3 is 18\n") else out_int(f3) fi;
  } };

  test(): Object {
    {
      out_string("T11: ");
      self.fun(y<-y+1, y<-y+1, y<-y+1);
      if 2 = (1+1).copy() then out_string("int is object\n") else abort() fi;
      (fun(y, y, y)).copy();

      out_string("T19: ");
      c <- new Dis_A;
      c.out();
      c <- new Dis_B;
      c.out();
      c <- new Dis_C;
      c.out();
      out_string("\n");
  
    }
   };  
};

class LoopTest{};

class Case_A inherits IO {
  x_A : Int <- 3;  
  bPrint () : Object {1};
};

class Case_B inherits Case_A {
  bPrint () : Object { out_string("Object is B\n")};
};

class Case_C inherits Case_A {
  bPrint () : Object{
  {
    out_int(x_A);
    out_string("\n");
  }
  };
};

class Case_D inherits Case_A {};

class Case_E inherits Case_A {};


class CaseTest_Sub inherits IO {
  myString : String;
  outString: String <- "Hello World";
  myNum : Int <- 2;
  myC : Case_C <- new Case_C;

  myPrint(out1 : Object): Object {
    {
    case out1 of
      id6 : Object => abort();
      id1 : String => out_string(id1.concat(" is String in CASE ****\n"));
      id2 : Int    => {out_int(id2); out_string(" is Num in CASE ****\n");};
      id4 : Case_C      =>{ out_string("Class C :"); id4.bPrint(); };
      id5 : Case_A      =>{ out_string("Class A :"); id5.bPrint(); };
    esac;
    }
  };
  fun(): Object {
    {
      if true then myNum <- (3+2)*5
        else myNum <- 1/(2-3)
      fi;
      self.myPrint(outString);
      myPrint(myNum);
      myPrint(myC);
      myPrint(new Case_B);
    }
  };
};

class CaseTest inherits IO {
  caseTester : CaseTest_Sub <- new CaseTest_Sub; 
  test (): Object {
    {
      out_string("T18: ");
      caseTester.fun();
    }
  };
};

class LetTest inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  test() : Object {
    {
      out_string("T14: ");
      let x : Int <- 1, y: Int <-1+x+1 in out_int(a+x+y);
      out_string("\n");
      out_string("T15: ");
      let x : Int <- 1 in { let x: Int <-1+x in out_int(x); out_int(x); };
      out_string("\n");
      out_string("T16: ");
      let x : Int <- 1 in
      { out_int(2 + {let x: Int <-1+x in x; } + x) ;  out_int(x); };
      out_string("\n");
      out_string("T22: \n");
      let x : Int <- 3, y: Int  in out_int(a+x+y); out_string("\n");
      out_string("T23: \n");
      let z : Bool in out_string(z.type_name().concat("\n")); 
      let z : String in { out_string((z).concat("no init\n")); out_string(z); };

    }
  };
};

class NewTest_Sub inherits IO {
  a : Int <- 11;
  b : Int <- 20;
  fun (): Object {
    {
      out_int(a);
      out_string("\n");
    }
  };
};
 
class NewTest inherits IO { 
  a : NewTest_Sub <- new NewTest_Sub;
  test() : Object { { 
    out_string("T17: "); a.fun(); 
  } };

};

class Init_A inherits IO {
  a : Int <-21;
};

class InitTest inherits Init_A {
  b : Int <- 2+
              let a : Int <- 1+2+a in
                        1+
                          let b: Int <- a in 3 * b + a; 
  x : Bool;
  s : String;
  a_obj : Init_A;
  test(): Object {
    {
      out_string("T21: \n");
      x <- 99 = b;
      if x  then out_string("correct\n")
            else { out_int(b); out_string("wrong\n"); } fi; 
      out_string(s.concat("empty\n"));
      out_string(x.type_name().concat("\n"));
      out_string((a_obj<-new Init_A).type_name().concat("\n"));
    }
   };
};

class Isvoid_A {
};

class IsvoidTest inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  a_obj : Isvoid_A;

  test(): Object {
   {
      out_string("T22: \n");
      if isvoid(a_obj) = true then out_string("correct\n") else out_string("wrong\n") fi;
      if isvoid(x) then out_string("F\n") else out_string("correct\n") fi;

      if isvoid while a < 10 loop { out_int(a <- 1+a); out_string("\n");} pool
         then out_string("correct\n")
         else out_string("wrong\n")
      fi;
    }
   };
};

class Main inherits IO {
  ioTester : IoTest <- new IoTest;
  domainTester : DomainTest <- new DomainTest;
  intTester : IntTest <- new IntTest;
  dispatchTester : DispatchTest <- new DispatchTest;
  letTester : LetTest <- new LetTest;
  newTester : NewTest <- new NewTest;
  caseTester : CaseTest <- new CaseTest;
  sdTester : Static_DispatchTest <- new Static_DispatchTest;
  initTester : InitTest <- new InitTest;
  isvoidTester : IsvoidTest <- new IsvoidTest;

  main() : Object { 
    {
      ioTester.test();
      domainTester.test();
      intTester.test();
      dispatchTester.test();
      letTester.test();
      newTester.test();
      caseTester.test();
      sdTester.test();
      initTester.test();
      isvoidTester.test();
    }
  };
};

