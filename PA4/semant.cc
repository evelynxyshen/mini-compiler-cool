

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "semant.h"
#include "utilities.h"


extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    No_expr,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}

typedef SymbolTable<Symbol, Symbol> Env;

ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr) {

    /* Fill this in */
  class_table = new SymbolTable<Symbol, Class__class>();
  attr_def_table = new Env();

  class_table->enterscope();

  /* First add all classes names into the symbol table */
  this->install_basic_classes();
  bool hasmain = 0;
 
  for(int i = classes->first(); classes->more(i); i=classes->next(i)) {
    Symbol class_name = classes->nth(i)->class_name();
    Symbol parent_name = classes->nth(i)->parent_name();
    if (class_name == Main){
      hasmain = 1;
    }
    /* Check Redefine Error */
    if(class_table->lookup(class_name) != NULL || class_name == SELF_TYPE ){
      this->semant_error(classes->nth(i));
      if(class_name == Int || class_name == Bool || class_name == Str || 
         class_name == Object || class_name == IO || class_name == SELF_TYPE)
        cerr <<"Redefinition of basic class "<<class_name<<".\n";
      else
        cerr <<"Class "<<class_name<<" was previously defined."<<endl;
    }
    else if(parent_name == Int || parent_name == Bool || parent_name == Str
            || parent_name == SELF_TYPE ){
      this->semant_error(classes->nth(i));
      cerr << "Class "<< classes->nth(i)->class_name() 
           <<" cannot inherit class "<<parent_name<<".\n";
    }
    class_table->addid(class_name, classes->nth(i));
  }
  if (!hasmain) {
    cerr << "Class Main is not defined." << endl;
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
  }

  for(int i = classes->first(); classes->more(i); i=classes->next(i)) {
    Symbol parent_name = classes->nth(i)->parent_name();
    /* Check Redefine Error */
    if(class_table->lookup(parent_name) == NULL ) {
      this->semant_error(classes->nth(i));
      cerr << "Class "<< classes->nth(i)->class_name() <<
              " inherits from an undefined class "<<parent_name<<endl;
    }
  }
  /* This table will be used to check inheritance relation */


    if (this->errors()) {
      cerr << "Compilation halted due to static semantic errors." << endl;
      exit(1); 
    }

  /* Check if there is inheritance cycle */
  for(int i = classes->first(); classes->more(i); i=classes->next(i)) {
    Class_ check_class = classes->nth(i);
    Symbol parent_class = check_class->parent_name();
    while(parent_class != Object || parent_class != IO || parent_class != Int
          || parent_class != Bool || parent_class != Str ){
      if(parent_class == check_class->class_name()){
        semant_error(check_class);
        cerr << "Class "<<check_class->class_name()<<
              " involved in an inheritance cycle.\n";
        break;
      } else {
        if(class_table->lookup(parent_class) == NULL){
          break;
        }
        else
          parent_class = class_table->lookup(parent_class)->parent_name();
      }
    }
  }

  if (this->errors()) {
      cerr << "Compilation halted due to static semantic errors." << endl;
      exit(1);
  }

}

/* Those classes are used widely */
Class_ Object_class, IO_class, Int_class, Bool_class, Str_class;

void ClassTable::install_basic_classes() {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

  /*  Class_ */ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
  /*  Class_ */ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
   /* Class_*/ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

    //
    // Bool also has only the "val" slot.
    //
  /*  Class_*/ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //       
  /*  Class_*/ Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       append_Features(
									       single_Features(attr(val, Int, no_expr())),
									       single_Features(attr(str_field, prim_slot, no_expr()))),
							       single_Features(method(length, nil_Formals(), Int, no_expr()))),
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, 
								      no_expr()))),
			       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)), 
								     single_Formals(formal(arg2, Int))),
						      Str, 
						      no_expr()))),
	       filename);

    class_table->addid(Object, Object_class);
    class_table->addid(IO, IO_class);
    class_table->addid(Bool, Bool_class);
    class_table->addid(Str, Str_class);
    class_table->addid(Int, Int_class);
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 



/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    ClassTable *classtable = new ClassTable(classes);

    /* some semantic analysis code may go here */
    /* First pass, check methods of all classes */
    for(int i = classes->first(); classes->more(i); i=classes->next(i))
      classes->nth(i)->check_feature_def(classtable);

/*
    if (classtable->errors()) {
  cerr << "Compilation halted due to static semantic errors." << endl;
  exit(1);
    }
*/
    /* Second pass */
    this->visit_AST(classtable, cout, 0);
//    cout <<"Semant Analysis End\n";

    if (classtable->errors()) {
	cerr << "Compilation halted due to static semantic errors." << endl;
	exit(1);
    }
  delete classtable;
}

void program_class::visit_AST(void* c_tbl, ostream& stream, int n)
{
//  stream << "program visit AST\n";
  for(int i = classes->first(); classes->more(i); i=classes->next(i))
    classes->nth(i)->visit_AST(c_tbl, stream, n+2);
}

void class__class::visit_AST(void* c_tbl, ostream& stream, int n)
{
//  dump_Symbol(stream, n+2, name);
//  stream << "class visit AST\n";
  Env *env = new Env();
  env->enterscope();
  //visit each feature, collect all attributes
  for(int i=features->first(); features->more(i); i=features->next(i))
    features->nth(i)->collect_feature(this, c_tbl, (void *)env);
  //recursively collect all attribute feature in parent classes
//  env->dump();
  ClassTableP class_table = (ClassTableP) c_tbl;
  Class_ parent_class = class_table->lookup(parent_name());
  if(parent_class!= NULL)
    collect_inherit_feature(this, c_tbl, (void *)env, parent_class);

  //after collect all features, check type
  for(int i=features->first(); features->more(i); i=features->next(i))
    features->nth(i)->check_feature(this, c_tbl, (void *)env); 
  env->exitscope();
  delete env;
}

void class__class::check_feature_def(void* c_tbl)
{
  ClassTableP class_table = (ClassTableP) c_tbl;
  class_table->class_table->enterscope();
  class_table->attr_def_table->enterscope();
  for(int i=features->first(); features->more(i); i=features->next(i))
    features->nth(i)->check_feature_def(this, c_tbl);
  class_table->class_table->exitscope();
  class_table->attr_def_table->exitscope();
}

void method_class::check_feature_def(Class_ c, void* class_tbl)
{
  /* Go for first pass to find out that no method is multiplied defined */
  ClassTableP class_table = (ClassTableP) class_tbl;

  /* Method begins with non-capital letter*/
  if(class_table->lookup(name) != NULL){
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Method "<<name<<" is multiply defined.\n";
  } else {
    //check formals definition
    for(int i=formals->first(); formals->more(i); i= formals->next(i)){
      Symbol formal_type = formals->nth(i)->get_type();
      Symbol param_name = formals->nth(i)->param_name();
      if(param_name == self ){
        class_table->semant_error(c->get_filename(), this);
        cerr<<"'self' cannot be the name of a formal parameter.\n";
      } else if(formal_type == SELF_TYPE ){
        class_table->semant_error(c->get_filename(), this);
        cerr<<"Formal parameter "<<param_name<<" cannot have type SELF_TYPE.\n";
      } else if( class_table->lookup(formal_type) == NULL ){
        class_table->semant_error(c->get_filename(), this);
        cerr <<"Class "<<formal_type<<" of formal parameter "
             <<param_name<<" is undefined.\n";
      } 
    }
    //check return type
    Class_ type = class_table->lookup(return_type);
    if(type == NULL && return_type != SELF_TYPE ){
      class_table->semant_error(c->get_filename(), this);
      cerr <<"Undefined return type "<<return_type<<" in method "<<name<<".\n";
    }
    //this will help to find multiply defined mehtod
//    class_table->class_table->addid(name, type);
    bool inherit_method = true;
    //check for method definition in parent class
    if(c != Object_class){
      Class_ parent_class = class_table->lookup(c->parent_name());
      if(parent_class)
        inherit_method =check_inherit_feature_def(c, class_tbl, parent_class);
    }
    if(inherit_method)
      class_table->class_table->addid(name, type);
  }
}

bool method_class::check_inherit_feature_def(Class_ c, void* class_tbl, Class_ parent_class)
{
  ClassTableP class_table = (ClassTableP) class_tbl;
  Symbol parent_class_name = parent_class->class_name();
  Feature parent_method = class_table->lookup_method(parent_class_name, name);
  //parent class does not define this method
  if(parent_method == NULL)
    return true;
  Formals parent_formals = parent_method->get_formals();
  if(return_type != parent_method->get_type()){
    class_table->semant_error(c->get_filename(), this);
    cerr <<"In redefined method "<<name<<", return type "<<return_type<<
        " is different from original return type "<<parent_method->get_type()
        <<".\n";
  } else if(formals->len() != parent_formals->len()){
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Incompatible number of formal parameters in redefined method "<<
        name<<".\n";
  } else {
    for(int i=formals->first(); formals->more(i); i=formals->next(i)){
      Symbol param_type = formals->nth(i)->get_type();
      Symbol inherit_param_type = parent_formals->nth(i)->get_type();
      if(param_type != inherit_param_type) {
        class_table->semant_error(c->get_filename(), this);
        cerr <<"In redefined method "<<name<<", parameter type "<<param_type<<
        " is different from original type "<<inherit_param_type <<".\n";
        return false;
      }
    }
    return true;  //return type, formals are all checked
  }
  return false; //return type or formal number is wrong
}

void attr_class::check_feature_def(Class_ c, void* class_tbl) 
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Class_ parent_class = class_table->lookup(c->parent_name());
  assert(parent_class);
  
  if (name == self )  {
    class_table->semant_error(c->get_filename(), this);
    cerr <<"'self' cannot be the name of an attribute.\n";
  } else if(class_table->attr_def_table->lookup(name)!=NULL){
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Attribute "<<name<<" is multiply defined in class.\n";
  } else if (check_inherit_feature_def(c, class_tbl, parent_class)){
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Attribute "<<name<<" is an attribute of an inherited class\n";
  } else {
    class_table->attr_def_table->addid(name, new Symbol(type_decl));
  } 
}

bool attr_class::check_inherit_feature_def(Class_ c, void* class_tbl, Class_ parent_class)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Symbol parent_class_name = parent_class->class_name();
//  Feature parent_method = class_table->lookup_method(parent_class_name, name);
  if(class_table->lookup_attribute(parent_class_name, name))
    return true;
  else
    return false;
}

void class__class :: collect_inherit_feature(Class_ c, void* class_tbl, 
                                            void*env_tbl, Class_ parent_class)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  while(1){
    if(parent_class == NULL)
      return;
    Features parent_features = parent_class->get_features();
    for(int i=parent_features->first(); parent_features->more(i); 
        i=parent_features->next(i))
    parent_features->nth(i)->collect_feature(this, class_tbl, (void *)env);
    if(parent_class == Object_class)
      return;
    else 
      parent_class = class_table->lookup(parent_class->parent_name());
  }
}

/* collect all correctly defined attribute */
void attr_class::collect_feature(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  Class_ type = class_table->lookup(type_decl);
  // SELF_TYPE is not in the class_table for lookup
/*  if(type == NULL && type_decl != SELF_TYPE ){
//    class_table->semant_error(c->get_filename(), this);
//    cerr <<"Class "<<type_decl<<" of attribute "<<name<<" is undefined.\n";
  }
  else if(name == self) {
//    class_table->semant_error(c->get_filename(), this);
//    cerr <<"'self' cannot be the name of an attribute.\n";
  } else
    env->addid(name, new Symbol(type_decl));
*/
  if( name != self ) //&& (type != NULL || type_decl == SELF_TYPE))
    env->addid(name, new Symbol(type_decl));
}

void attr_class::check_feature(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  /* If type_decl is SELF_TYPE, it could not be looked up */
  if(class_table->lookup(type_decl)== NULL && type_decl != SELF_TYPE ){
    /*error is reported in collect feature, no need to further report it*/
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Class "<<type_decl<<" of attribute "<<name<<" is undefined.\n";
    return;
  }
  Symbol init_type = init->check_expr(c, class_tbl, env_tbl);
  if( init_type == No_expr ) /* no need to further check if no initial expr*/
    return;
//  cout<< "INIT_TYPE is "<<init_type<<endl;
  if(class_table->Subtype(init_type, type_decl, c)){
    init->set_type(init_type);
  } else {
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Inferred type "<<init_type<<" of initialization of attribute "<<
        name<<" does not conform to declared type "<<type_decl<<".\n";
  }
}

void method_class::check_feature(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  // parameter will be in the scope
  env->enterscope();
  Symbol param_name, param_type;
  // formals are already checked before
  for(int i= formals->first(); formals->more(i); i=formals->next(i)){
    param_name = formals->nth(i)->param_name();
    param_type = formals->nth(i)->get_type();
    if(!env->probe(param_name))
      env->addid(param_name, new Symbol(param_type));
    else {
      class_table->semant_error(c->get_filename(), this);
      cerr <<"Formal paramter "<<param_name<<" is multiply defined.\n";
    }
  }
  Symbol method_type = expr->check_expr(c, class_tbl, env_tbl);
//  cout << "Attribute check type "<< method_type <<" "<<return_type<<endl;
//  if(method_type == SELF_TYPE || class_table->Subtype(method_type, return_type, c))
//    expr->set_type(method_type);
  if(!class_table->Subtype(method_type, return_type, c)) {
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Inferred return type "<<method_type<<" of method "<<
        name<<" does not conform to declared return type "<<return_type<<".\n";
  }
  //local params are not used outside
  env->exitscope();
}

Symbol assign_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  Symbol type;
  if(name == self){
    class_table->semant_error(c->get_filename(), this);
    cerr << "Cannot assign to 'self'.\n";
    type = SELF_TYPE;
  } else if ( env->lookup(name) == NULL ) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "Assignment to undeclared variable "<<name<<".\n";
    type = Object;
  } else
    type = *env->lookup(name);
  Symbol expr_type = expr->check_expr(c, class_tbl, env_tbl);
//  cout<<"check subtype "<<expr_type<<" "<<type<<endl;
  if(!class_table->Subtype(expr_type, type, c)) {
//    return expr_type;
   class_table->semant_error(c->get_filename(), this);
  cerr << "Type "<<expr_type<<" of assigned expression does not conform to declared type "<<type<<" of identifier "<<name<<".\n";
 }
  set_type(expr_type) ;
  return expr_type;
}

Symbol static_dispatch_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Symbol expr_type = expr->check_expr(c, class_tbl, env_tbl);
  Symbol return_type;
  if( type_name == SELF_TYPE ){
    class_table->semant_error(c->get_filename(), this);
    cerr <<"Static dispatch to SELF_TYPE\n";
    return Object;
  }
  Feature method = class_table->lookup_method(type_name, name);

  if(!class_table->Subtype(expr_type, type_name, c)){
    class_table->semant_error(c->get_filename(), this);
    cerr << "Expression type " << expr_type << " does not conform to decleared statis dispatch type "
         << type_name << ".\n";
    return Object; 
  }

  if( method == NULL ){
    class_table->semant_error(c->get_filename(), this);
    cerr << "Static dispatch to undefined method "<<name<<".\n"; 
    return Object;
  } else {
    //check formal
//    cout <<"Find type is "<<expr_type<<endl;
    Formals method_formals = method->get_formals();
    assert(method_formals);
  
   if(method_formals->len() != actual->len())  {
      class_table->semant_error(c->get_filename(), this);
      cerr << "Method "<<name<<" called with wrong number of arguments.\n";
      return method->get_type();
    }
    int i;  //iterator to check all formals and actuals
    for(i=actual->first(); actual->more(i); i=actual->next(i)){
      Symbol actual_expr_type = actual->nth(i)->
                                check_expr(c, class_tbl, env_tbl);
      Symbol formal_type = method_formals->nth(i)->get_type();
      Symbol param_name = method_formals->nth(i)->param_name();
      if(!class_table->Subtype(actual_expr_type, formal_type, c)){
        class_table->semant_error(c->get_filename(), this);
        cerr << "In call of method "<<name<<", type "<<actual_expr_type
           <<" of parameter "<<param_name<<" does not conform to declared type "
           <<formal_type<<".\n"; 
        return method->get_type();
      }
    }
    if( method->get_type() == SELF_TYPE ) {
      set_type(expr_type);
      return expr_type;
    }
    else {
      set_type(method->get_type());
      return method->get_type();
    }
  }
}

Symbol dispatch_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Symbol dispatch_class, expr_type = expr->check_expr(c, class_tbl, env_tbl);
  if( expr_type == SELF_TYPE )
    dispatch_class = c->class_name();
  else
    dispatch_class = expr_type;
  if(class_table->lookup(dispatch_class) == NULL ) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "Dispatch on undefined class "<<dispatch_class<<".\n";
    return Object;
  }
  Feature method = class_table->lookup_method(dispatch_class, name);
  if( method == NULL ){
    class_table->semant_error(c->get_filename(), this);
    cerr << "Dispatch to undefined method "<<name<<".\n"; 
    return Object;
  } else {
    Symbol method_return_type = method->get_type();
    if(class_table->lookup(method_return_type)==NULL 
      && method_return_type!=SELF_TYPE )  {
      method_return_type = Object;
    }

    //check formal
//    cout <<"Find type is "<<expr_type<<endl;
    Formals method_formals = method->get_formals();
    assert(method_formals);
  
    int i;  //iterator to check all formals and actuals
    for(i=actual->first(); actual->more(i); i=actual->next(i)){
      if(!method_formals->more(i)) {
        class_table->semant_error(c->get_filename(), this);
        cerr << "Method "<<name<<" called with wrong number of arguments.\n";
        return method_return_type;
      }
      Symbol actual_expr_type = actual->nth(i)->
                                check_expr(c, class_tbl, env_tbl);
      Symbol formal_type = method_formals->nth(i)->get_type();
      Symbol param_name = method_formals->nth(i)->param_name();
      if(!class_table->Subtype(actual_expr_type, formal_type, c)){
        class_table->semant_error(c->get_filename(), this);
        cerr << "In call of method "<<name<<", type "<<actual_expr_type
           <<" of parameter "<<param_name<<" does not conform to declared type "
           <<formal_type<<".\n"; 
        return method_return_type;
      }
    }
    if(method_formals->more(i)){
        class_table->semant_error(c->get_filename(), this);
        cerr << "Method "<<name<<" called with wrong number of arguments.\n";
        return method_return_type;
    }
    if( method->get_type() == SELF_TYPE ) {
      set_type(expr_type);
      return expr_type;
    }
    else {
      set_type(method->get_type());
      return method_return_type;
    }
  }
}

Symbol cond_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Symbol type1 = pred->check_expr(c, class_tbl, env_tbl);
  Symbol type2 = then_exp->check_expr(c, class_tbl, env_tbl);
  Symbol type3 = else_exp->check_expr(c, class_tbl, env_tbl);
  Symbol lub = class_table->lub(type2, type3, c);
  if( type1 == Bool ) 
    this->set_type(lub);
  else{
    class_table->semant_error(c->get_filename(), this);
    cerr << "Predicate of 'if' does not have type Bool.\n";
  }
  return lub;
}

Symbol loop_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = pred->check_expr(c, class_tbl, env_tbl);
  type2 = body->check_expr(c, class_tbl, env_tbl);

  if (type1 == Bool) {
    this->set_type(Object);
    return Object;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "Loop condition does not have type Bool.\n";
    return Object;
  }
}

Symbol typcase_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol return_type;
  ClassTableP class_table = (ClassTableP)class_tbl;
  expr->check_expr(c, class_tbl, env_tbl);
  Env *case_branch_match = new Env();
  case_branch_match->enterscope();
  int i = cases->first();
  return_type = cases->nth(i)->check_case_branch(c, class_tbl, env_tbl, (void *)case_branch_match);
  i = cases->next(i);
  while(cases->more(i)){
    Symbol branch_type=cases->nth(i)->check_case_branch(c, class_tbl, env_tbl,(void *) case_branch_match);
    return_type = class_table->lub(return_type, branch_type, c);
    i = cases->next(i);
  }
  set_type(return_type);
  delete case_branch_match;
  return return_type;
}

Symbol branch_class::check_case_branch(Class_ c, void* class_tbl, void* env_tbl, void *decl_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  Env * decl = (Env *)decl_tbl;
  if(name == self ){
    class_table->semant_error(c->get_filename(), this);
    cerr << "'self' bound in 'case'\n";
  }

  if(decl->lookup(type_decl)) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "Duplicate branch "<<type_decl<<" in case statement.\n";
  } else {
    decl->addid(type_decl, new Symbol(type_decl));
  }
  if(type_decl == SELF_TYPE ) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "Identifier "<<name<<" declared with type SELF_TYPE in case branch\n";
  } else if(class_table->lookup(type_decl) == NULL ) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "Class "<<type_decl<<" of case branch is undefined\n";
  }
  env->enterscope();
  env->addid(name, new Symbol(type_decl));
  Symbol return_type = expr->check_expr(c, class_tbl, env_tbl);
  env->exitscope();
  return return_type;
}

Symbol let_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  Env * env = (Env *)env_tbl;
  env->enterscope();
  if(class_table->lookup(type_decl) == NULL && type_decl != SELF_TYPE ){
    class_table->semant_error(c->get_filename(), this);
    cerr << "Class "<<type_decl<<" of let-bound identifier "<<identifier
         << " is undefined\n";
  }
  Symbol init_type = init->check_expr(c, class_tbl, env_tbl); 
  if (identifier == self ){
    class_table->semant_error(c->get_filename(), this);
    cerr << "'self' cannot be bound in a 'let' expression\n";
  } else { 
      if(init_type != No_expr
          && (class_table->lookup(type_decl)|| type_decl==SELF_TYPE) 
          &&  !class_table->Subtype(init_type, type_decl, c)) {
        class_table->semant_error(c->get_filename(), this);
        cerr<<"Inferred type "<<init_type<<" of initialization of "<<identifier
         <<" does not conform to identifier's declared type "<<type_decl<<"\n";
      } 
    env->addid(identifier, new Symbol(type_decl));
  }
  Symbol body_type = body->check_expr(c, class_tbl, env_tbl);
  env->exitscope();
  set_type(body_type);
  return body_type;
}

Symbol block_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol return_type;
  for (int i=body->first(); body->more(i); i= body->next(i)) 
    return_type = body->nth(i)->check_expr(c, class_tbl, env_tbl);
  set_type(return_type);
  return return_type;
}

Symbol new__class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  ClassTableP class_table = (ClassTableP)class_tbl;
  if(class_table->lookup(type_name) == NULL && type_name != SELF_TYPE ) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "no type in NEW\n";
    return Object;
  }
  set_type(type_name);
  return type_name;
}

Symbol isvoid_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type;
  type = e1->check_expr(c, class_tbl, env_tbl);
  this->set_type(Bool);
  return Bool;
}



Symbol plus_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  if (type1 == Int && type2 == Int ) {
    this->set_type(Int);
    return Int;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "non-Int arguments: "<<type1<<" + "<<type2<<".\n";
    return Int;
  }
} 

Symbol sub_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  if (type1 == Int && type2 == Int ) {
    this->set_type(Int);
    return Int;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "non-Int arguments: "<<type1<<" - "<<type2<<".\n";
    return Int;
  }
}

Symbol mul_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  if (type1 == Int && type2 == Int ) {
    this->set_type(Int);
    return Int;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "non-Int arguments: "<<type1<<" * "<<type2<<".\n";
    return Int;
  }
}

Symbol divide_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  if (type1 == Int && type2 == Int ) {
    this->set_type(Int);
    return Int;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "non-Int arguments: "<<type1<<" / "<<type2<<".\n";
    return Int;
  }
}

Symbol bool_const_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  this->set_type(Bool);
  return Bool;
}

Symbol neg_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type;
  type = e1->check_expr(c, class_tbl, env_tbl);
  if (type == Int) {
    this->set_type(Int);
    return Int;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "Argument of '~' has type "<<type<<" instead of Int.\n";
    return Int;
  }
}

Symbol comp_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type;
  type = e1->check_expr(c, class_tbl, env_tbl);
  if (type == Bool) {
    this->set_type(Bool);
    return Bool;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "Argument of 'not' has type "<<type<<" instead of Bool.\n";
    return Bool;
  }
}

Symbol lt_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  if (type1 == Int && type2 == Int ) {
    this->set_type(Bool);
    return Bool;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "non-Int arguments: "<<type1<<" < "<<type2<<".\n";
    return Bool;
  }
}

Symbol leq_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  if (type1 == Int && type2 == Int ) {
    this->set_type(Bool);
    return Bool;
  } else {
    ClassTableP class_table = (ClassTableP)class_tbl;
    class_table->semant_error(c->get_filename(), this);
    cerr << "non-Int arguments: "<<type1<<" <= "<<type2<<".\n";
    return Bool;
  }
}

Symbol eq_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Symbol type1, type2;
  type1 = e1->check_expr(c, class_tbl, env_tbl);
  type2 = e2->check_expr(c, class_tbl, env_tbl);
  ClassTableP class_table = (ClassTableP)class_tbl;
  if ( ((type1 == Int || type1 == Bool || type1 == Str) 
  || (type2 == Int || type2 == Bool || type2 == Str))
  && (type2 != type1 ) ) {
    class_table->semant_error(c->get_filename(), this);
    cerr << "Illegal comparison with a basic type.\n";
    return Bool;
  } else {
    this->set_type(Bool);
    return Bool;
  }
}

Symbol int_const_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  this->set_type(Int);
  return Int;
}


Symbol string_const_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  this->set_type(Str);
  return Str;
}

Symbol no_expr_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
//  this->set_type(No_expr);
  return No_expr;
}

Symbol object_class::check_expr(Class_ c, void* class_tbl, void* env_tbl)
{
  Env *env = (Env *)env_tbl;
  ClassTableP class_table = (ClassTableP)class_tbl;
  if(env->lookup(name)){
    this->set_type(*(env->lookup(name)));
    return *(env->lookup(name));
  } else if (name != self ){
    class_table->semant_error(c->get_filename(), this);
    cerr << "Undeclared identifier "<<name<<".\n";
    return Object;
  } else {
    this->set_type(SELF_TYPE);
    return SELF_TYPE;
  }
}


Class_ ClassTable::lookup(Symbol sym)
{
  return class_table->lookup(sym);
}

bool ClassTable::Subtype(Class_ child, Class_ parent)
{
  assert(child != NULL);
  assert(parent != NULL);

  if(child == parent)
    return true;
  Class_ parent_in_table = class_table->lookup(child->parent_name());
//  cout << parent_in_table->class_name() <<endl;
  while(parent_in_table){
    if(parent_in_table == child) {
      cout << "Cyclic Graph\n" <<endl;
      break;
    }
    if (parent_in_table == parent)
      return true;
    else if(parent_in_table != Object_class){
      parent_in_table = class_table->lookup(parent_in_table->parent_name());
    }
    else
      break;
  }
  return false;
}

bool ClassTable::Subtype(Symbol child_type, Symbol parent_type, Class_ c)
{
  if(child_type == SELF_TYPE && parent_type == SELF_TYPE)
    return true;
  else if( child_type == SELF_TYPE ) {
    Symbol class_type = c->class_name();
    return Subtype(class_type, parent_type);
  } else if( parent_type == SELF_TYPE )
    return false;
  else
    return Subtype(child_type, parent_type);
}

bool ClassTable::Subtype(Symbol child_name, Symbol parent_name)
{
  Class_ child = class_table->lookup(child_name);
  Class_ parent = class_table->lookup(parent_name);
  if(child == NULL || parent == NULL )
    return false;
  return this->Subtype(child, parent);
}

/* Return the Class name of the least upper bound Class */
Symbol ClassTable::lub(Symbol a, Symbol b)
{
  Class_ a_class = class_table->lookup(a);
  Class_ b_class = class_table->lookup(b);
  if(a_class == NULL || b_class == NULL)
    return Object;

  if(Subtype(a, b))
    return b;
  else if(Subtype(b, a))
    return a;

  Class_ a_parent = a_class; class_table->lookup(a_class->parent_name());
  Class_ b_parent = b_class; 
  while(1) { 
    a_parent = class_table->lookup(a_parent->parent_name());
    b_parent = class_table->lookup(b_parent->parent_name());

    if(a_parent == NULL || b_parent == NULL)
      return Object;

    if(Subtype(a_class, b_parent))
      return b_parent->class_name();
    else if(Subtype(b_class, a_parent))
      return a_parent->class_name();

    if(a_parent == Object_class || b_parent == Object_class)
      return Object;
  }
}

/* If SELF_TYPE is invovled in Class C */
Symbol ClassTable::lub(Symbol a, Symbol b, Class_ c)
{
  if(a == SELF_TYPE && b == SELF_TYPE)
    return SELF_TYPE;
  else if(a == SELF_TYPE )
    return lub(c->class_name(), b);
  else if(b == SELF_TYPE )
    return lub(a, c->class_name());
  else
    return lub(a, b);
}

Feature ClassTable::lookup_method(Symbol class_name, Symbol method_name)
{
  while(1) 
  {
    Class_ dispatch_class = this->lookup(class_name);
    if(dispatch_class == NULL)
      return NULL;
//    cout <<"find class "<<endl;
    Features features = dispatch_class->get_features();
    for(int i=features->first(); features->more(i); i=features->next(i))
    {
//      cout<<"inside loop\n";
      if((features->nth(i)->find_method(method_name)))
        return features->nth(i);
    }
    /* If not find in current class, find in parent class */
    if( dispatch_class != Object_class )
      class_name = dispatch_class->parent_name();
    else
      return NULL;
  }
  return NULL;
}

bool ClassTable::lookup_attribute(Symbol class_name, Symbol attr_name)
{
  while(1){
    Class_ lookup_class = lookup(class_name);
    if(lookup_class == NULL)
      return false;
    Features features = lookup_class->get_features();
    for(int i=features->first(); features->more(i); i=features->next(i))
    {
//      cout<<"inside loop\n";
      if((features->nth(i)->find_attribute(attr_name)))
        return true;
    }
    if( lookup_class != Object_class )
      class_name = lookup_class->parent_name();
    else
      return false;
  }
  return false;
}
