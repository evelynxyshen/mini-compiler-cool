class Main inherits IO {
  x:Int <- 35;
  main (): Object {
   { x <- x + 24;
     if x = 57 then out_string("Hi\n")
               else out_string("F\n")
     fi;}
   };
};
