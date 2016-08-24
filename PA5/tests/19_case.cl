class A inherits IO {
  x_A : Int <- 3;  
  bPrint () : Object {1};
};

class B inherits A {
  bPrint () : Object { out_string("Object is B\n")};
};

class C inherits A {
  bPrint () : Object{
  {
    out_int(x_A);
    out_string("\n");
  }
  };
};

class D inherits A {};

class E inherits A {};

class Main inherits IO {
  myString : String <- "MyString.";
  myNum : Int <- 2;
  myC: C <- new C;
  myPrint(out1 : Object): Object {
    {
    case out1 of 
      id4 : Object => abort();
      id1 : String => out_string(id1.concat("String\n"));
      id2 : Int    => out_string("Num\n");
      id3 : A      =>{ out_string("Class A :"); id3.bPrint(); };
      id4 : C      =>{ out_string("Class C :"); id4.bPrint(); };
--      id4 : Object => abort(); 
    esac;
    }
  };

  a : String <- "abc";
  main (): Object {
    {
      self.myPrint(myString);
      myPrint(myNum);
      myPrint(myC);
      myPrint(new B);
    }
  };
};

