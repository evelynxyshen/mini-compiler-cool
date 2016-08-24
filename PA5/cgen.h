#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"

enum Basicness     {Basic, NotBasic};
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

class CgenClassTable : public SymbolTable<Symbol,CgenNode> {
private:
   List<CgenNode> *nds;
   ostream& str;
   int stringclasstag;
   int intclasstag;
   int boolclasstag;


// The following methods emit code for
// constants and global declarations.

   void code_global_data();
   void code_global_text();
   void code_bools(int);
   void code_select_gc();
   void code_constants();
   void code_class_tag(CgenNodeP node, int level);
   void code_class_nameTab();
   void code_class_nameTab(CgenNodeP node);
   void code_class_objTab();
   void code_class_objTab(CgenNodeP node);
   void code_dispatch_table(CgenNodeP node);
   void code_dispatch_table_parent(CgenNodeP node);
//   void code_class_protObj();
   void code_class_protObj(CgenNodeP node);
   void code_class_init(CgenNodeP node);
   void code_class_methods();
   void code_class_methods(CgenNodeP node);

// The following creates an inheritance graph from
// a list of classes.  The graph is implemented as
// a tree of `CgenNode', and class names are placed
// in the base class symbol table.

   void install_basic_classes();
   void install_class(CgenNodeP nd);
   void install_classes(Classes cs);
   void build_inheritance_tree();
   void set_relations(CgenNodeP nd);
   SymbolTable<Symbol, Symbol> *child_methods;
   SymbolTable<Symbol, Symbol> *dispatched_methods;
public:
   CgenClassTable(Classes, ostream& str);
   void code();
   CgenNodeP root();
   SymbolTable<Symbol, int> *formal_table;
   int argc;
   SymbolTable<Symbol, int> *let_table;
//   int bind_num;
   int pos; //the current $sp from $fp
};


class CgenNode : public class__class {
private: 
   CgenNodeP parentnd;                        // Parent of class
   List<CgenNode> *children;                  // Children of class
   Basicness basic_status;                    // `Basic' if class is basic
                                              // `NotBasic' otherwise

public:
   CgenNode(Class_ c,
            Basicness bstatus,
            CgenClassTableP class_table);

   void add_child(CgenNodeP child);
   List<CgenNode> *get_children() { return children; }
   void set_parentnd(CgenNodeP p);
   CgenNodeP get_parentnd() { return parentnd; }
   int basic() { return (basic_status == Basic); }

   int class_tag;
   int class_tag_coverage;
   int class_inherit_level;

   int attr_num(CgenNodeP p);
   void init_attr(CgenNodeP p, ostream & o);
   SymbolTable<Symbol, int> *attr_name_table;
   SymbolTable<Symbol, int> *method_table;
   int total_attr_num;
   int total_method_num;
   void set_feature_table();
   void set_feature_table(CgenNodeP nd, CgenNodeP parent);
};

class BoolConst 
{
 private: 
  int val;
 public:
  BoolConst(int);
  void code_def(ostream&, int boolclasstag);
  void code_ref(ostream&) const;
};

