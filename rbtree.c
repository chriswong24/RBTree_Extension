#include "ruby.h"

// Declaring values of the various classes of the Red Black Tree
VALUE cRBTree; 
VALUE cRBNode;
VALUE cNilNode;


// Minor differences from rbtree.rb:
// - colors are now strings instead of enumerables
// - Took out instance part of rbtree.rb and instead will be .new for nilnode

typedef struct node{
	char *color;
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
} Node;

//Equivalent of NilNode
Node set_nil(Node node){
	printf("\nSetting Defaults\n");
	node.color = "black";
	node.key = 69;
	node.left = NULL;
	node.right = NULL;
	node.parent = NULL;

	return node;
}

/***************************
** Node class and methods ** 
****************************/

// class Node
//		def initialize(key, color = "red")
// 			...
static VALUE node_init(int argc, VALUE *argv, VALUE self){
	
	VALUE color;

	if (argc > 2 || argc == 0){
		rb_raise(rb_eArgError, "Wrong number of arguments!");
	}
	
	rb_iv_set(self, "@key", argv[0]);

	if(argc == 2){
		color = argv[1];
	}
	else{
		color = rb_str_new2("red");
	}

	rb_iv_set(self, "@color", color);

	Node nil_node;
	nil_node = set_nil(nil_node); // def set_nil

	printf("nil_node.key: %d", nil_node.key);

	VALUE *nn;
	VALUE n_node;

	n_node = Data_Wrap_Struct(cNilNode, 0, free, nn);
	rb_iv_set(self, "@parent", n_node);
	rb_iv_set(self, "@left", n_node);
	rb_iv_set(self, "@right", n_node);


	//@left = @right = @parent = NilNode.instance

	//left = rb_iv_get(self, "@left");
	//right = rb_iv_get(self, "@right");
	//parent = rb_iv_get(self, "@parent");

	//rb_iv_set(self, "@left", right);

	return self;
}

// in Node class, def black?
static VALUE node_black(VALUE self){

	char *node_color;

	node_color = RSTRING(rb_iv_get(self, "@color"));
	printf("Node Color: %s", node_color);

	if (strcmp(node_color, "black") == 1){
		return Qtrue;
	}
	else{
		return Qfalse;
	}

	printf("Error, control should not have reached this point");
	return Qnil; // Error if reaches this point
}

// in Node class, def red?
static VALUE node_red(VALUE self){
	char *node_color;

	node_color = RSTRING(rb_iv_get(self, "@color"));
	printf("Node Color: %s", node_color);

	if (strcmp(node_color, "red") == 1){
		return Qtrue;
	}
	else{
		return Qfalse;
	}

	printf("Error, control should not have reached this point");
	return Qnil; // Error if reaches this point
}

/******************************
** NilNode class and methods **
*******************************/

// In NilNode class
//		def initialize
static VALUE NilNode_init(VALUE self){

	rb_iv_set(self, "@color", rb_str_new2("black"));
	rb_iv_set(self, "@key", INT2NUM(69));
	rb_iv_set(self, "@left", Qnil);
	rb_iv_set(self, "@right", Qnil);
	rb_iv_set(self, "@parent", Qnil);

	return self;
}

// In NildNode class, def nil?
static VALUE NilNode_nil(VALUE self){
	return Qtrue;
}

/*****************************
** RBTree class and methods **
******************************/

// RBTree class
//		def initialize
static VALUE rbt_init(VALUE self){

	//klass = Data_Wrap_Struct

	//rb_iv_set(self, "@root", klass);

	Node orig_node;
	orig_node = set_nil(orig_node);

	Node *nil_node = &orig_node;
	nil_node = ALLOC(Node); //This line seems to have fixed a bunch of things... remove it and ruby breaks
	printf("\nnil_node->key: %d\n\n", nil_node->key);
	nil_node->key = 69;
	printf("\nnil_node->key: %d\n\n", nil_node->key);
	printf("\norig_node.key: %d\n\n", orig_node.key);
	VALUE n_node;

	n_node = Data_Wrap_Struct(cNilNode, NULL, free, nil_node);
	rb_obj_call_init(n_node, 0, 0);

	// class attributes and accessors
	rb_iv_set(self, "@root", n_node);
	rb_iv_set(self, "@size", INT2NUM(0));

	Node *x;
	Data_Get_Struct(rb_iv_get(self, "@root"), Node, x);
	printf("x_init->key: %d\n", x->key);	

	return self;
}

static VALUE rbt_add(VALUE self, VALUE key) {
	return key;

}

static VALUE rbt_insert(VALUE self, VALUE x) {
	return x;
}

static VALUE rbt_insert_helper(VALUE self, VALUE z) {

	Node y;
	y = set_nil(y);
	Node *y_ptr = &y;
	// y = ALLOC(Node);

	Node *x;
	Data_Get_Struct(rb_iv_get(self, "@root"), Node, x);
	printf("x->key: %d\n", x->key);



	return z;
}

void Init_RBTree(){

	// Class declarations
	cRBTree = rb_define_class("RBTree", rb_cObject);
	
	cRBNode = rb_define_class_under(cRBTree, "Node", rb_cObject);
	cNilNode = rb_define_class_under(cRBTree, "NilNode", rb_cObject);

	

	// Node class attr_accessors
	rb_define_attr(cRBNode, "color", 1, 1);
	rb_define_attr(cRBNode, "key", 1, 1);
	rb_define_attr(cRBNode, "left", 1, 1);
	rb_define_attr(cRBNode, "right", 1, 1);
	rb_define_attr(cRBNode, "parent", 1, 1);

	//Node class methods
	rb_define_method(cRBNode, "initialize", node_init, -1);
	rb_define_method(cRBNode, "black?", node_black, 0);
	rb_define_method(cRBNode, "red?", node_red, 0);

	// NilNode class attr_accessors
	rb_define_attr(cNilNode, "color", 1, 1);
	rb_define_attr(cNilNode, "key", 1, 1);
	rb_define_attr(cNilNode, "left", 1, 1);
	rb_define_attr(cNilNode, "right", 1, 1);
	rb_define_attr(cNilNode, "parent", 1, 1);

	//NilNode class methods
	rb_define_method(cNilNode, "initialize", NilNode_init, 0);
	rb_define_method(cNilNode, "nil?", NilNode_nil, 0);

	// RBTree attr_accessors
	rb_define_attr(cRBTree, "root", 1, 1);
	rb_define_attr(cRBTree, "size", 1, 1);

	// RBTree Methods
	rb_define_method(cRBTree, "initialize", rbt_init, 0);
	
	rb_define_method(cRBTree, "add", rbt_add, 1);
	rb_define_method(cRBTree, "insert", rbt_insert, 1);
	rb_define_method(cRBTree, "insert_helper", rbt_insert_helper, 1);
}

