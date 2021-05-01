//=============================================================================
#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include "BaseTypes.h"
#include "Sys/Tlist.h"
#include "Sys/Str.h"
#include "Math/Maths.h"// mat4.h"

//padding = (align - (offset mod align)) mod align
//new offset = offset + padding = offset + (align - (offset mod align)) mod align
//
//padding = (align - (offset & (align - 1))) & (align - 1) = (-offset) & (align - 1)
//new offset = (offset + align - 1) & ~(align - 1)
//
//(((i+31)>>5)<<2); // aligned to 32-bits
//=============================================================================<
//struct var{//u512=512bits=mat4=64char=16float=8bl
//	u8_t data[64];
//	u16_t *u16(){return (u16_t*)data;}
//	u32_t *u32(){return (u32_t*)data;}
//	i32_t *i32(){return (i32_t*)data;}
//	float *flt(){return (float*)data;}
//	//vec3 *vec3(){return (vec3*)data;}	 // (
//	//vec4 *vec4(){return (vec4*)data;}
//	//mat4 *mat4(){return (mat4*)data;}
//	//u64_t data[8];//64byte
//	//union{
//	//	u8_t bytes[64];//string{byte char[64];}
//	//	float fl[16];
//	//	double dbl[8];
//	//	vec4 tttt[4]; // (
//	//	//mat4 mat;
//	//};
//
//};
//struct FunctionBase;//FD (
static const char* VAR_TYPE[]={"unknown","int","float","str","function","void","mat4"};//,"Origin", "mat4", "quat", "vec4", "vec3", "vec2"
//============================================================================= <Variable>	   (2^20)/(64+4) -> 1Mb = 15420 Vars
struct DLL_API Variable{//8bytes=u64, 16bytes=u128 +2b =10b		   sizeof()=12
	void *data;//4b|8b
	u16_t mem, mmem;// +4b
	u8_t type;//{i32_t,u32_t,float,vec2,vec3,vec4,quat,mat4,str}
	u8_t flag;//{const,var,pointer}
	enum TYPE{ UNK = 0, INT, FLT, STR, FUN, NON, MAT };//,UINT,FLOAT}; // VOID,CONST -reserved
	enum FLAG{ VAR = 0, REF };
	//-----------------------------------------------------------------------------
	void init(){ type = 0, flag = 0, mem = mmem = 0, data = nullptr; };
	void clear(){ type = 0, flag = 0, mem = 0; }
	//-----------------------------------------------------------------------------
	Variable(){ init(); }
	// TYPE{UNK=0,INT,FLOAT,str,FUN}; FLAG{VAR=0,REF};
	Variable(const int vtype, void *vptr, const int vflag = FLAG::VAR);
	//-----------------------------------------------------------------------------
	void resize(int nsz);
	void prepare_mem(const int vtype, const int vflag = FLAG::VAR, const int len = 0);
	//-----------------------------------------------------------------------------
	// TYPE{UNK=0,INT,FLOAT,str,FUN}; FLAG{VAR=0,REF};
	void set(const int vtype, void *vptr, const int vflag = FLAG::VAR);
	//-----------------------------------------------------------------------------
	void string(const char *s, int num);
	//-----------------------------------------------------------------------------
	//void operator=(int a){set(TYPE::INT,&a);}
	//void operator=(int *a){set(TYPE::INT,a,FLAG::REF);}//array of int?
	//-----------------------------------------------------------------------------
	//void set_value(const char *vname){
	//	if(type==TYPE::INT){
	//		*(int*)data=atoi(vname);// (*get_p<int>())=atoi(vname);
	//	}
	//}
	//-----------------------------------------------------------------------------
	template <typename T> T    get(){ return *(T*) (data); }
	template <typename T> T  get_s(){ return *(T*) (data); }//u32_t  a=BUF.get_s<u32_t>(0);//get 4 bytes call(a)
	template <typename T> T* get_p(){ return  (T*) (data); }//u32_t *a=BUF.get_p<u32_t>(0);//get 4 bytes call(*a)
	//-----------------------------------------------------------------------------
	void add(Variable a);
	void sub(Variable a);
	void mul(Variable a);
	void div(Variable a);
	void eq(Variable a);
	//-----------------------------------------------------------------------------
	//void run_no_ret(VirtOPCodes *VC);/*FD'ed{	 VirtOPCodes - unknown identifer - FD
	//	if(type==FUN) get_p<FunctionBase>()->run(NULL);
	//}*/
};
//============================================================================= <VariableToType>
template <class Type> struct VariableToType {//regular any
	VariableToType(const Variable &v) : value(*(Type*) v.data) { }  //value((Type)v.data) { }  
	Type value;
};
template <class Type> struct VariableToType<Type&> {//ref - totest
	VariableToType(const Variable &v) : value(*(Type*) v.data) { }
	Type &value;
};
template <class Type> struct VariableToType<Type*> {//string
	VariableToType(const Variable &v) : value((Type*) v.data) { }
	Type *value;
};
//============================================================================= <TypeToVariable>
//VariableToType<A0> a0(VC->pop());
//Ret value = func(a0.value);
//Variable *R = new Variable();
//TypeToVariable<Ret> ret(*R, value);
template <class Type> struct TypeToVariable {
	TypeToVariable(Variable &var, Type t) { var.set(Variable::TYPE::INT, &t); }
};
template <class Type> struct TypeToVariable<Type*> {
	TypeToVariable(Variable &var, Type *t) { var.set(Variable::TYPE::NON, t, Variable::FLAG::REF); }
};
#define DECLARE_TYPE_TO_VARIABLE_STACK(TYPE,TYPE2) \
template <> struct TypeToVariable<TYPE> { \
	TypeToVariable(Variable &var,TYPE t) { var.set(TYPE2, &t ); } \
};
DECLARE_TYPE_TO_VARIABLE_STACK(int, Variable::INT)
DECLARE_TYPE_TO_VARIABLE_STACK(float, Variable::FLT)
DECLARE_TYPE_TO_VARIABLE_STACK(mat4, Variable::MAT)
//============================================================================= <get_builtin_type>
static int get_builtin_type(const char *tname){
	int ret=Variable::UNK;
		if (!strcmp(tname, "void"))		ret = Variable::NON;//void
	else if (!strcmp(tname, "int"))		ret = Variable::INT;
	else if (!strcmp(tname, "float"))	ret = Variable::FLT;
	else if (!strcmp(tname, "str"))		ret = Variable::STR;
	else if (!strcmp(tname, "mat4"))	ret = Variable::MAT;
	return ret;
}
////============================================================================= <SmartStr>
//struct SmartStr{//RAII	 sizeof()=4
//	TPool<str>::pnode iter;
//
//	SmartStr(){iter=TPool<str>::Inst().get();iter->data_ptr->size=0;}//LOG::msg("SmartStr constr");
//	~SmartStr(){TPool<str>::Inst().free(iter);}//null? LOG::msg("SmartStr destr");
//	operator       str*()     {return iter->data_ptr;}
//	operator const str*()const{return iter->data_ptr;}
//	str     *operator->()     {return iter->data_ptr;}
//	bool operator==(const char *strp)const{return (*iter->data_ptr)==strp;}
//};//SmartStr
//static SmartStr _firstSmartStr_toHoldPoolInstance;
//============================================================================= <SmartVar>
//struct SmartVar{//RAII
//	TPool<Variable>::pnode iter;
//SmartVar(){iter=TPool<Variable>::Inst().get();}//LOG::msg("SmartStr constr");
//~SmartVar(){TPool<Variable>::Inst().free(iter);}//null? LOG::msg("SmartStr destr");
//operator       Variable*()     {return iter->data_ptr;};
//operator const Variable*()const{return iter->data_ptr;};
//Variable     *operator->()     {return iter->data_ptr;};
//};//SmartVar
//=============================================================================
enum{
	OP_NOP=0,OP_ASSIGN,//OP_MOV,OP_CLR,OP_CPY,OP_PUSH,OP_POP,	//mem
	OP_CONST,OP_VAR,OP_FUNC,									//data
	OP_OPEN,OP_EQ,OP_RET,OP_JNZ,OP_JMP,//OP_LOOP,OP_CALL,		//algo
	OP_ADD,OP_SUB,OP_MUL,OP_DIV,OP_INV,//,OP_EXP				//math
	OP_SIZE//how mush ops for OP_NAME[]
};
static const char* OP_NAME[]={	
	"OP_NOP","OP_ASSIGN",							//lowest priority
	"OP_CONST","OP_VAR","OP_FUNC",
	"OP_OPEN","OP_EQ","OP_RET","OP_JNZ","OP_JMP",
	"OP_ADD","OP_SUB","OP_MUL","OP_DIV","OP_INV"	//highest priority
};
//============================================================================= <VirtOPCodes>
struct DLL_API VirtOPCodes{//sizeof()=16
	u32_t mv, memv;
		Variable **V;
		int *ops;//operations

	VirtOPCodes(){ init(); }
	void init(){
		V = nullptr;
		ops = nullptr;
		mv = memv = 0;
	}
	~VirtOPCodes(){ if(memv){ FREE(V);FREE(ops);memv = 0; }clear(); }
	void clear(){
		mv = 0;
	}
	void resize(u32_t nmv);
	//vop=
	//	OP_NOP=0, OP_ASSIGN,					//mem
	//	OP_CONST, OP_VAR, OP_FUNC,				//data
	//	OP_OPEN, OP_EQ, OP_RET, OP_JNZ, OP_JMP,	//algo
	//	OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_INV	//math
	void push(int vop, Variable *var = nullptr);
	Variable *pop();
	Variable *top();
	void run(VirtOPCodes *code_page);
	void print()const;
};
//=============================================================================
#endif
