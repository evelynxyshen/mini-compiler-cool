(*
 *  This is a basic test
 *
 *  First it will test whether comments works
  ((((*** 
   *  Then it will test whether nested comments works 
    *
    ***(**
      3rd level nested comments
    *)*
  (((
  **)
 *)

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {  
    out_string("Hello World!\n") 
  };
};
