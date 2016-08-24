
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include "cgen.h"
#include "cgen_gc.h"
#include <stdio.h>
#include <stdlib.h>

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;
extern int cgen_optimize;

int box_ccnt = 0;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol 
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
//*****************************
// my static definition
//*****************************
static CgenNodeP root_class_nd;
static int class_tag = 0; //begin install from Object, so Object has tag 0
static CgenNodeP current_nd = NULL; //this global pointer is used in code gen

/* expr->code() could access CgenClassTable, and use SymbolTable */
static CgenClassTableP current_cgen = NULL; 

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


//  BoolConst is a class that implements code generation for operations
//  on the two booleans, which are given global names here.
BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void program_class::cgen(ostream &os) 
{
  // spim wants comments to start with '#'
  os << "# start of generated code\n";

  initialize_constants();
  CgenClassTable *codegen_classtable = new CgenClassTable(classes,os);

  os << "\n# end of generated code\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_load(char *dest_reg, int offset, char *source_reg, ostream& s)
{
  s << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")" 
    << endl;
}

static void emit_store(char *source_reg, int offset, char *dest_reg, ostream& s)
{
  s << SW << source_reg << " " << offset * WORD_SIZE << "(" << dest_reg << ")"
      << endl;
}

static void emit_load_imm(char *dest_reg, int val, ostream& s)
{ s << LI << dest_reg << " " << val << endl; }

static void emit_load_address(char *dest_reg, char *address, ostream& s)
{ s << LA << dest_reg << " " << address << endl; }

static void emit_partial_load_address(char *dest_reg, ostream& s)
{ s << LA << dest_reg << " "; }

static void emit_load_bool(char *dest, const BoolConst& b, ostream& s)
{
  emit_partial_load_address(dest,s);
  b.code_ref(s);
  s << endl;
}

static void emit_load_string(char *dest, StringEntry *str, ostream& s)
{
  emit_partial_load_address(dest,s);
  str->code_ref(s);
  s << endl;
}

static void emit_load_int(char *dest, IntEntry *i, ostream& s)
{
  emit_partial_load_address(dest,s);
  i->code_ref(s);
  s << endl;
}

static void emit_move(char *dest_reg, char *source_reg, ostream& s)
{ s << MOVE << dest_reg << " " << source_reg << endl; }

static void emit_neg(char *dest, char *src1, ostream& s)
{ s << NEG << dest << " " << src1 << endl; }

static void emit_add(char *dest, char *src1, char *src2, ostream& s)
{ s << ADD << dest << " " << src1 << " " << src2 << endl; }

static void emit_addu(char *dest, char *src1, char *src2, ostream& s)
{ s << ADDU << dest << " " << src1 << " " << src2 << endl; }

static void emit_addiu(char *dest, char *src1, int imm, ostream& s)
{ s << ADDIU << dest << " " << src1 << " " << imm << endl; }

static void emit_div(char *dest, char *src1, char *src2, ostream& s)
{ s << DIV << dest << " " << src1 << " " << src2 << endl; }

static void emit_mul(char *dest, char *src1, char *src2, ostream& s)
{ s << MUL << dest << " " << src1 << " " << src2 << endl; }

static void emit_sub(char *dest, char *src1, char *src2, ostream& s)
{ s << SUB << dest << " " << src1 << " " << src2 << endl; }

static void emit_sll(char *dest, char *src1, int num, ostream& s)
{ s << SLL << dest << " " << src1 << " " << num << endl; }

static void emit_jalr(char *dest, ostream& s)
{ s << JALR << "\t" << dest << endl; }

static void emit_jal(char *address,ostream &s)
{ s << JAL << address << endl; }

static void emit_return(ostream& s)
{ s << RET << endl; }

static void emit_gc_assign(ostream& s)
{ s << JAL << "_GenGC_Assign" << endl; }

static void emit_disptable_ref(Symbol sym, ostream& s)
{  s << sym << DISPTAB_SUFFIX; }

static void emit_init_ref(Symbol sym, ostream& s)
{ s << sym << CLASSINIT_SUFFIX; }

static void emit_label_ref(int l, ostream &s)
{ s << "label" << l; }

static void emit_protobj_ref(Symbol sym, ostream& s)
{ s << sym << PROTOBJ_SUFFIX; }

static void emit_method_ref(Symbol classname, Symbol methodname, ostream& s)
{ s << classname << METHOD_SEP << methodname; }

static void emit_label_def(int l, ostream &s)
{
  emit_label_ref(l,s);
  s << ":" << endl;
}

static void emit_beqz(char *source, int label, ostream &s)
{
  s << BEQZ << source << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_beq(char *src1, char *src2, int label, ostream &s)
{
  s << BEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bne(char *src1, char *src2, int label, ostream &s)
{
  s << BNE << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bleq(char *src1, char *src2, int label, ostream &s)
{
  s << BLEQ << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blt(char *src1, char *src2, int label, ostream &s)
{
  s << BLT << src1 << " " << src2 << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_blti(char *src1, int imm, int label, ostream &s)
{
  s << BLT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_bgti(char *src1, int imm, int label, ostream &s)
{
  s << BGT << src1 << " " << imm << " ";
  emit_label_ref(label,s);
  s << endl;
}

static void emit_branch(int l, ostream& s)
{
  s << BRANCH;
  emit_label_ref(l,s);
  s << endl;
}

//
// Push a register on the stack. The stack grows towards smaller addresses.
//
static void emit_push(char *reg, ostream& str)
{
  emit_store(reg,0,SP,str);
  emit_addiu(SP,SP,-4,str);
}
//***********************************
// TODO: New Implementation: Push stack
//***********************************
static void emit_push_stack(ostream & str)
{
  emit_addiu(SP,  SP, -12,  str);   //push stack
  emit_store(FP,  3,  SP,   str);   //store $fp
  emit_store(SELF,2,  SP,   str);   //store $s0, self
  emit_store(RA,  1,  SP,   str);   //store $ra
  emit_addiu(FP,  SP, 4,    str);   //new $fp
}

static void emit_pop_return(ostream & str )
{
  emit_load(FP,   3,  SP, str);
  emit_load(SELF, 2,  SP, str);
  emit_load(RA,   1,  SP, str);
  emit_addiu(SP,  SP, 12, str);
  emit_return(str);
}

static void emit_pop_return(int argc, ostream & str )
{ 
  emit_load(FP,   3,  SP, str);
  emit_load(SELF, 2,  SP, str);
  emit_load(RA,   1,  SP, str);
  emit_addiu(SP,  SP, 12 + argc*4, str);
  emit_return(str);
}


//
// Fetch the integer value in an Int object.
// Emits code to fetch the integer value of the Integer object pointed
// to by register source into the register dest
//
static void emit_fetch_int(char *dest, char *source, ostream& s)
{ emit_load(dest, DEFAULT_OBJFIELDS, source, s); }

//
// Emits code to store the integer value contained in register source
// into the Integer object pointed to by dest.
//
static void emit_store_int(char *source, char *dest, ostream& s)
{ emit_store(source, DEFAULT_OBJFIELDS, dest, s); }


static void emit_test_collector(ostream &s)
{
  emit_push(ACC, s);
  emit_move(ACC, SP, s); // stack end
  emit_move(A1, ZERO, s); // allocate nothing
  s << JAL << gc_collect_names[cgen_Memmgr] << endl;
  emit_addiu(SP,SP,4,s);
  emit_load(ACC,0,SP,s);
}

static void emit_gc_check(char *source, ostream &s)
{
  if (source != (char*)A1) emit_move(A1, source, s);
  s << JAL << "_gc_check" << endl;
}


///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type StringEntry.  StringEntry methods are defined both for String
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream& s)
{
  s << STRCONST_PREFIX << index;
}

//
// Emit code for a constant String.
// You should fill in the code naming the dispatch table.
//

void StringEntry::code_def(ostream& s, int stringclasstag)
{
  IntEntryP lensym = inttable.add_int(len);

  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s  << LABEL                                             // label
      << WORD << stringclasstag << endl                                 // tag
      << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len+4)/4) << endl // size
      << WORD;


 /***** Add dispatch information for class String ******/
  emit_disptable_ref(Str, s);

      s << endl;                                              // dispatch table
      s << WORD;  lensym->code_ref(s);  s << endl;            // string length
  emit_string_constant(s,str);                                // ascii string
  s << ALIGN;                                                 // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the 
// stringtable.
//
void StrTable::code_string_table(ostream& s, int stringclasstag)
{  
  for (List<StringEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,stringclasstag);
}

//
// Ints
//
void IntEntry::code_ref(ostream &s)
{
  s << INTCONST_PREFIX << index;
}

//
// Emit code for a constant Integer.
// You should fill in the code naming the dispatch table.
//

void IntEntry::code_def(ostream &s, int intclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                // label
      << WORD << intclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl  // object size
      << WORD; 

 /***** Add dispatch information for class Int ******/
  emit_disptable_ref(Int, s);

      s << endl;                                          // dispatch table
      s << WORD << str << endl;                           // integer value
}


//
// IntTable::code_string_table
// Generate an Int object definition for every Int constant in the
// inttable.
//
void IntTable::code_string_table(ostream &s, int intclasstag)
{
  for (List<IntEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s,intclasstag);
}


//
// Bools
//
BoolConst::BoolConst(int i) : val(i) { assert(i == 0 || i == 1); }

void BoolConst::code_ref(ostream& s) const
{
  s << BOOLCONST_PREFIX << val;
}
  
//
// Emit code for a constant Bool.
// You should fill in the code naming the dispatch table.
//

void BoolConst::code_def(ostream& s, int boolclasstag)
{
  // Add -1 eye catcher
  s << WORD << "-1" << endl;

  code_ref(s);  s << LABEL                                  // label
      << WORD << boolclasstag << endl                       // class tag
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl   // object size
      << WORD;

 /***** Add dispatch information for class Bool ******/
  emit_disptable_ref(Bool, s);

      s << endl;                                            // dispatch table
      s << WORD << val << endl;                             // value (0 or 1)
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//***************************************************
//
//  Emit code to start the .data segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_data()
{
  Symbol main    = idtable.lookup_string(MAINNAME);
  Symbol string  = idtable.lookup_string(STRINGNAME);
  Symbol integer = idtable.lookup_string(INTNAME);
  Symbol boolc   = idtable.lookup_string(BOOLNAME);

  str << "\t.data\n" << ALIGN;
  //
  // The following global names must be defined first.
  //
  str << GLOBAL << CLASSNAMETAB << endl;
  str << GLOBAL; emit_protobj_ref(main,str);    str << endl;
  str << GLOBAL; emit_protobj_ref(integer,str); str << endl;
  str << GLOBAL; emit_protobj_ref(string,str);  str << endl;
  str << GLOBAL; falsebool.code_ref(str);  str << endl;
  str << GLOBAL; truebool.code_ref(str);   str << endl;
  str << GLOBAL << INTTAG << endl;
  str << GLOBAL << BOOLTAG << endl;
  str << GLOBAL << STRINGTAG << endl;

  //
  // We also need to know the tag of the Int, String, and Bool classes
  // during code generation.
  //
  str << INTTAG << LABEL
      << WORD << intclasstag << endl;
  str << BOOLTAG << LABEL 
      << WORD << boolclasstag << endl;
  str << STRINGTAG << LABEL 
      << WORD << stringclasstag << endl;    
}


//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_text()
{
  str << GLOBAL << HEAP_START << endl
      << HEAP_START << LABEL 
      << WORD << 0 << endl
      << "\t.text" << endl
      << GLOBAL;
  emit_init_ref(idtable.add_string("Main"), str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Int"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("String"),str);
  str << endl << GLOBAL;
  emit_init_ref(idtable.add_string("Bool"),str);
  str << endl << GLOBAL;
  emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
  str << endl;
}

void CgenClassTable::code_bools(int boolclasstag)
{
  falsebool.code_def(str,boolclasstag);
  truebool.code_def(str,boolclasstag);
}

void CgenClassTable::code_select_gc()
{
  //
  // Generate GC choice constants (pointers to GC functions)
  //
  str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
  str << "_MemMgr_INITIALIZER:" << endl;
  str << WORD << gc_init_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
  str << "_MemMgr_COLLECTOR:" << endl;
  str << WORD << gc_collect_names[cgen_Memmgr] << endl;
  str << GLOBAL << "_MemMgr_TEST" << endl;
  str << "_MemMgr_TEST:" << endl;
  str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}


//********************************************************
//
// Emit code to reserve space for and initialize all of
// the constants.  Class names should have been added to
// the string table (in the supplied code, is is done
// during the construction of the inheritance graph), and
// code for emitting string constants as a side effect adds
// the string's length to the integer table.  The constants
// are emmitted by running through the stringtable and inttable
// and producing code for each entry.
//
//********************************************************

void CgenClassTable::code_constants()
{
  //
  // Add constants that are required by the code generator.
  //
  stringtable.add_string("");
  inttable.add_string("0");

  stringtable.code_string_table(str,stringclasstag);
  inttable.code_string_table(str,intclasstag);
  code_bools(boolclasstag);
}

//**********************
// Emit code for class_nameTable, emit from Object class to all children
//**********************

void CgenClassTable::code_class_nameTab()
{
  str<<CLASSNAMETAB<<LABEL;
  for(List<CgenNode> *l = nds; l; l = l->tl()) 
    if(l->hd()->get_name() == Object ){
      root_class_nd = l->hd();
      break;
    }
  
  code_class_nameTab(root_class_nd);
}

void CgenClassTable::code_class_nameTab(CgenNodeP nd)
{
  assert(nd);
  //****************************************
  // build attr_name_table and method_table in this pass
  //****************************************
  nd->set_feature_table();
  Symbol class_name = nd->get_name();
  StringEntry *strEntry = stringtable.lookup_string(class_name->get_string());
  str<<WORD;
  strEntry->code_ref(str);
  str<<endl;

  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl()){
    code_class_nameTab(child->hd());
  }
}

void CgenClassTable::code_class_tag(CgenNodeP nd, int level)
{
  assert(nd);
  nd->class_tag = class_tag ++;
  nd->class_inherit_level = level;
  Symbol class_name = nd->get_name();
  if(class_name == Int)
    intclasstag = nd->class_tag;
  if(class_name == Str)
    stringclasstag = nd->class_tag;
  if(class_name == Bool)
    boolclasstag = nd->class_tag;

  //depth first, build class tag for all classes
  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl()){
    code_class_tag(child->hd(), level+1);
  }
  nd->class_tag_coverage = class_tag - 1;
}


//*****************************
// Emit code for object Table
//*****************************

void CgenClassTable::code_class_objTab(){
  str<<CLASSOBJTAB<<LABEL;
  code_class_objTab(root_class_nd);
}

void CgenClassTable::code_class_objTab(CgenNodeP nd)
{
  Symbol class_name = nd->get_name();
  str << WORD;
  emit_protobj_ref(class_name, str);
  str << endl;
  str << WORD;
  emit_init_ref(class_name, str);
  str << endl;
  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl()){
    code_class_objTab(child->hd());
  }
}

//**********************************
// Emit code for dispatch table, not easy job
//**********************************

void CgenClassTable::code_dispatch_table_parent(CgenNodeP nd)
{
  Features features = nd->get_features();
  for(int i=features->first(); features->more(i); i= features->next(i)) {
    Feature f = features->nth(i);
    if(f->is_method() && !child_methods->probe(f->get_name())){
      //dispatch the last override one
      child_methods->addid(f->get_name(), new Symbol(nd->get_name()));
    }
  }

  CgenNodeP parent = nd->get_parentnd();
  if(parent != NULL)
    code_dispatch_table_parent(parent);

//  Features features = nd->get_features();
  for(int i=features->first(); features->more(i); i= features->next(i)) {
    Feature f = features->nth(i);
    //one method only dispatch one time
    if(f->is_method() && !dispatched_methods->probe(f->get_name())){
      //if child class override this methods, only dispatch the last override
      Symbol *class_name = child_methods->probe(f->get_name());
      if(class_name)
        str << WORD <<*class_name<<"." <<f->get_name() << endl;
      else
        str << WORD <<nd->get_name()<<"." <<f->get_name() << endl;
      dispatched_methods->addid(f->get_name(), new Symbol(nd->get_name()));
    }
  }
}

void CgenClassTable::code_dispatch_table(CgenNodeP nd)
{
  emit_disptable_ref(nd->get_name(), str);
  str<<LABEL;

  child_methods->enterscope();
  dispatched_methods->enterscope();

  code_dispatch_table_parent(nd);

  child_methods->exitscope();
  dispatched_methods->exitscope();

  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl()){
     code_dispatch_table(child->hd());
  }
}

/*
void CgenClassTable::code_class_protObj()
{
}*/


void CgenClassTable::code_class_protObj(CgenNodeP nd)
{
  str << WORD << "-1" << endl;
//  nd->set_attr_name_table();
  str << nd->get_name() << PROTOBJ_SUFFIX << LABEL;
  str << WORD << nd->class_tag << endl;
  int size = DEFAULT_OBJFIELDS + nd->total_attr_num;
  str << WORD << size << endl;
  str << WORD << nd->get_name() << DISPTAB_SUFFIX << endl;
  //initialize all attribute in the prototype object
  nd->init_attr(nd, str);

  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl())
    code_class_protObj(child->hd());
}

//******************************************
//emit initializer for all classes,
//treat initializer similarly as methods
//******************************************
void CgenClassTable::code_class_init(CgenNodeP nd)
{
  current_nd = nd;
  str << nd->get_name() << CLASSINIT_SUFFIX << LABEL;
  // all initilizer have one argument passed in, $a0
  emit_push_stack(str);

  emit_move(SELF, ACC, str);  //get argument to self, $s0
  if(nd != root())  //run parent class initialization first
    str << JAL << nd->get_parentnd()->get_name() << CLASSINIT_SUFFIX << endl;

  //in initialization, expr may be a let_expr, pos is used for local variable
  pos = 1;   
  if(!nd->basic()) {  //initialize all attributes
    Features f = nd->get_features();
    for(int i=f->first(); f->more(i); i=f->next(i)){
      Expression e = f->nth(i)->get_init();
      // this feature is an attribute, and there is expression for assignment
      if(e && e->get_type() != NULL && e->get_type() != No_type) { 
        e->code(str);
        int attr_num = *nd->attr_name_table->probe(f->nth(i)->get_name());
        emit_store(ACC, attr_num+DEFAULT_OBJFIELDS, SELF, str);
        if(cgen_Memmgr == GC_GENGC) {
          // cout << "GC_ENABLED\n";
          emit_addiu(A1, SELF, (attr_num+DEFAULT_OBJFIELDS)*4, str);
          emit_gc_assign(str);
        }
      }
    }
  }
  emit_move(ACC, SELF, str);
  // pop stack
  emit_pop_return(str);

  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl())
    code_class_init(child->hd());
}

//******************************************
// Emit all methods
//******************************************

void CgenClassTable::code_class_methods(CgenNodeP nd)
{
  if(!nd->basic()) { //skip for Object, IO, Int, Bool, Str
    current_nd = nd;  //set current CgenNodeP, used to search attribute
    Features f = nd->get_features();
    for( int i = f->first(); f->more(i); i = f->next(i) ){
      if(!f->nth(i)->is_method())
        continue;
      Feature method = f->nth(i);
      method_class * m = (method_class *)method;
      Formals formals = m->formals;
      //collect formal id in a environment table
      formal_table->enterscope();
      formal_type->enterscope();
      argc = formals->len();
      for(int i= formals->first(); formals->more(i); i=formals->next(i)) {
        formal_table->addid( ( (formal_class *) formals->nth(i) )->name, 
                              new int(i) );
        formal_type->addid( ( (formal_class *) formals->nth(i) )->name,
                              new Symbol(formals->nth(i)->get_type()) );
      }

      str << nd->get_name() << "." << method->get_name() << LABEL;
      emit_push_stack(str);
      emit_move(SELF, ACC, str);
      current_cgen->pos = 1;  //this is used for local new location
      method->method_expr()->code(str);
      emit_pop_return(formals->len(), str);      
      formal_table->exitscope();
      formal_type->exitscope();
    }
  }
  for(List<CgenNode> *child = nd->get_children(); child; child = child->tl())
    code_class_methods(child->hd());
}

CgenClassTable::CgenClassTable(Classes classes, ostream& s) : nds(NULL) , str(s)
{
   current_cgen = this;
   //those values are overwrite later
   stringclasstag = 4 /* Change to your String class tag here */;
   intclasstag =    2 /* Change to your Int class tag here */;
   boolclasstag =   3 /* Change to your Bool class tag here */;

   enterscope();
   if (cgen_debug) cout << "Building CgenClassTable" << endl;
   install_basic_classes();
   install_classes(classes);
   build_inheritance_tree();

   code();
   exitscope();
}

void CgenClassTable::install_basic_classes()
{

// The tree package uses these globals to annotate the classes built below.
  //curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");

//
// A few special class names are installed in the lookup table but not
// the class list.  Thus, these classes exist, but are not part of the
// inheritance hierarchy.
// No_class serves as the parent of Object and the other special classes.
// SELF_TYPE is the self class; it cannot be redefined or inherited.
// prim_slot is a class known to the code generator.
//
  addid(No_class,
	new CgenNode(class_(No_class,No_class,nil_Features(),filename),
			    Basic,this));
  addid(SELF_TYPE,
	new CgenNode(class_(SELF_TYPE,No_class,nil_Features(),filename),
			    Basic,this));
  addid(prim_slot,
	new CgenNode(class_(prim_slot,No_class,nil_Features(),filename),
			    Basic,this));

// 
// The Object class has no parent class. Its methods are
//        cool_abort() : Object    aborts the program
//        type_name() : Str        returns a string representation of class name
//        copy() : SELF_TYPE       returns a copy of the object
//
// There is no need for method bodies in the basic classes---these
// are already built in to the runtime system.
//
  install_class(
   new CgenNode(
    class_(Object, 
	   No_class,
	   append_Features(
           append_Features(
           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
           single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	   filename),
    Basic,this));

// 
// The IO class inherits from Object. Its methods are
//        out_string(Str) : SELF_TYPE          writes a string to the output
//        out_int(Int) : SELF_TYPE               "    an int    "  "     "
//        in_string() : Str                    reads a string from the input
//        in_int() : Int                         "   an int     "  "     "
//
   install_class(
    new CgenNode(
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
	   filename),	    
    Basic,this));

//
// The Int class has no methods and only a single attribute, the
// "val" for the integer. 
//
   install_class(
    new CgenNode(
     class_(Int, 
	    Object,
            single_Features(attr(val, prim_slot, no_expr())),
	    filename),
     Basic,this));

//
// Bool also has only the "val" slot.
//
    install_class(
     new CgenNode(
      class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename),
      Basic,this));

//
// The class Str has a number of slots and operations:
//       val                                  ???
//       str_field                            the string itself
//       length() : Int                       length of the string
//       concat(arg: Str) : Str               string concatenation
//       substr(arg: Int, arg2: Int): Str     substring
//       
   install_class(
    new CgenNode(
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
	     filename),
        Basic,this));

}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_class(CgenNodeP nd)
{
  Symbol name = nd->get_name();

  if (probe(name))
    {
      return;
    }

  // The class name is legal, so add it to the list of classes
  // and the symbol table.
  nds = new List<CgenNode>(nd,nds);
  addid(name,nd);
}

void CgenClassTable::install_classes(Classes cs)
{
  for(int i = cs->first(); cs->more(i); i = cs->next(i))
    install_class(new CgenNode(cs->nth(i),NotBasic,this));
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree()
{
  for(List<CgenNode> *l = nds; l; l = l->tl())
      set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd)
{
  CgenNode *parent_node = probe(nd->get_parent());
  nd->set_parentnd(parent_node);
  parent_node->add_child(nd);
}

void CgenNode::add_child(CgenNodeP n)
{
  children = new List<CgenNode>(n,children);
}

void CgenNode::set_parentnd(CgenNodeP p)
{
  assert(parentnd == NULL);
  assert(p != NULL);
  parentnd = p;
}



void CgenClassTable::code()
{
  code_class_tag(root(), 0);

  if (cgen_debug) cout << "coding global data" << endl;
  code_global_data();

  if (cgen_debug) cout << "choosing gc" << endl;
  code_select_gc();

  if (cgen_debug) cout << "coding constants" << endl;
  code_constants();

//                 Add your code to emit
//                   - prototype objects
//                   - class_nameTab
//                   - dispatch tables
//
  code_class_nameTab();
  code_class_objTab();
  
  child_methods = new SymbolTable<Symbol, Symbol>();
  dispatched_methods = new SymbolTable<Symbol, Symbol>();

  code_dispatch_table(root());
  code_class_protObj(root());

  if (cgen_debug) cout << "coding global text" << endl;
  code_global_text();

//                 Add your code to emit
//                   - object initializer
//                   - the class methods
//                   - etc...
  formal_table = new SymbolTable<Symbol, int> ();
  formal_table->enterscope(); //initiate formal table scope, initiation use it
  let_table = new SymbolTable<Symbol, int>();
  let_table->enterscope(); //initiate let table scope, let table use it
  formal_type = new SymbolTable<Symbol, Symbol>();
  formal_type->enterscope();
  let_type = new SymbolTable<Symbol, Symbol>();
  let_type->enterscope();

  code_class_init(root());
  code_class_methods(root());

  str << "\n# My code gen stop here\n";
  formal_table->exitscope();
  let_table->exitscope();
  formal_type->exitscope();
  let_type->exitscope();
}


CgenNodeP CgenClassTable::root()
{
   return probe(Object);
}


///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) :
   class__class((const class__class &) *nd),
   parentnd(NULL),
   children(NULL),
   basic_status(bstatus)
{ 
   stringtable.add_string(name->get_string());          // Add class name to string table
}

int CgenNode::attr_num(CgenNodeP nd)
{
  int total_attr_num = 0;
  CgenNodeP parent = nd->get_parentnd();
  if(parent != NULL)
    total_attr_num = attr_num(parent);
  Features f = nd->get_features();
  for(int i=f->first(); f->more(i); i=f->next(i))
    if(!f->nth(i)->is_method())
      total_attr_num++;
  return total_attr_num;
}

void CgenNode::init_attr(CgenNodeP nd, ostream &o)
{
  CgenNodeP parent = nd->get_parentnd();
  if(parent)
    init_attr(parent, o);
  
  Features features = nd->get_features();
  for(int i=features->first(); features->more(i); i=features->next(i)){
    Feature f = features->nth(i);
    if (f->is_method())
      continue;
    Symbol type = f->get_type();
    if(type == prim_slot)
      o << WORD << "0\n";
    else if(type == Int ) {
      if(cgen_optimize)
        o << WORD << "0\n";
      else {
        o << WORD;
        inttable.lookup_string("0")->code_ref(o);
        o << endl;
      }
    } else if (type == Str) {
      o << WORD;
      stringtable.lookup_string("")->code_ref(o);
      o << endl;
    } else if (type == Bool) {
      o << WORD << BOOLCONST_PREFIX << 0 <<endl;
    } else {
      o << WORD << "0\n";
    }
  }
  
}

void CgenNode::set_feature_table()
{
  attr_name_table = new SymbolTable<Symbol, int>();
  attr_name_table->enterscope();
  total_attr_num = 0;

  method_table = new SymbolTable<Symbol, int>();
  method_table->enterscope();
  total_method_num = 0;

  method_class_table = new SymbolTable<Symbol, Symbol>();
  method_class_table->enterscope();

  attr_type_table = new SymbolTable<Symbol, Symbol>();
  attr_type_table->enterscope();

  CgenNodeP parent = get_parentnd();
  Features f = get_features();
  for(int i=f->first(); f->more(i); i=f->next(i)) {
    if(f->nth(i)->is_method() && 
        !method_class_table->lookup(f->nth(i)->get_name()) )
      method_class_table->addid(f->nth(i)->get_name(), new Symbol(get_name()));
  }

  if(parent)
    set_feature_table(this, parent);

//  Features f = get_features();
  for(int i=f->first(); f->more(i); i=f->next(i)) {
    if(!f->nth(i)->is_method()) { 
      attr_name_table->addid(f->nth(i)->get_name(), new int(total_attr_num++)); 
      attr_type_table->addid(f->nth(i)->get_name(), 
                            new Symbol(f->nth(i)->get_type()));
    } else {
      //if parent does not have such method, insert in method table
      if(!method_table->lookup(f->nth(i)->get_name()))
        method_table->addid(f->nth(i)->get_name(), new int(total_method_num++));
    }
  }
}

void CgenNode::set_feature_table(CgenNodeP nd, CgenNodeP parent)
{
  CgenNodeP grand_parent = parent->get_parentnd();
  Features f = parent->get_features();
  Symbol p_name = parent->get_name();
  for(int i=f->first(); f->more(i); i=f->next(i)) {
    if(f->nth(i)->is_method() && 
        !nd->method_class_table->lookup(f->nth(i)->get_name()) )
      nd->method_class_table->addid(f->nth(i)->get_name(), new Symbol(p_name));
  }
  if(grand_parent)
    set_feature_table(nd, grand_parent);
  for(int i=f->first(); f->more(i); i=f->next(i)) {
    if(!f->nth(i)->is_method()) {
      nd->attr_name_table->addid(f->nth(i)->get_name(), 
                                new int(nd->total_attr_num++));
      nd->attr_type_table->addid(f->nth(i)->get_name(),
                                new Symbol(f->nth(i)->get_type()));
    }
    else {
      if(!method_table->lookup(f->nth(i)->get_name()))
        nd->method_table->addid(f->nth(i)->get_name(), 
                                new int(total_method_num++));
    }
  }
}



//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************

int label_cur_num = 0;
// int boxing, put raw int in 4(SP), return obj pointer to ACC
int int_flag_global = 0;

void boxing( ostream &s ) {
  box_ccnt += 4;
  emit_load_int(ACC, inttable.lookup_string("0"),s );
  emit_jal("Object.copy", s);
  emit_load(T1, 1, SP, s);
  emit_store(T1, 3, ACC, s);
  s << "# box_ccnt :" << box_ccnt << endl;
}


void assign_class::code(ostream &s) {
//  cout << "assign_class. \n";
  Symbol *type_defined = current_cgen->let_type->lookup(name);
  int int_flag_rec;
  if(cgen_optimize && expr->get_type() == Int){
    int_flag_rec = int_flag_global;
    int_flag_global = 0;

    if(!type_defined )
      type_defined = current_cgen->formal_type->probe(name);
    if (! type_defined )
      type_defined = current_nd->attr_type_table->probe(name);
    if (! type_defined ) {
      cout << get_line_number();
      cout << "Wrong HERE Oh HERE\n";
    }
    if( *type_defined == Object ) {
        int_flag_global = 1;
    }
   
  }

  expr->code(s);

  int num = 0;
  assert(current_nd);
  int *offset = current_cgen->let_table->lookup(name);
  if(offset)  { //first find in let binding table
    int pos = *offset;
    emit_store(ACC, -pos, FP, s);
  } else if(current_cgen->formal_table->probe(name))  { //find in argument
    offset = current_cgen->formal_table->probe(name);
    emit_store(ACC, current_cgen->argc -1 - *offset + 3, FP, s);
  } else if( current_nd->attr_name_table->probe(name) ){
    int *attr_num = current_nd->attr_name_table->probe(name);
    emit_store(ACC, *attr_num + DEFAULT_OBJFIELDS, SELF, s);
    if( cgen_Memmgr == GC_GENGC ) {
        emit_addiu(A1, SELF, (*attr_num + DEFAULT_OBJFIELDS)*4, s);
        emit_gc_assign(s);
    }
  } else
    s << "#TODO: find ID fail\n";
  
  if (cgen_optimize && expr->get_type() == Int && *type_defined == Int) {
    assert(!int_flag_global);
    if (int_flag_rec == 1) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
    int_flag_global = int_flag_rec;
  }   
}

void static_dispatch_class::code(ostream &s) {
//  cout << "static dispatch . \n";
  int int_flag_rec = int_flag_global;
 
  Symbol method_def_class = *current_cgen->probe(type_name)->method_class_table
      ->probe(name);
  Features f = ( (class class__class *)
                current_cgen->probe(method_def_class) )->features;
  method_class *method = NULL;
  for(int i=0; i<f->len(); i++){
    if(f->nth(i)->is_method() && f->nth(i)->get_name() == name ) {
      method = (method_class *)f->nth(i);
    }
  }
 
  for(int i=actual->first(); actual->more(i); i=actual->next(i)){
    if (cgen_optimize) {
      if(actual->nth(i)->get_type() == Int
      &&( (method_def_class==IO && !strcmp(name->get_string(), "out_int"))
        ||(method_def_class==Str && !strcmp(name->get_string(), "substr"))
        || method->formals->nth(i)->get_type() == Object ) ) {
        cout<<"argument boxing\n";
        int_flag_global = 1;
//        boxing(s);
//        emit_store(ACC, 1, SP, s);
      }
    }

    actual->nth(i)->code(s);
    int_flag_global = 0;
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos ++;
  }

  expr->code(s);
  if ((cgen_optimize) && (expr->get_type() == Int)) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      s << "# dispatch boxing" << endl;
      cout << "dispatch boxing.\n";
      boxing(s);
      emit_addiu(SP, SP, 4, s);
  }

  //run time system check, check if expr is pointed to zero
  int label = label_cur_num++;
  emit_bne(ACC, ZERO, label, s);
  // emit abort code here, get filename and line number
  char *filename = ((class__class *)current_nd)->filename->get_string();
  emit_load_string(ACC, stringtable.lookup_string(filename),s);
  emit_load_imm(T1, get_line_number(), s);
  emit_jal("_dispatch_abort", s);
  
  emit_label_def(label, s);
  s << LA << T1 << " " <<type_name << DISPTAB_SUFFIX <<endl;
  
  //get entry in dispatch table
  CgenNodeP nd = current_cgen->probe(type_name);
  int *disp_entry = nd->method_table->probe(name);
  emit_load(T1, *disp_entry, T1, s);
  emit_jalr(T1, s); 
  current_cgen->pos -= actual->len();
  if ( cgen_optimize ) {
     if (  (method_def_class == IO && !strcmp(name->get_string(), "in_int"))
      || (!strcmp(name->get_string(), "copy")  && expr->get_type() == Int)
      || (method_def_class == Str && !strcmp(name->get_string(),"length"))
      ) {
        if (int_flag_rec == 0){
          emit_load(ACC, 3, ACC, s);
          box_ccnt += 1;
        }
      } else {
        if (method->return_type == Int && int_flag_rec == 1){
          emit_store(ACC, 0, SP, s);
          emit_addiu(SP, SP, -4, s);
          boxing(s);
          emit_addiu(SP, SP, 4, s);
        }
      }
  }
  int_flag_global = int_flag_rec;
}

void dispatch_class::code(ostream &s) {
//  cout << "dispatch class. \n";
  //first, find this method
//  cout<<"here\n";
  int int_flag_rec = int_flag_global;
  
  Symbol expr_type = expr->get_type();
  if(expr_type == SELF_TYPE || expr_type == NULL)
    expr_type = current_nd->get_name();
//  cout << expr_type << endl;
  Symbol method_def_class = *current_cgen->probe(expr_type)->method_class_table
      ->probe(name);
  Features f = ( (class class__class *)
                current_cgen->probe(method_def_class) )->features;
  method_class *method = NULL;
  for(int i=0; i<f->len(); i++){
    if(f->nth(i)->is_method() && f->nth(i)->get_name() == name ) {
      method = (method_class *)f->nth(i);
    }
  }
  if(method == NULL)
    cout << name << " WRONG\n";
  //evaluate all actuals, push all actuals in order 
  for(int i=actual->first(); actual->more(i); i=actual->next(i)){
    if (cgen_optimize) {
      if(actual->nth(i)->get_type() == Int
      &&( (method_def_class==IO && !strcmp(name->get_string(), "out_int"))
        ||(method_def_class==Str && !strcmp(name->get_string(), "substr"))
        || method->formals->nth(i)->get_type() == Object ) ) {
        cout<<method_def_class<<" "<<name<<" argument boxing\n";
        int_flag_global = 1;
        //boxing(s);
        //emit_store(ACC, 1, SP, s);
      }
    }

    actual->nth(i)->code(s);
    int_flag_global = 0;
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos ++;
  }

  expr->code(s);
  if ((cgen_optimize) && (expr->get_type() == Int)) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      s << "# dispatch boxing" << endl;
      cout << "dispatch boxing.\n";
      boxing(s);
      emit_addiu(SP, SP, 4, s);
  }

 //run time system check, check if expr is pointed to zero
  int label = label_cur_num++;
  emit_bne(ACC, ZERO, label, s);
  // emit abort code here, get filename and line number
  char *filename = ((class__class *)current_nd)->filename->get_string();
  emit_load_string(ACC, stringtable.lookup_string(filename),s);
  emit_load_imm(T1, get_line_number(), s);
  emit_jal("_dispatch_abort", s);

  emit_label_def(label, s);
  emit_load(T1, DISPTABLE_OFFSET, ACC, s);  //get pointer to dispatch table  
  //get entry in dispatch table
  CgenNodeP nd;
  if(expr->get_type() == SELF_TYPE)
    nd = current_nd;
  else  //if the expr is not SELF_TYPE, find the CgenNode
    nd = current_cgen->probe(expr->get_type());
  int *disp_entry = nd->method_table->probe(name);
  emit_load(T1, *disp_entry, T1, s);
  emit_jalr(T1, s); 
  current_cgen->pos -= actual->len();
  if ( cgen_optimize ) {
      if (  (method_def_class == IO && !strcmp(name->get_string(), "in_int"))
        || (!strcmp(name->get_string(), "copy")  && expr->get_type() == Int)
        || (method_def_class == Str && !strcmp(name->get_string(), "length"))
        )
      {
        if (int_flag_rec == 0){
          emit_load(ACC, 3, ACC, s);
          box_ccnt += 1;
        }
      } else {
        if (method->return_type == Int && int_flag_rec == 1){
          emit_store(ACC, 0, SP, s);
          emit_addiu(SP, SP, -4, s);
          boxing(s);
          emit_addiu(SP, SP, 4, s);
        }
      }
  } 
  int_flag_global = int_flag_rec;
}

void cond_class::code(ostream &s) {
//  cout << "cond class. \n";
  pred->code(s);
  emit_load(T1, 3, ACC, s);
  int false_lnum = label_cur_num;
  label_cur_num ++;
  emit_beq(T1, ZERO, false_lnum, s);    //false_branch: label 0
  then_exp->code(s);

  int endif_lnum = label_cur_num;
  label_cur_num ++;
  emit_branch(endif_lnum, s);            //endif_branch: label 1
 
  emit_label_def(false_lnum, s); 
  else_exp->code(s);
  emit_label_def(endif_lnum, s);  

}

void loop_class::code(ostream &s) {
//  cout << "loop class. \n";
  int end_lnum = label_cur_num;
  label_cur_num ++;
  int loop_lnum = label_cur_num;
  label_cur_num ++;
  emit_label_def(loop_lnum, s);
  pred->code(s);
  emit_load(T1, 3, ACC, s);
  emit_beq(T1, ZERO, end_lnum, s);    //false_branch
  body->code(s);
  emit_branch(loop_lnum, s);
  emit_label_def(end_lnum, s);
  emit_move(ACC, ZERO, s);
}

void typcase_class::code(ostream &s) {
//  cout << "typcase class. \n";
  expr->code(s);
  if ((cgen_optimize) && (expr->get_type() == Int)) {
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    boxing(s);
    emit_addiu(SP, SP, 4, s);
  }

  emit_store(ACC, 0, SP, s);  //new location on stack
  emit_addiu(SP, SP, -4, s);
  int pos = current_cgen->pos ++ ;

  int end_lnum = label_cur_num;
  label_cur_num ++;

  int case_cur_lnum = label_cur_num;
  label_cur_num ++;
  //check run time error: case on void
  emit_bne(ACC, ZERO, case_cur_lnum, s);
   // emit abort code here, get filename and line number
  char *filename = ((class__class *)current_nd)->filename->get_string();
  emit_load_string(ACC, stringtable.lookup_string(filename),s);
  emit_load_imm(T1, get_line_number(), s);
  emit_jal("_case_abort2", s);

  void **t = new void * [cases->len()];
  for(int i= cases->first(); cases->more(i); i = cases->next(i) ){
    Case c = cases->nth(i);
    t[i] = (void *)(c);
  }

  //deep level will be emitted first
  for(int i=0; i<cases->len(); i++){
    for(int j=i+1; j<cases->len(); j++){
      CgenNodeP nd1 = 
        current_cgen->lookup(((class branch_class *)t[i])->type_decl);
      CgenNodeP nd2 = 
        current_cgen->lookup(((class branch_class *)t[j])->type_decl);
      if(nd2->class_inherit_level > nd1->class_inherit_level){
        void *swap = t[j];
        t[j] = t[i];
        t[i] = swap;
      }
    }
  }
  
  int case_next_lnum;
  for(int i = cases->first(); cases->more(i); i = cases->next(i) ){
    emit_label_def(case_cur_lnum, s);
    class branch_class * case_branch = (class branch_class *)t[i];
    Symbol case_nd_name = case_branch->name; //cout << case_nd_name << endl;
    Symbol case_nd_type = case_branch->type_decl;
    int type_tag_sm = current_cgen->lookup(case_nd_type)->class_tag;
    int type_tag_lg = current_cgen->lookup(case_nd_type)->class_tag_coverage;
    emit_load(T2, 0, ACC, s);
    case_next_lnum = label_cur_num;
    label_cur_num ++;
    emit_blti(T2, type_tag_sm, case_next_lnum, s);
    emit_bgti(T2, type_tag_lg, case_next_lnum, s);
    if (cgen_optimize && case_nd_type == Int) {
      emit_load(ACC, 3, ACC, s);
      box_ccnt += 1;
      emit_store(ACC, 1, SP, s);
    }
    current_cgen->let_table->enterscope();
    current_cgen->let_table->addid(case_nd_name, new int(pos));
    current_cgen->let_type->enterscope();
    current_cgen->let_type->addid(case_nd_name, new Symbol(case_nd_type));

    Expression case_nd_expr = case_branch->expr;
    case_nd_expr->code(s);
    emit_branch(end_lnum, s);
    current_cgen->let_table->exitscope();
    current_cgen->let_type->exitscope();

    case_cur_lnum = case_next_lnum;
  }

  emit_label_def(case_next_lnum, s);
  emit_jal("_case_abort", s);

  emit_label_def(end_lnum, s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->pos--;
}

void block_class::code(ostream &s) {
//  cout << "block class. \n";
  for (int i = body->first(); body->more(i); i = body->next(i) ){
    body->nth(i)->code(s);
  }
}

void let_class::code(ostream &s) {
//  cout << "let class. \n";
  //if there is no let initiation expression, 
  //load a default value according to type
  if(init->get_type() && init->get_type() != No_type )
    init->code(s);
  else {
    if(type_decl == Int ) {
      if(cgen_optimize)
        s << LI << ACC <<" 0\n";
      else {
        s << LA << ACC << " ";
        inttable.lookup_string("0")->code_ref(s);
        s << endl;
      }
    } else if(type_decl == Str) {
      s << LA << ACC << " ";
      stringtable.lookup_string("")->code_ref(s);
      s << endl;
    } else if(type_decl == Bool ) 
      emit_load_address(ACC, "bool_const0", s);
    else
      emit_move(ACC, ZERO, s);
  }
  emit_store(ACC, 0, SP, s);  //new location on stack
  emit_addiu(SP, SP, -4, s);
  current_cgen->let_table->enterscope();  
  //variable's new location, relative to $fp
  current_cgen->let_table->addid(identifier, new int(current_cgen->pos++));

  current_cgen->let_type->enterscope();
  current_cgen->let_type->addid(identifier, new Symbol(type_decl));
  
  body->code(s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->let_table->exitscope();
  current_cgen->let_type->exitscope();
  current_cgen->pos--;
}

void plus_class::code(ostream &s) {
//  cout << "plus class.\n";
  if (cgen_optimize) {
    int int_flag_rec = int_flag_global;
    int_flag_global = 0;
    e1->code(s); //a value will be on accumulator
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos++;
    e2->code(s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    current_cgen->pos--;
    emit_add(ACC, ACC, T1, s);
    if (int_flag_rec == 1) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
    int_flag_global = int_flag_rec;
    return;
  }

//original code: no optimization

  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;
  e2->code(s);
  emit_jal("Object.copy", s);

  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(T2, 3, ACC, s);
  emit_add(T1, T1, T2, s);
  emit_store(T1, 3, ACC, s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->pos--;
}

void sub_class::code(ostream &s) {
//  cout << "sub class. \n";
  if (cgen_optimize) {
    int int_flag_rec = int_flag_global;
    int_flag_global = 0;
    e1->code(s); //a value will be on accumulator
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos++;
    e2->code(s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    current_cgen->pos--;
    emit_sub(ACC, T1, ACC, s);
    if (int_flag_rec == 1) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
    int_flag_global = int_flag_rec;
    return;
  }

//original code: no optimization
  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;
  e2->code(s);
  emit_jal("Object.copy", s);

  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(T2, 3, ACC, s);
  emit_sub(T1, T1, T2, s);
  emit_store(T1, 3, ACC, s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->pos--;
}

void mul_class::code(ostream &s) {
//  cout << "mul class. \n";
  if (cgen_optimize) {
    int int_flag_rec = int_flag_global;
    int_flag_global = 0;
    e1->code(s); //a value will be on accumulator
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos++;
    e2->code(s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    current_cgen->pos--;
    emit_mul(ACC, T1, ACC, s);
    if (int_flag_rec == 1) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
    int_flag_global = int_flag_rec;
    return;
  }

//original code: no optimization
  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;
  e2->code(s);
  emit_jal("Object.copy", s);

  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(T2, 3, ACC, s);
  emit_mul(T1, T1, T2, s);
  emit_store(T1, 3, ACC, s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->pos--;
}

void divide_class::code(ostream &s) {
//  cout << "div class. \n";
  if (cgen_optimize) {
    int int_flag_rec = int_flag_global;
    int_flag_global = 0;
    e1->code(s); //a value will be on accumulator
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos++;
    e2->code(s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    current_cgen->pos--;
    emit_div(ACC, T1, ACC, s);
    if (int_flag_rec == 1) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
    int_flag_global = int_flag_rec;
    return;
  }

//original code: no optimization
  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;
  e2->code(s);
  emit_jal("Object.copy", s);

  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(T2, 3, ACC, s);
  emit_div(T1, T1, T2, s);
  emit_store(T1, 3, ACC, s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->pos--;
}

void neg_class::code(ostream &s) {
//  cout << "neg class. \n";
  if (cgen_optimize) {
    int int_flag_rec = int_flag_global;
    int_flag_global = 0;
    e1->code(s);
    emit_sub(ACC, ZERO, ACC, s);
    if (int_flag_rec == 1) {
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
    int_flag_global = int_flag_rec;
    return;
  }

  e1->code(s);
  emit_jal("Object.copy", s);

  emit_load(T1, 3, ACC, s);
  emit_sub(T1, ZERO, T1, s); 
  emit_store(T1, 3, ACC, s);
}

void lt_class::code(ostream &s) {
//  cout << "lt class . \n";
  if (cgen_optimize) {
    e1->code(s);
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos++;
    e2->code(s);
    emit_load(T1, 1, SP, s);
    emit_addiu(SP, SP, 4, s);
    current_cgen->pos--;

    int true_lnum = label_cur_num ++;
    emit_blt(T1, ACC, true_lnum, s);
    emit_load_bool(ACC, BoolConst(0), s);
    int end_lnum = label_cur_num ++;
    emit_branch(end_lnum, s);
    emit_label_def(true_lnum, s);
    emit_load_bool(ACC, BoolConst(1), s);
    emit_label_def(end_lnum, s);
    return;
  }

//original code: no optimization
  s << "# less than." <<endl;
  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;
  e2->code(s);
  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(T2, 3, ACC, s);
  int true_lnum = label_cur_num ++;
  emit_blt(T1, T2, true_lnum, s);
  emit_addiu(SP, SP, 4, s);
  emit_load_bool(ACC, BoolConst(0), s);
  int end_lnum = label_cur_num ++;
  emit_branch(end_lnum, s);
  emit_label_def(true_lnum, s);
  emit_addiu(SP, SP, 4, s);
  emit_load_bool(ACC, BoolConst(1), s);
  emit_label_def(end_lnum, s);
  current_cgen->pos--;
}

void eq_class::code(ostream &s) {
//  cout << "eq class. \n";
  int int_flag_rec;
  if ((cgen_optimize) && (e1->get_type() == Int)) {
      int_flag_rec = int_flag_global;
      int_flag_global = 0;

    //only Int and Int could compare type
      e1->code(s);
      emit_store(ACC, 0, SP, s); //only data is on stack, no object
      emit_addiu(SP, SP, -4, s);
      current_cgen->pos++;

      e2->code(s);
      emit_load(T1, 1, SP, s);
      emit_addiu(SP, SP, 4, s);
      current_cgen->pos--;
      int true_lnum = label_cur_num ++;
      int_flag_global = int_flag_rec;

      emit_beq(T1, ACC, true_lnum, s);
      emit_load_bool(ACC, BoolConst(0), s);
      int end_lnum = label_cur_num++;
      emit_branch(end_lnum, s);
      emit_label_def(true_lnum, s);
      emit_load_bool(ACC, BoolConst(1), s);

      emit_label_def(end_lnum, s);
      return;
  }

//original code, all type works
  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;

  e2->code(s);
  emit_load(T1, 1, SP, s);
  emit_addiu(SP, SP, 4, s);
  current_cgen->pos--;
  emit_move(T2, ACC, s);
  int true_lnum = label_cur_num;
  label_cur_num ++;
  emit_beq(T1, T2, true_lnum, s);
  emit_load_bool(ACC, BoolConst(1), s);
  emit_load_bool(A1, BoolConst(0), s);
  emit_jal("equality_test", s);
  int end_lnum = label_cur_num;
  label_cur_num ++;
  emit_branch(end_lnum, s);
  emit_label_def(true_lnum, s);
  emit_load_bool(ACC, BoolConst(1), s);
  emit_label_def(end_lnum, s);
}

void leq_class::code(ostream &s) {
//  cout << "leq class.\n";

  if (cgen_optimize) {
    e1->code(s);
    emit_store(ACC, 0, SP, s);
    emit_addiu(SP, SP, -4, s);
    current_cgen->pos++;

    e2->code(s);
    emit_load(T1, 1, SP, s);
    int true_lnum = label_cur_num;
    label_cur_num ++;
    emit_bleq(T1, ACC, true_lnum, s);
    emit_addiu(SP, SP, 4, s);
    emit_load_bool(ACC, BoolConst(0), s);
    int end_lnum = label_cur_num;
    label_cur_num ++;
    emit_branch(end_lnum, s);
    emit_label_def(true_lnum, s);
    emit_addiu(SP, SP, 4, s);
    emit_load_bool(ACC, BoolConst(1), s);
    emit_label_def(end_lnum, s);
    current_cgen->pos--;
    return;
  }

//original code : no optimization
  e1->code(s);
  emit_store(ACC, 0, SP, s);
  emit_addiu(SP, SP, -4, s);
  current_cgen->pos++;

  e2->code(s);
  emit_load(T1, 1, SP, s);
  emit_load(T1, 3, T1, s);
  emit_load(T2, 3, ACC, s);
  int true_lnum = label_cur_num;
  label_cur_num ++;
  emit_bleq(T1, T2, true_lnum, s);
  emit_addiu(SP, SP, 4, s);
  emit_load_bool(ACC, BoolConst(0), s);
  int end_lnum = label_cur_num;
  label_cur_num ++;
  emit_branch(end_lnum, s);
  emit_label_def(true_lnum, s);
  emit_addiu(SP, SP, 4, s);
  emit_load_bool(ACC, BoolConst(1), s);
  emit_label_def(end_lnum, s);
  current_cgen->pos--;
}

void comp_class::code(ostream &s) {
//  cout << "comp class. \n";
  e1->code(s);
  int end_lnum = label_cur_num;
  label_cur_num ++;
  int false_lnum = label_cur_num;
  label_cur_num ++;

  emit_load(T1, 3, ACC, s);
  emit_beq(T1, ZERO, false_lnum, s);
  emit_load_bool(ACC, BoolConst(0), s);
  emit_branch(end_lnum, s);
  emit_label_def(false_lnum, s);
  emit_load_bool(ACC, BoolConst(1), s);
  emit_label_def(end_lnum, s);
}

void int_const_class::code(ostream& s)  
{
  //
  // Need to be sure we have an IntEntry *, not an arbitrary Symbol
  //
  if (cgen_optimize && !int_flag_global) {
    s << LI << ACC <<" "<< token << endl;
    return;
  }

// original code : no optimization
  emit_load_int(ACC,inttable.lookup_string(token->get_string()),s);
}

void string_const_class::code(ostream& s)
{
  emit_load_string(ACC,stringtable.lookup_string(token->get_string()),s);
}

void bool_const_class::code(ostream& s)
{
  emit_load_bool(ACC, BoolConst(val), s);
}

void new__class::code(ostream &s) {
  Symbol type;
  if( type_name == SELF_TYPE )
    type = current_nd->get_name();
  else
    type = type_name;

  s << LA << ACC << " " << type << PROTOBJ_SUFFIX << endl;
  emit_jal("Object.copy", s);
  s << JAL << type << CLASSINIT_SUFFIX << endl;    
}

void isvoid_class::code(ostream &s) {
//  cout << "isvoid class.\n";
  e1->code(s);
  int isvoid_lnum = label_cur_num;
  label_cur_num ++;
  int end_lnum = label_cur_num;
  label_cur_num ++;
  emit_beqz(ACC, isvoid_lnum, s);
  emit_load_bool(ACC, BoolConst(0), s);
  emit_branch(end_lnum, s);
  emit_label_def(isvoid_lnum, s);
  emit_load_bool(ACC, BoolConst(1), s);
  emit_label_def(end_lnum, s);
}

void no_expr_class::code(ostream &s) {
//  emit_load_int(ACC, inttable.lookup_string("0"), s);
}

void object_class::code(ostream &s) {
//  cout << name << " object class. \n";  
  if( name == self )
    emit_move(ACC, SELF, s);
  else{
    int attr_num = 0, formal_num = 0, pos = 0;
    assert(current_nd);
    int *offset = current_cgen->let_table->lookup(name);
    if(offset){
      pos = *offset;
      emit_load(ACC,  -pos , FP, s);
    }
    else if(current_cgen->formal_table->probe(name)){
      offset = current_cgen->formal_table->probe(name);
      formal_num = *offset;
      emit_load(ACC, current_cgen->argc - 1 - formal_num + 3, FP, s);
    } else {
      offset = current_nd->attr_name_table->probe(name);
      if(offset)
        emit_load(ACC, *offset + DEFAULT_OBJFIELDS, SELF, s);
      else
        s <<"# object id could not find, something wrong\n";
    }
     
  }
  if (cgen_optimize && int_flag_global) {
    Symbol *typeP = NULL, type = NULL;
/*    if(name == self) 
      *type = current_nd->get_name();
    else*/
    typeP = current_cgen->let_type->lookup(name);
    if(!typeP)
      typeP = current_cgen->formal_type->probe(name);
    if(!typeP)
      typeP = current_nd->attr_type_table->probe(name);
    if(!typeP){
      cout <<get_line_number()<<name<< " WRONG at Object id\n";
      type = current_nd->get_name();
    } else
      type = *typeP;
//    cout<<get_line_number()<<name<<endl;
 
    if(type == Int ){
      emit_store(ACC, 0, SP, s);
      emit_addiu(SP, SP, -4, s);
      boxing(s);
      emit_addiu(SP, SP, 4, s);
    }
  }
}

