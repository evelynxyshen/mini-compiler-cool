class Main inherits IO {
  a : Int <- 1;
  b : Int <- 20;
  x : Bool;
  main (): Object { 
    { 
      let x : Int <- 3, y: Int  in out_int(a+x+y);
      out_string("\n****\n");
      let z : Bool in out_string(z.type_name().concat("\n")); 
      let z : String in { out_string((z).concat("no init\n")); out_string(z); };
      
    }
   };
};
