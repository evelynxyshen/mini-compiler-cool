class Main inherits IO {
  myString : String <- "Hello World!\n;";
-- in comments;
(* This is comments*)
(* "This is another 
  " **** ****)
--(*
  *)
  (*** testing nested comments ****
    *
    **((
    --**(*
    inside nested comments *)
    
  *)
  ****)
  *)
  *(* Now this comments will match(*(
    again
  )**)
  *)
  ;
  main(): Object {    
    123
    self.out_string(myString)  
  };
};
-- no \n OK?
(*  EOF in comments
