#ifndef __TLIST_H__
#define __TLIST_H__ 1

#include "BaseTypes.h"

//============================================================================== http://www.programmersforum.ru/showthread.php?s=dae7e5f2540783ed87c00739467bdfbd&t=39678&page=2
template <typename T> 
struct DLL_API Tlist{
	struct node{ 
		T *data_ptr;
		node *next,*prev;
		//void clear(){data_ptr=nullptr,next=nullptr,prev=nullptr;} 
		node():data_ptr(nullptr),next(nullptr),prev(nullptr){}
		node(T *data):data_ptr(data),next(nullptr),prev(nullptr){}
		T* operator->(){return data_ptr;}
	};
 //typedef Tlist<T>::node iterator;
//------------------------------------------------------------------------------
	node *begin,*end;
//------------------------------------------------------------------------------
Tlist():begin(nullptr),end(nullptr){}
//------------------------------------------------------------------------------
~Tlist(){// is it need?
	//LOG::MSG("TList destr");
	node *it=begin;
	while(begin){
		it=it->next;
		delete begin;
		begin=it;
	}
	begin=end=nullptr;
	//LOG::MSG("TList destr done");
}
//------------------------------------------------------------------------------
u32_t size_slow()const{
	node *it=nullptr;
	u32_t num_elements=0;
	while(iterate(it)) num_elements++;
	return num_elements;//(end-begin) /sizeof(node); //
}
//------------------------------------------------------------------------------
inline bool iterate(node *&it)const{			  // Tlist<struct>::node *it=nullptr;
	it=(it==nullptr)?begin:it=it->next;	  // while(X.iterate(it)) (*it)->usage
	return it!=nullptr;
}
//------------------------------------------------------------------------------
inline bool r_iterate(node *&it){//reverse
	it=(it==nullptr)?end:it=it->prev;
	return it!=nullptr;
}
//------------------------------------------------------------------------------
node *add(T *data){
	node *nd=new node(data);
	if(begin==nullptr){
		begin=nd;end=nd;
	}else{
		end->next=nd;
		nd->prev=end;
		end=nd;
	}
	return nd;
}
//------------------------------------------------------------------------------
node *add(node *nd){
	if(begin==nullptr) begin=nd,end=nd; else{
		end->next=nd;
		nd->prev=end;
		end=nd;
		end->next=nullptr;
	}
	return nd;
}
//------------------------------------------------------------------------------
void ins(node *new_node, node *after_node){
	unlink(new_node);
	new_node->next = after_node->next;
	new_node->prev = after_node;
	after_node->next = new_node;
}
//------------------------------------------------------------------------------
void unlink(node *nd){//nd are not begin|end itselves
	if(!nd)return;
	//begin=begin->next;
	//if(begin!=nullptr){
	//	begin->prev=nullptr;
	//}else{
	//	end=nullptr;
	//};
	//LOG::MSG("nd %p",nd);
	//LOG::MSG("nd %p",nd->next);
	//LOG::MSG("nd %p",nd->prev);
	if(nd->prev)nd->prev->next=nd->next;else begin=nd->next;
	if(nd->next)nd->next->prev=nd->prev;else end=nd->prev;
	if(end==nullptr || begin==nullptr)begin=end=nullptr;//?check it
	nd->next=nullptr;
	nd->prev=nullptr;
}
//------------------------------------------------------------------------------
void circulate(node *&it){// add next node at end from begin, ring buffer with reusing
	it=begin;
	begin=begin->next;begin->prev=nullptr;
	it->prev=end;it->next=nullptr;
	end->next=it, end=it;
}
//------------------------------------------------------------------------------
};
//=============================================================================<TPool>
// TPool ITEMS must have simple default constructor
template <typename T> 
struct TPool{
	Tlist<T> A, U;
	typedef typename Tlist<T>::node* pnode;
	static TPool &Inst(){//LOG::MSG("get instance");
		static TPool SS;
		return SS;
	}
	pnode get(){//LOG::MSG("StrPool:: add new string");
		pnode iter = nullptr;
		if(U.begin == nullptr){
			//LOG::MSG("create new node");
			iter = A.add(new T());//return S.add(new Str())->data_ptr;
		}else{
			//LOG::MSG("StrPool reuse");
			iter = U.begin;
			U.unlink(iter);
			A.add(iter);//return S.add(iter)->data_ptr;
		}
		//LOG::MSG("get %p",iter);
		return iter;
	}
	void free(pnode node){//use in destructor for smart
		A.unlink(node);
		U.add(node);
	}
private:
    TPool():A(), U(){}
    ~TPool(){}//LOG::MSG("TPool singleton destr");}
	TPool(TPool const&); // no copy
	TPool& operator= (TPool const&);  // no assign
};//TPool
//==============================================================================
#endif
