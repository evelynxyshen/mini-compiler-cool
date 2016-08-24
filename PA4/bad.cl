class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		self;
           }
	};
};

Class Main {
	main():C {
	 {
	  (new C).init(1,1);
	  (new C).init(1,true,3);
	  (new C).iinit(1,true);
	  (new C);
	 }
	};
};

(* Test if type definition is wrong *)
Class Test_Attribute_Type_Main InhEriTs IO {
  myString1 : String1 <- myString;
  myString : String1 <- "Hello World!\n";

  main(): Object { 
    { 
      out_string("Hello World!\n");
      out_string(myString1) ;
    }
  };
};


class Dispatch_A {
  myString(a: String, b: String ):String { myString };
  myString : String <- "Hi\n";
};

(* Test wrong dispatch expression *)
class Dispatch_Main InhEriTs IO {
  myString : String <- "Hello World!\n";
  a : Dispatch_A;
  myInt : Int;
  main(): Object {
    a.myString(myString, myString, myString)
  };
  error1(): Int {
    a.myString(myString)
  };
  error2(): Object {
    a.myString(myString, myInt)
  };
  error3(): Int {
    a.myString1(myString)
  };
  error4(): String {
    b.myString(myString)
  };
  error5(): String {
    a.myString(myString1)
  };

};

(* Test arithmatic and bool op *)
class Arith_Bool_A {
  myInt1(): Int { "1"*1 };
  myInt2(): Int { 1*"1" };
  myInt3(): Int { "1"*"1" };
  myInt4(): Int { 1*1 };
  myBool1(): Bool {true};
  myBool2(): Bool {false};
  myBool3(): Bool {7};
  mylt1(): Bool {2 < 3};
  mylt2(): Bool {"2" < 3};
  mylt3(): Bool {2 < "3"};
  mylt4(): Bool {"2" < "3"};
  myleq1(): Bool {2 <= 3};
  myleq2(): Bool {"2" <= 3};
  myleq3(): Bool {2 <= "3"};
  myleq4(): Bool {"2" <= "3"};
  myeq1(): Bool {myInt4() = "3"};
  myeq2(): Bool { 2 = 3};
  myeq3(): Bool {"2" = 3};
  myneg1(): Int { ~3 };
  myneg2(): Int { ~"3" };
  myneg3(): Int { ~myInt4() };
  myneg4(): Int { ~true};
  mycomp1(): Bool {not(true)};
  mycomp2(): Bool {not(2)};
  
  myString : String <- "Hi\n";
};

(* Test 'self' expression in attribute, formal, assignment method *)
class SELF_EXPR {
  myString : String <- "Hi\n";
  myvoid1(): Bool{isvoid(false )};
  myvoid2(): Bool{isvoid(2)};
  mySelf(self: Object) : Object {1};
  self : SELF_TYPE;
  self(a: String) : Object { self <- 2};
  a(a: String) : String { myString <- 2};
};

(* Test attribute inherits*)
class Inherits_Attr_Test_A {
  myString : String <- "Hi\n";
  myString1 : String <- "Hi String1\n";
  myString1 : String <- "Hi String1 Overide\n";
  myWrong : Wrongtype;
  myWrong : Wrongtype1;
  b(a: String, b: Int ) : Object { myString <- a };
  self : SELF_TYPE;
};

class Inherits_Attr_Test_B inherits Inherits_Attr_Test_A {
  myString : String <- "Child's Hi\n";
  myString1 : String <- "Hi String1 inherit overide\n";
  myString1 : String <- "Hi String1 inherit second time\n";
  myWrong : String <- "Could overide wrong type\n";
  b() : Int {1};
  self : SELF_TYPE;
};

class Inherits_Attr_Test_C inherits Inherits_Attr_Test_A {
  b(a: Int) : Object {1};
  b() : Int {1};
  b(a: String, b: Int ) : Object {1};
  b(a: String, b: Int ) : Object {2}; 
};

class Inherits_Attr_Test_D inherits Inherits_Attr_Test_A {
  b(a: Int, b: String) : Object {1};
};

(* Test 'if' expression return type *)

class IF_return_type_A {
  if_error1(a: String, b: String ):String 
      { if myString then myString else myString fi };
  if_error2(a: String, b: String ):String 
      { if myString then myString else myInt fi };
  myString : String <- "Hi\n";
  myInt : Int <- 1;
};

(* Test if static dispatch is wrong *)

class A_static_dispatch {
  myString(a: String, b: Int ):String { myString };
  myString : String <- "Hi\n";
};

class B_static_dispatch inherits A_static_dispatch {
  myStringB : String <- "Hi Overide\n";
  myString(a: String, b: Int ): String { myStringB };
  mySelf(a: String): SELF_TYPE { self };
};

class C_static_dispatch inherits B_static_dispatch {
  myStringC : String <- "Hi Second Overide\n";
};

Class Main_static_dispatch InhEriTs IO {
  myString : String <- "Hello World!\n";
  myIO : IO;
  c : C_static_dispatch;
  e: E_static_dispatch;
  main(): SELF_TYPE {
    out_string(c@SELF_TYPE.myString("dummy", 1))
  };
  testStatic(): Object {
    out_string(c@B.myString1("dummmy", 1))
  };
  testStatic_TYPE(): Object {
    out_string(e@B.myString1("dummmy", 1))
  };
  testStatic_TYPE(): SELF_TYPE {
    c@C.mySelf("dummy")
  };
};

(* Test 'case' expression *)
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

(* Check if type error in 'let' expression *)
class Let_Test_Bad inherits IO {
  myNum1 : Int  <- 3 ;
  myNum2 : Int  <- 2 ;
  myNum3 : Int;
  let_test (): Object {
    let hello: String <- "Hello ",
        world: String <- "World!",
        newline: String <- "\n",
        no_init: String, 
        self : WRONG_TYPE <- "Overide self" + 2,
        wrong_type : NO_DEFINE <- wrong_type + 1,
        nested_let : Int <- let temp: Bool <- true,
                                temp2: Int,
                                temp3: String <- "HI",
                                myNum3 : String <- "Overide" 
                            in myNum3 <- myNum1 + myNum2,
        exit_scope : String <- myNum3,
        self_type : SELF_TYPE <- self,
        self_type : SELF_TYPE <- myNum3
    in
    {
      wrong_type + 1;
      self + 1;
      out_string(hello.concat(world.concat(newline)));
      if nested_let = (myNum1 + myNum2) then out_string("Nested let success\n")
      else  { out_string("Nested let fail\n"); abort(); }
      fi;
    }
  };
};

