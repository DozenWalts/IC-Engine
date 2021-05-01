//=============================================================================
#ifndef __SCRIPT_HC__
#define __SCRIPT_HC__

#include "BaseTypes.h"
#include "Sys/Tlist.h"
#include "Sys/HashTable.h"
#include "Function.h"
#include "Variable.h"
//=============================================================================
//=============================================================================
//============================================================================= <Script>
struct DLL_API Script{
	str *body;
	const char *s;//pointer to body->text;
	//locals
	//KeyValueHashTable<str,Variable> vars;//52
	//KeyValueHashTable<str,FunctionBase*> funcs;//44
	HashTable<str, Variable> vars;
	typedef HashTable<str, Variable>::node var_node;

	HashTable<str, FunctionBase*> funcs;
	typedef HashTable<str, FunctionBase*>::node func_node;

	VirtOPCodes code;//16
	//int ext_int;
	int parse_line;
	bool error;
	//-----------------------------------------------------------------------------
	Script();
	~Script();
	void reset(){
		if(body) body->clear();
		s = nullptr;
		code.clear();
		vars.clear();
		funcs.clear();
		parse_line = 0;
		error = false;
	}
	//----------------------------------------------------------------------------- set
	void set(const char *text);
	//-----------------------------------------------------------------------------
	//void add_var(Variable *var){
		//Variable *ext=&vars.get_add(ext_str,ext_str->text,ext_str->size);
		//ext->set(Variable::INT,var_ref,Variable::REF);
	//}
	//----------------------------------------------------------------------------- add_int
	void add_int(int *var_ref, const char *var_name);
	void add_bool(bool *var_ref, const char *var_name);
	//----------------------------------------------------------------------------- add_func
	void add_func(FunctionBase *func_ptr, const char *fun_name);
	//----------------------------------------------------------------------------- add_func
	void add_func(FunctionBase *func_ptr, const str &fun_name);
	//----------------------------------------------------------------------------- member_fun
	int member_fun(int a, int b);
	//----------------------------------------------------------------------------- print_locals
	void print_locals();
	//----------------------------------------------------------------------------- skip_spaces
	//char* returnNextToken(char* string){
	//    while (string && *string < ' ') string++;
	//    return string;
	//}
	//int charToInt(char v){return v-'0';}

	void skip_spaces();
	//----------------------------------------------------------------------------- is_symbol
	bool is_symbol(char symb);
	//----------------------------------------------------------------------------- read_func_params
	void read_func_params(){}
	//----------------------------------------------------------------------------- read_func_proto
	void read_func_proto();
	//----------------------------------------------------------------------------- parse
	void parse(VirtOPCodes *Vcode, bool single_block = false);
	//----------------------------------------------------------------------------- compile
	void compile();
	//----------------------------------------------------------------------------- read_name
	bool read_name(str *rname);
	//----------------------------------------------------------------------------- read_const
	void read_const(str *cname, int &rtype);
	//----------------------------------------------------------------------------- read_expression
	void read_expression(VirtOPCodes *Vcode);
	//-----------------------------------------------------------------------------	run
	void run();
	Variable *exec(str func_name_code);

	Variable *run_function(str func_name_code, void *fp0);
	Variable *run_function(str func_name_code, void *fp0, void *fp1);
	Variable *run_function(str func_name_code, void *fp0, void *fp1, void *fp2);
	Variable *run_function(str func_name_code, void *fp0, void *fp1, void *fp2, void *fp3);
	Variable *run_function(str func_name_code, void *fp0, void *fp1, void *fp2, void *fp3, void *fp4);

	Variable *exec(u32_t f_id);
	//-----------------------------------------------------------------------------
	//int b_fun(){// INF LOOP
	//	return 1+b_fun();
	//}
	//-----------------------------------------------------------------------------
};
//=============================================================================
#endif