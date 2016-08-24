class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  y : Int <- 13;
--  s : String <- ""
  main (): Object { 
    {
      self.test(y<-y+ (let x: Int <- 1 in 1+x) + 1, y<-y+1, y<-y+1);
      let y : Int in { out_int(y+2); out_string("\n"); };
      if 2 = (1+1).copy() then out_string("int is object\n") else abort() fi;
      (test(y, y, y)).copy();
    }
   };
  test(f1: Int, f2: Int, f3:Int) : Object { {
    if y= 18 then out_string("y is 18\n") else out_string("F\n") fi;
    if f1 = 16 then out_string("f1 is 16\n") else out_int(f1) fi;
    if f2 = 17 then out_string("f2 is 17\n") else out_int(f2) fi;
    if f3 = 18 then out_string("f3 is 18\n") else out_int(f3) fi;
  } };
};
