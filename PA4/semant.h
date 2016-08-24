#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {
private:
  int semant_errors;
  void install_basic_classes();
  ostream& error_stream;
  /* A symbol table is used to check correctness of inherits*/
//  SymbolTable<Symbol, Class__class> *class_table;

public:
  SymbolTable<Symbol, Symbol> *attr_def_table;
  SymbolTable<Symbol, Class__class> *class_table;
  ClassTable(Classes);
  Class_ lookup(Symbol sym);
  bool Subtype(Class_ child, Class_ parent);
  bool Subtype(Symbol child_name, Symbol parent_name);
  bool Subtype(Symbol child_type, Symbol parent_type, Class_ c);
  Symbol lub(Symbol a, Symbol b);
  Symbol lub(Symbol a, Symbol b, Class_ c);
  bool lookup_attribute(Symbol class_name, Symbol method_name);
  Feature lookup_method(Symbol class_name, Symbol method_name);
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
  
};


#endif

