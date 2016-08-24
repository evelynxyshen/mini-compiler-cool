
class A {
  myInt1(): Int { "1"*1 };
  myInt2(): Int { 1*"1" };
  myInt3(): Int { "1"*"1" };
  myInt4(): Int { 1*1 };
  myBool1(): Bool {true};
  myBool2(): Bool {false};
  myBool3(): Bool {7};
  mylt1(): Bool {2 < 3};
  mylt2(): Bool {"2" < 3};
  mylt3(): Bool {2 < "3"};
  mylt4(): Bool {"2" < "3"};
  myleq1(): Bool {2 <= 3};
  myleq2(): Bool {"2" <= 3};
  myleq3(): Bool {2 <= "3"};
  myleq4(): Bool {"2" <= "3"};
  myeq1(): Bool {myInt4() = "3"};
  myeq2(): Bool { 2 = 3};
  myeq3(): Bool {"2" = 3};
  myneg1(): Int { ~3 };
  myneg2(): Int { ~"3" };
  myneg3(): Int { ~myInt4() };
  myneg4(): Int { ~true};
  mycomp1(): Bool {not(true)};
  mycomp2(): Bool {not(2)};
  
  myString : String <- "Hi\n";
};

Class Main InhEriTs IO {
  myString : String <- "Hello World!\n";

  main(): Object {
    out_string("Hello World!\n")
  };
};

