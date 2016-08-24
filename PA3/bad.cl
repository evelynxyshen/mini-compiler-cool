
(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "myparser bad.cl" to see the error messages that your parser
 *  generates
 *)

(* class definition no error *)
class A {
  ;
  -- a good feature 
  feature_b(): Int { 1 };
  -- test recover from bad features
  a_C(): Int;
  a_D : Int < 1;
  (* feature definition correct, test recover from error in { [expr;]+ } *)
  feature_c(): Int { { $ ;} };
  feature_d(): Int { {{1; $3;};
                     $2;} };
  (* Test error expression *)
  feature_e(): Int {  true & false };
  (* Test recover from wrong let binding *)
  feature_let(): Object {
    let h: String <- "Hello ",
        w: String < "World!", (* Test consecutive wrong let binding *)
        n: String = "\n",
        l: string <- "\n" (* Test the final let binding is wrong *)
    in
      temp <- h.concat(w.concat(n))
  };
};

(* Test whether parser could catch wrong expressions *)
class ExpressionTest {
  (* comparator could not be assocative *)
  compExpr (): Object {{ {true = false = true; };
                        { 1 <2 < 3; };
                        { 1<=2<=3; }; }};
  (* Test wrong assignment expression and dispatch expression*)
  assignExpr (): Object { {Int <- 1; 
                           a <- ;} };
  dispatchExpr (): Object {{SELF_TYPE.compExpr();
                            assignExpr(;}};
  (* Test wrong arithmatic expression *)
  arithmaticExpr (): Object { {
                              myNum +; 
                              myNum -; myNum *<- 2; myNum -> 2;
                              } };
  boolExpr (): Object {{ {isvoid MyNum;}; {not Mybool;};}};
  (* Test all kinds of errors in case expression *)
  caseExpr (out1 : Object): Object {
    { {
    case out1 in (* Key words wrong *)
      id1 : String => out_string("String\n");
      id2 : Int    => out_string("Num\n");
    esac;}; {
    case Out1 of (* ID type wrong *)
      id1 : String => out_string("String\n");
      id2 : Int    => out_string("Num\n");
    esac; }; {
    case out1 of (* Darrow key word wrong *)
      id1 : String -> out_string("String\n");
      id2 : Int    => out_string("Num\n");
    esac; }; {
    case out1 of (* expression wrong *)
      id1 : String => out_string("String\n";
      id2 : Int    => out_string("Num\n");
    esac; };
    }
  };
  (* Test all kinds of error in while loop expr *)
  loopExpr ():Object {
  {
    {  while 0 > myNum loop myNum <- myNum -1
      pool; -- expression between while and loop wrong
    };
    {  while 0 < myNum begin myNum <- myNum -1
      pool; -- keywords wrong
    };
    {  while 0 < myNum loop myNum <- myNum -1
      ; -- missing keywords
    };

  }  };
  ifExpr(): Object {
    {
      {if true myNum <- (3+2)*5
        else myNum <- 1/(2-3)
      fi;} ;  -- missing keywords
      {if Class_A then myNum <- (3+2)*5
        else myNum <- 1/(2-3)
      fi;};   -- expression is wrong
    }
  };
  otherExpr(): Object {
    {
      { new object;} ;  -- wrong ID
      { isvoid Type;};   -- test isvoid
      { ~Something  ;}; -- test ~
      { 3*(4+5; };      -- () mismatch
    } 
  };

};

(* Test wrong class definition due to illegal character input *)
#

(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error:  closing brace is missing *)
Class E inherits A { 
;
(* If a class is not terminated correctly, then it could not recover *)
(* error:  keyword inherits is misspelled *)
Class f inherts A {
};



