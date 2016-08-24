#!/usr/bin/perl
#open (MYFILE, '>7_EOF_string.cl');
#print MYFILE "class Main inherits IO {\n \
#\tmyString : String <- \" EOF in string";

#open (MYFILE1, '>>5_string_null.cl');
#print MYFILE1 "\" null in string \0 EOF in string";
#close(MYFILE);

open (MYFILE, '>17_long_string.cl');
print MYFILE "class Main inherits IO {\n \
\tmyString : String <- \"";

for ($count = 0; $count <1025; $count++){
  print MYFILE "a";
}
print MYFILE  "\";\n";

print MYFILE "\tmyString : String <- \"";

for ($count = 0; $count <1024; $count++){
  print MYFILE "b";
}
print MYFILE "\\\n\";\n";

print MYFILE "\tmyString : String <- \"";

for ($count = 0; $count <1023; $count++){
  print MYFILE "c";
}
print MYFILE "\\t\\\n\";\n\n\n";

print MYFILE "\tmyString : String <- \"";

for ($count = 0; $count <1023; $count++){
  print MYFILE "d";
}
print MYFILE "\\b\\t\\c\\f\\n\";\n";

print MYFILE "\tmyString : String <- \"";
for ($count = 0; $count <1021; $count++){
  print MYFILE "e";
}
print MYFILE "\\b\\c\\n\";\n";

print MYFILE "\tmyString : String <- \"";

for ($count = 0; $count <1025; $count++){
  print MYFILE "1";
}

#print MYFILE  "\\t\\t\\t\";\n";

#print MYFILE  "\tmain(): Object {    out_string(myString)  }; \n";
#print MYFILE  "};";
close (MYFILE);
