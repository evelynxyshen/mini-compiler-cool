class Main inherits IO {

  myString : String <- "Hello \0 World";
	myString : String <- "\   \t\t\t";
	main(): Object {    out_string(myString)  }; 
};
