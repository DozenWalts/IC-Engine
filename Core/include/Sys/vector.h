#ifndef __VECTOR_H__
#define __VECTOR_H__ 1

#include "BaseTypes.h"

// !ATENTION! Vector<struct_with_pointers> c; -> Vector<struct_with_pointers*> c;
// else it invalidate pointers at destructor ex:{vector.resize(){a=b;};delete a; b<-invalidated}
template <class Type> 
struct Vector {	  //  sizeof(Vector<vec3>)= 12
	// Vector::Iterator
	class Iterator {
		private:
			friend struct Vector;
			//const u32_t &count;
			Iterator(Type *ptr/*, Type *end*/) : ptr(ptr)/*, end(end)*/ { }
		public:
			typedef Type DataType;
				
			Iterator() : ptr(0) { }
			Iterator(const Iterator &it) : ptr(it.ptr) { }
			~Iterator() { }
				
			Iterator &operator=(const Iterator &it) {
				ptr = it.ptr;
				return *this;
			}
				
			INLINE int operator==(const Iterator &it) const { return ptr == it.ptr; }
			INLINE int operator!=(const Iterator &it) const { return ptr != it.ptr; }
				
			INLINE Type &operator*() { return *ptr; }
			INLINE const Type &operator*() const { return *ptr; }
				
			INLINE Type *operator->() { return ptr; }
			INLINE const Type *operator->() const { return ptr; }
				
			INLINE Type &get() { return *ptr; }
			INLINE const Type &get() const { return *ptr; }

			INLINE Type &get_next(bool loop = false) { ++ptr;return *ptr; }//??
			INLINE Type &get_prev(bool loop = false) { ++ptr;return *ptr; }

			INLINE Iterator &operator++() {
				ptr++;
				return *this;
			}
			INLINE Iterator operator++(int) {
				Iterator temp = *this;
				ptr++;
				return temp;
			}
				
			Iterator operator+(int n) const { return Iterator(ptr + n); }
			Iterator operator-(int n) const { return Iterator(ptr - n); }
			Iterator &operator+=(int n) { ptr += n; return *this; }
			Iterator &operator-=(int n) { ptr -= n; return *this; }
				
			int operator-(const Iterator &it) const { return (int)(ptr - it.ptr); }
				
		private:
			Type *ptr;
			//Type *end;
	};
		
	// Vector
	Vector() : size(0), mem(0), data(0) {}
	Vector(const Vector &v) : size(0), mem(0), data(0) {append(v);}
	Vector(const Type &v,int new_size) : size(0), mem(0), data(0) {
		reserve(new_size);
		size=new_size;
		loop0i(new_size) data[i] = v;
	}
	Vector(const Type *v,int new_size) : size(0), mem(0), data(0) {append(v,new_size);}
	explicit Vector(int new_size) : size(0), mem(0), data(0) {reserve(new_size);size=new_size;}
	~Vector() {destroy();}
		
	Vector &operator=(const Vector &v) {
		if(this == &v) return *this;
		reserve(v.size);
		size=v.size;
		loop0i(size) data[i] = v.data[i];
		return *this;
	}
	void swap(Vector &v) {
		if(this == &v) return;
		u32_t l = size; size = v.size; v.size = l;
		u32_t c = mem; mem = v.mem; v.mem = c;
		Type *d = data; data = v.data; v.data = d;
	}
		
	INLINE Type &operator[](int index) {
		assert(index >= 0 && (u32_t)index < mem && "Vector::operator[](): bad index");
		return data[index];
	}
	INLINE const Type &operator[](int index) const {
		assert(index >= 0 && (u32_t)index < mem && "Vector::operator[](): bad index");
		return data[index];
	}
		
	//INLINE void set(int index,const Type &t) {
	//	assert(index >= 0 && (u32_t)index < size && "Vector::set(): bad index");
	//	data[index] = t;
	//}
	//INLINE Type &get(int index) {
	//	assert(index >= 0 && (u32_t)index < size && "Vector::get(): bad index");
	//	return data[index];
	//}
	//INLINE const Type &get(int index) const {
	//	assert(index >= 0 && (u32_t)index < size && "Vector::get(): bad index");
	//	return data[index];
	//}
	//INLINE Type *get() { return data; }
	//INLINE const Type *get() const { return data; }
		
	INLINE Iterator begin() const { return Iterator(data); }
	INLINE Iterator end() const { return Iterator(data + size); } //?? size-1 maybe
	INLINE Iterator last() const { return Iterator(data + size - 1); }
	INLINE Type lastVal() const { return *(data + size - 1); }
	//Type  *last(){return size?data+(size-1):nullptr;}

	void reserve(u32_t new_size) {
		if(new_size <= mem) return;
		mem = new_size;

		//RESIZE(data,Type,mem);

		// placement new?
		//new (&new_data[i]) Type (data[i]);

		Type *new_data = new Type[new_size];
		loop0i(size) {
			new_data[i] = data[i];
		}
		delete [] data;
		data = new_data;

		//size = new_size;
	}
	void resize(u32_t new_size){
		reserve(new_size);
		size = new_size;
	}
	
	void clear() {size = 0;}
	void init() {size=mem=0;data=nullptr;}
	void destroy() {
		if(mem) delete [] data;
		//FREE(data);
		size = mem = 0;
		data = 0;
	}
	
	template <class T> Iterator find(const T &t) const {
		loop0i(size) if(data[i] == t) return Iterator(data + i);
		return Iterator(data + size);
	}
	
	// usage: Struct *&val = append();
	//				   val = new Struct();
	INLINE Type &append() {
		reserve(size + 1);
		return data[size++];
	}
	INLINE void append(const Type &t) {
		reserve(size + 1);
		data[size++] = t;
	}
	INLINE void push(const Type &t) {
		reserve(size + 1);
		data[size++] = t;
	}
	void append(int pos,const Type &t) {
		assert(pos >= 0 && pos <= size && "Vector::append(): bad position");
		if(size + 1 <= mem) {
			for(u32_t i = size - 1; i >= pos; i--) { // ?? int??
				data[i + 1] = data[i];
			}
			data[pos] = t;
			size++;
			return;
		}
		mem = size * 2 + 1;

		////RESIZE(data,Type,mem);
		////loopi(pos,size) data[i + 1] = data[i];
		////data[pos] = t;

		Type *new_data = new Type[mem];
		loop0i(pos) new_data[i] = data[i];
		new_data[pos] = t;
		loopi(pos,size) new_data[i + 1] = data[i];
		delete [] data;
		data = new_data;

		size++;
	}
	INLINE void append(const Iterator &it,const Type &t) {append(it - begin(),t);}
		
	void append(const Vector &v) {
		if(size + v.size > mem) {
			reserve(size + v.size);
		}
		loop0i(v.size) data[size++] = v.data[i];
	}
		
	INLINE void remove_last() {
		assert(size > 0 && "Vector::remove(): bad size");
		size--;
	}
//void del(const u32_t &idx){if(idx<0 || idx>=size)return;
//	size--;
//	if(idx==size)return;
//	//data[idx]=data[size];
//	memcpy((T*)&data[idx],(T*)&data[size],sizeof(T));
//}
	void remove(u32_t pos,int rem_num = 1) {// copy all from pos+i to last-rem_num
		assert(pos < size && "Vector::remove(): bad position");
		assert(rem_num >= 0 && pos + rem_num <= size && "Vector::remove(): bad rem_num");
		for(u32_t i = pos; i < size - rem_num; i++) {
			data[i] = data[i + rem_num];
		}
		size -= rem_num;
	}
	INLINE void remove(const Iterator &it) {remove(it - begin());}
		
	INLINE void removeFast(u32_t pos) {// copy last to pos, size-1
		assert(pos < size && "Vector::removeFast(): bad position");
		data[pos] = data[size - 1];
		size--;
	}
	INLINE void removeFast(const Iterator &it) {removeFast(it - begin());}
		
	u32_t size, mem;
	Type *data;
};
#endif
