class Main inherits IO {
 
	myString : String <- "\   \t\t\t";
  myString : String <- "\t\t\t\\";
  myString : String <- "\n\t\b\f\
 \ \H\e\l\l\o";
	main(): Object {    out_string(myString)  }; 
  myString : String <- "\t\t\t\";
};
