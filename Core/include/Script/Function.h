#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "Variable.h"
#include "Sys/Str.h"

//============================================================================= <FunctionBase>
class FunctionBase {
public:
	FunctionBase(){ }
	virtual ~FunctionBase() { }
	//	virtual FunctionBase *clone() const = 0;
	virtual int get_num_args() const = 0;
	virtual const str &get_args() const = 0;
	virtual void run(VirtOPCodes *VC) const = 0;
	virtual bool internal() const = 0;
};
//============================================================================= <TypeList>
struct TypeListEnd {};
template <class T,class U> struct TypeList {
	typedef T Head;
	typedef U Tail;
};
template <class T0  = TypeListEnd,class T1  = TypeListEnd,class T2  = TypeListEnd,class T3  = TypeListEnd,
		  class T4  = TypeListEnd,class T5  = TypeListEnd,class T6  = TypeListEnd,class T7  = TypeListEnd,
		  class T8  = TypeListEnd,class T9  = TypeListEnd,class T10 = TypeListEnd,class T11 = TypeListEnd,
		  class T12 = TypeListEnd,class T13 = TypeListEnd,class T14 = TypeListEnd,class T15 = TypeListEnd>
struct MakeTypeList {
	typedef TypeList<T0, typename MakeTypeList<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::Type> Type;
};
//============================================================================= <MakeTypeList>
template <>									struct MakeTypeList<> {	typedef TypeListEnd Type;};
template <class T,unsigned int>				struct TypeAt {	typedef TypeListEnd Type;};
template <class T,class U>					struct TypeAt<TypeList<T,U>,0> { typedef T Type;};
template <class T,class U,unsigned int i>	struct TypeAt<TypeList<T,U>,i> { typedef typename TypeAt<U,i-1>::Type Type;}; 
//----------------------------------------------------------------------------- <Length>
template <class T> struct Length;
template <>					struct Length<TypeListEnd> {	enum { Value = 0 };};
template <class T,class U>	struct Length<TypeList<T,U> > {	enum { Value = 1 + Length<U>::Value };};
//============================================================================= <TypeToType>
template <class T> struct TypeToType {typedef T Type;}; 
//============================================================================= <IntToType>
template <int v> struct IntToType {enum { Value = v };}; 
//============================================================================= <ExternFunction>
template <class TList,class Func> 
class ExternFunction : public FunctionBase {
public:
	ExternFunction(Func func, const char *args) : func(func), args(args) { }
	//virtual FunctionBase *clone()const{
	//	return new ExternFunction<TList,Func>(func,args);
	//}
private:
	enum { Length = Length<TList>::Value - 1 };
	typedef typename TypeAt<TList, 0>::Type Ret;
	typedef typename TypeAt<TList, 1>::Type A0;
	typedef typename TypeAt<TList, 2>::Type A1;
	typedef typename TypeAt<TList, 3>::Type A2;
	typedef typename TypeAt<TList, 4>::Type A3;
	typedef typename TypeAt<TList, 5>::Type A4;
	typedef typename TypeAt<TList, 6>::Type A5;
	typedef typename TypeAt<TList, 7>::Type A6;
	typedef typename TypeAt<TList, 8>::Type A7;
	virtual bool internal()const { return false; }
	virtual int get_num_args()const {
		return Length;
	}
	virtual const str &get_args()const {
		return args;
	}

	// run function; MAIN_ENTRY_POINT; VC holds in and out vars
	virtual void run(VirtOPCodes *VC)const {
		do_run(VC, TypeToType<Ret>(), IntToType<Length>());
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<0>)const {
		Ret value = func();
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		if (VC)VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<0>)const {//no return val
		func();
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<1>)const {
		VariableToType<A0> a0(VC->pop());
		Ret value = func(a0.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<1>)const {//no return val
		VariableToType<A0> a0(VC->pop());
		func(a0.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<2>)const {
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = func(a0.value, a1.value);
		//LOG::MSG("%i = func(%i,%i)",value,a1.value,a0.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<2>)const {//no return val
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<3>)const {
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		Ret value = func(a0.value, a1.value, a2.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}

	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<3>)const {
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value, a2.value);
	}
	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<4>)const {
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		Ret value = func(a0.value, a1.value, a2.value, a3.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}

	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<4>)const {
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value, a2.value, a3.value);
	}
	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<5>)const {
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = func(a0.value, a1.value, a2.value, a3.value, a4.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}

	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<5>)const {
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value, a2.value, a3.value, a4.value);
	}
	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<6>)const {
		VariableToType<A5> a5(VC->pop());
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		Ret value = func(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}

	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<6>)const {
		VariableToType<A5> a5(VC->pop());
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value);
	}
	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<7>)const {
		VariableToType<A6> a6(VC->pop());
		VariableToType<A5> a5(VC->pop());
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		Ret value = func(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}

	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<7>)const {
		VariableToType<A6> a6(VC->pop());
		VariableToType<A5> a5(VC->pop());
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value);
	}
	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<8>)const {
		VariableToType<A7> a7(VC->pop());
		VariableToType<A6> a6(VC->pop());
		VariableToType<A5> a5(VC->pop());
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		Ret value = func(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value, a7.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}

	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<8>)const {
		VariableToType<A7> a7(VC->pop());
		VariableToType<A6> a6(VC->pop());
		VariableToType<A5> a5(VC->pop());
		VariableToType<A4> a4(VC->pop());
		VariableToType<A3> a3(VC->pop());
		VariableToType<A2> a2(VC->pop());
		VariableToType<A1> a1(VC->pop());
		VariableToType<A0> a0(VC->pop());
		func(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value, a7.value);
	}
	Func func;
	str args;
};
//============================================================================= <MakeFunction>
template <class Ret>
FunctionBase *MakeFunction(Ret (*func)()						,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret>::Type, Ret (*)()>(func,args);}
template <class Ret,class A0>
FunctionBase *MakeFunction(Ret (*func)(A0)						,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0>::Type, Ret (*)(A0)>(func,args);}
template <class Ret,class A0,class A1>
FunctionBase *MakeFunction(Ret (*func)(A0,A1)					,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1>::Type, Ret (*)(A0,A1)>(func,args);}
template <class Ret,class A0,class A1,class A2>
FunctionBase *MakeFunction(Ret (*func)(A0,A1,A2)				,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1,A2>::Type, Ret (*)(A0,A1,A2)>(func,args);}
template <class Ret,class A0,class A1,class A2,class A3>
FunctionBase *MakeFunction(Ret (*func)(A0,A1,A2,A3)				,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1,A2,A3>::Type, Ret (*)(A0,A1,A2,A3)>(func,args);}
template <class Ret,class A0,class A1,class A2,class A3,class A4>
FunctionBase *MakeFunction(Ret (*func)(A0,A1,A2,A3,A4)			,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1,A2,A3,A4>::Type, Ret (*)(A0,A1,A2,A3,A4)>(func,args);}
template <class Ret,class A0,class A1,class A2,class A3,class A4,class A5>
FunctionBase *MakeFunction(Ret (*func)(A0,A1,A2,A3,A4,A5)		,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5>::Type, Ret (*)(A0,A1,A2,A3,A4,A5)>(func,args);}
template <class Ret,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
FunctionBase *MakeFunction(Ret (*func)(A0,A1,A2,A3,A4,A5,A6)	,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5,A6>::Type, Ret (*)(A0,A1,A2,A3,A4,A5,A6)>(func,args);}
template <class Ret,class A0,class A1,class A2,class A3,class A4,class A5	,class A6,class A7>
FunctionBase *MakeFunction(Ret (*func)(A0,A1,A2,A3,A4,A5,A6,A7)	,const char *args=0){return new ExternFunction<typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5,A6,A7>::Type, Ret (*)(A0,A1,A2,A3,A4,A5,A6,A7)>(func,args);}
//============================================================================= <MakeLambda>
#define LAMBDA(Ret, A0)\
(Ret*)(A0 *a0))\
[](A0)->Ret

#define LAMBDA(Ret, A0, A1)\
(Ret*)(A0 *a0, A1 *a1))\
[](A0, A1)->Ret
//============================================================================= <ExternMFunction>
template <class Class,class TList,class Func>
class ExternMFunction : public FunctionBase {
public:
	ExternMFunction(Class *object, Func func, const char *args) : object(object), func(func), args(args) {}
	//virtual ExternMFunction *clone()const{
	//	return new ExternMFunction<Class,TList,Func>(object,func,args);
	//}
private:
	enum { Length = Length<TList>::Value - 1 };
	typedef typename TypeAt<TList, 0>::Type Ret;
	typedef typename TypeAt<TList, 1>::Type A0;
	typedef typename TypeAt<TList, 2>::Type A1;
	typedef typename TypeAt<TList, 3>::Type A2;
	typedef typename TypeAt<TList, 4>::Type A3;
	typedef typename TypeAt<TList, 5>::Type A4;
	typedef typename TypeAt<TList, 6>::Type A5;
	typedef typename TypeAt<TList, 7>::Type A6;
	typedef typename TypeAt<TList, 8>::Type A7;
	virtual bool internal()const { return false; }
	virtual int get_num_args()const {
		return Length;
	}
	virtual const str &get_args()const {
		return args;
	}
	// run function
	virtual void run(VirtOPCodes *VC)const {
		do_run(VC, TypeToType<Ret>(), IntToType<Length>());
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<0>)const {
		Ret value = (object->*func)();
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		if (VC)VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<0>)const {
		(object->*func)();
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<1>)const {
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<1>)const {
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<2>)const {
		VariableToType<A1> a1(*VC->pop());//error C2664: 'VariableToType<const char *>::VariableToType(const VariableToType<const char *> &)' : cannot convert argument 1 from 'Variable *' to 'const Variable &'
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<2>)const {
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<3>)const {
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value, a2.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<3>)const {
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value, a2.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<4>)const {
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value, a2.value, a3.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<4>)const {
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value, a2.value, a3.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<5>)const {
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<5>)const {
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<6>)const {
		VariableToType<A5> a5(*VC->pop());
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<6>)const {
		VariableToType<A5> a5(*VC->pop());
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<7>)const {
		VariableToType<A6> a6(*VC->pop());
		VariableToType<A5> a5(*VC->pop());
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<7>)const {
		VariableToType<A6> a6(*VC->pop());
		VariableToType<A5> a5(*VC->pop());
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value);
	}

	template <class Type> void do_run(VirtOPCodes *VC, Type, IntToType<8>)const {
		VariableToType<A7> a7(*VC->pop());
		VariableToType<A6> a6(*VC->pop());
		VariableToType<A5> a5(*VC->pop());
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		Ret value = (object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value, a7.value);
		Variable *R = new Variable();
		TypeToVariable<Ret> ret(*R, value);
		VC->push(OP_CONST, R);
	}
	void do_run(VirtOPCodes *VC, TypeToType<void>, IntToType<8>)const {
		VariableToType<A7> a7(*VC->pop());
		VariableToType<A6> a6(*VC->pop());
		VariableToType<A5> a5(*VC->pop());
		VariableToType<A4> a4(*VC->pop());
		VariableToType<A3> a3(*VC->pop());
		VariableToType<A2> a2(*VC->pop());
		VariableToType<A1> a1(*VC->pop());
		VariableToType<A0> a0(*VC->pop());
		(object->*func)(a0.value, a1.value, a2.value, a3.value, a4.value, a5.value, a6.value, a7.value);
	}
	Class *object;
	Func func;
	str args;
};
//============================================================================= <MakeMFunction>
template <class Class,class Ret>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)()								,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret>::Type, Ret (Class::*)()>(object,func,args);}
template <class Class,class Ret>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)() const						,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret>::Type, Ret (Class::*)() const>(object,func,args);}
template <class Class,class Ret,class A0>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0)							,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0>::Type, Ret (Class::*)(A0)>(object,func,args);}
template <class Class,class Ret,class A0>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0) const						,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0>::Type, Ret (Class::*)(A0) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1)						,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1>::Type, Ret (Class::*)(A0,A1)>(object,func,args);}
template <class Class,class Ret,class A0,class A1>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1) const					,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1>::Type, Ret (Class::*)(A0,A1) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2)						,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2>::Type, Ret (Class::*)(A0,A1,A2)>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2) const				,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2>::Type, Ret (Class::*)(A0,A1,A2) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3)					,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3>::Type, Ret (Class::*)(A0,A1,A2,A3)>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3) const			,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3>::Type, Ret (Class::*)(A0,A1,A2,A3) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4)				,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4>::Type, Ret (Class::*)(A0,A1,A2,A3,A4)>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4) const			,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4>::Type, Ret (Class::*)(A0,A1,A2,A3,A4) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4,class A5>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4,A5)			,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5>::Type, Ret (Class::*)(A0,A1,A2,A3,A4,A5)>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4,class A5>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4,A5) const		,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5>::Type, Ret (Class::*)(A0,A1,A2,A3,A4,A5) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4,A5,A6)			,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5,A6>::Type, Ret (Class::*)(A0,A1,A2,A3,A4,A5,A6)>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4,A5,A6) const	,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5,A6>::Type, Ret (Class::*)(A0,A1,A2,A3,A4,A5,A6) const>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4,A5,A6,A7)		,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5,A6,A7>::Type, Ret (Class::*)(A0,A1,A2,A3,A4,A5,A6,A7)>(object,func,args);}
template <class Class,class Ret,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
FunctionBase *MakeMFunction(Class *object, Ret (Class::*func)(A0,A1,A2,A3,A4,A5,A6,A7) const,const char *args=0){return new ExternMFunction<Class, typename MakeTypeList<Ret,A0,A1,A2,A3,A4,A5,A6,A7>::Type, Ret (Class::*)(A0,A1,A2,A3,A4,A5,A6,A7) const>(object,func,args);}
//============================================================================= <InternalFunction>
struct InternalFunction :FunctionBase {
	VirtOPCodes *func, *backup;
	Variable *vars;
	str args;
	int Length;
	int _ret;

	InternalFunction() :func(nullptr), backup(nullptr), vars(nullptr), args(nullptr), Length(0) {}
	bool internal()const { return true; }
	int get_num_args()const { return Length; }
	const str &get_args()const { return args; }
	// run function
	//virtual void run(VirtOPCodes *VC) const = 0;
	void run(VirtOPCodes *VC)const {
		LOG::msg("call internal function [back = %p] [fun = %p]", backup, func);
		VC->run(func);
		LOG::msg("end internal function [back = %p] [fun = %p]", backup, func);
	}
	void push(InternalFunction *oif) {//other_internal_function
		if (backup == nullptr) {//if not reassigned
			//LOG::MSG("set other_internal_function [func = %p] <- [oif = %p]",func,oif->func);
			backup = func;//save
			func = oif->func;
		} else {//already reassigned
			if (oif->backup == backup) { //not null already in else; *self==*self -> restore
				//LOG::MSG("restore internal_function [func = %p] <- [backup = %p]",func,backup);
				func = backup;//load
				backup = nullptr;
			} else {
				//LOG::MSG("renew internal_function [func = %p] <- [other = %p]",func,oif->func);
				func = oif->func;//rerenew with other
			}
		}//else
	}//push()
};
//=============================================================================
#endif
