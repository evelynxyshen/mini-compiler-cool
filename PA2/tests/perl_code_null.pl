#!/usr/bin/perl
open (MYFILE, '>13_code_null.cl');
print MYFILE "class Main inherits IO {\n \
\tmyString : String <- \0\"";

for ($count = 0; $count <1; $count++){
  print MYFILE "\\\0\0\0";
}
print MYFILE  "\\t\\t\\t\";\n\0";

print MYFILE  "\tmain(): Object {    out_string(myString)  }; \n";
print MYFILE  "};";
