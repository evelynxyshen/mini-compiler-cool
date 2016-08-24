#!/usr/bin/perl
open (MYFILE, '>20_all_character.cl');
print MYFILE "class Main inherits IO {\n";

for ($count = 0; $count <256; $count++){
  my $char = chr($count);
  print MYFILE "$char\t";
}

print MYFILE "\n";

for ($i = 0; $i < 256; $i++) {
  for ($j = 0; $j < 256; $j++ ) {
    my $char1 = chr($i);
    my $char2 = chr($j);
    print MYFILE "$char1$char2\t";
  }
  printf MYFILE "\n";
}


print MYFILE  "\tmain(): Object {    out_string(myString)  }; \n";
print MYFILE  "};";
close MYFILE;
