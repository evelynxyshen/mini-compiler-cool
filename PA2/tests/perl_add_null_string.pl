#!/usr/bin/perl
#open (MYFILE, '>7_EOF_string.cl');
#print MYFILE "class Main inherits IO {\n \
#\tmyString : String <- \" EOF in string";

#open (MYFILE1, '>>5_string_null.cl');
#print MYFILE1 "\" null in string \0 EOF in string";
#close(MYFILE);

open (MYFILE, '>12_string_escape_null.cl');
print MYFILE "class Main inherits IO {\n \
\tmyString : String <- \"";

for ($count = 0; $count <1; $count++){
  print MYFILE "\\\0";
}
print MYFILE  "\\t\\t\\t\";\n";

print MYFILE  "\tmain(): Object {    out_string(myString)  }; \n";
print MYFILE  "};";
