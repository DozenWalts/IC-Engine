#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "Str.h"
//=============================================================================
//https://github.com/g-truc/glm/blob/master/glm/gtx/hash.inl
INLINE void hash_combine(size_t &seed, size_t hash){
	hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
	seed ^= hash;
}
// int hash combine
//https://gist.github.com/badboy/6267743
//http://burtleburtle.net/bob/hash/integer.html
//https://github.com/skeeto/hash-prospector
//https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
//https://en.wikipedia.org/wiki/List_of_hash_functions
static u32_t hash32(u32_t x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}
//u32_t unhash(u32_t x) {
//	x = ((x >> 16) ^ x) * 0x119de1f3;
//	x = ((x >> 16) ^ x) * 0x119de1f3;
//	x = (x >> 16) ^ x;
//	return x;
//}
//u64_t hash(u64_t x) {
//	x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
//	x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
//	x = x ^ (x >> 31);
//	return x;
//}
//u64_t unhash(u64_t x) {
//	x = (x ^ (x >> 31) ^ (x >> 62)) * UINT64_C(0x319642b2d24d8ec3);
//	x = (x ^ (x >> 27) ^ (x >> 54)) * UINT64_C(0x96de1b173f119089);
//	x = x ^ (x >> 30) ^ (x >> 60);
//	return x;
//}
//http://mostlymangling.blogspot.com/2018/07/on-mixing-functions-in-fast-splittable.html
//static inline uint64_t ror64(uint64_t v, int r) {
//	return (v >> r) | (v << (64 - r));
//}
//
//uint64_t rrxmrrxmsx_0(uint64_t v) {
//	v ^= ror64(v, 25) ^ ror64(v, 50);
//	v *= 0xA24BAED4963EE407UL;
//	v ^= ror64(v, 24) ^ ror64(v, 49);
//	v *= 0x9FB21C651E98DF25UL;
//	return v ^ v >> 28;
//}
//=============================================================================
//http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash
//=============================================================================
static u32_t JSHash(const char* str, u32_t len){
	u32_t hash = 1315423911;
	for(u32_t i = 0; i < len; str++, i++) hash ^= ((hash << 5) + (*str) + (hash >> 2));
	return hash;
} 
//=============================================================================
static u32_t ELFHash(const char* str, u32_t len){
	u32_t hash = 0, x = 0;
	for(u32_t i = 0; i < len; str++, i++){
		hash = (hash << 4) + (*str);
		if((x = hash & 0xF0000000L) != 0) hash ^= (x >> 24);
		hash &= ~x;
	}
	return hash;
}
//=============================================================================
const u32_t FNV_32_PRIME = 16777619u;

static u32_t FNVHash32(const u32_t input1, const u32_t input2){
	u32_t hash = 2166136261u;
	const u8_t* pBuf = (u8_t*) &input1;

	hash *= FNV_32_PRIME; hash ^= *pBuf++;
	hash *= FNV_32_PRIME; hash ^= *pBuf++;
	hash *= FNV_32_PRIME; hash ^= *pBuf++;
	hash *= FNV_32_PRIME; hash ^= *pBuf++;

	pBuf = (u8_t*) &input2;
	
	hash *= FNV_32_PRIME; hash ^= *pBuf++;
	hash *= FNV_32_PRIME; hash ^= *pBuf++;
	hash *= FNV_32_PRIME; hash ^= *pBuf++;
	hash *= FNV_32_PRIME; hash ^= *pBuf++;

	return hash;
}
//=============================================================================
//https://github.com/martinus/robin-hood-hashing/blob/master/src/include/robin_hood.h
template <typename T>
inline T unaligned_load(void const* ptr) {//noexceptnoexcept
	// using memcpy so we don't get into unaligned load problems.
	// compiler should optimize this very well anyways.
	T t;
	memcpy(&t, ptr, sizeof(T));
	return t;
}
// Hash an arbitrary amount of bytes. This is basically Murmur2 hash without caring about big
// endianness. TODO(martinus) add a fallback for very large strings?
static size_t hash_bytes(void const* ptr, size_t const len)  {
	static const uint64_t m = UINT64_C(0xc6a4a7935bd1e995);
	static const uint64_t seed = UINT64_C(0xe17a1465);
	static const unsigned int r = 47;

	auto const data64 = static_cast<uint64_t const*>(ptr);
	uint64_t h = seed ^ (len * m);

	size_t const n_blocks = len / 8;
	for (size_t i = 0; i < n_blocks; ++i) {
		auto k = unaligned_load<uint64_t>(data64 + i);

		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
	}

	auto const data8 = reinterpret_cast<uint8_t const*>(data64 + n_blocks);
	switch (len & 7U) {
		case 7:h ^= static_cast<uint64_t>(data8[6]) << 48U;
		case 6:h ^= static_cast<uint64_t>(data8[5]) << 40U;
		case 5:h ^= static_cast<uint64_t>(data8[4]) << 32U;
		case 4:h ^= static_cast<uint64_t>(data8[3]) << 24U;
		case 3:h ^= static_cast<uint64_t>(data8[2]) << 16U;
		case 2:h ^= static_cast<uint64_t>(data8[1]) << 8U;
		case 1:h ^= static_cast<uint64_t>(data8[0]); h *= m;
		default:break;
	}

	h ^= h >> r;
	h *= m;
	h ^= h >> r;
	return static_cast<size_t>(h);
}
//inline size_t hash_int(uint64_t obj) 
//https://github.com/facebook/folly/blob/master/folly/hash/Hash.h 128 to 64
//============================================================================= (u32_t)std::hash<unsigned int>()((unsigned int)k); }//
template <typename KEY>
struct hash1 {
	INLINE u32_t operator() (const KEY &k)const { return hash_bytes(&k, sizeof(KEY));}// ELFHash((const char*)&k, sizeof(KEY)); }//hash32((u32_t)k); }//
};
template <typename KEY>
struct hash2 {
	INLINE u32_t operator() (const KEY &k)const { return 1;}// hash32((u32_t)k); }//JSHash((const char*)&k, sizeof(KEY)); }// ELFHash((const char*)&k, sizeof(KEY)); }
};

template<>
struct hash1<str> {
	INLINE u32_t operator() (const str &k)const { return hash_bytes(k.text, k.size); }
};
template<>
struct hash2<str> {
	INLINE u32_t operator() (const str &k)const { return 1;}// ELFHash(k.text, k.size); }
};

#include "Math/vec3.h"
template<>
struct hash1<vec3> {
	INLINE u32_t operator() (const vec3 &k)const { return hash_bytes(k.v, sizeof(vec3)); }
};
template<>
struct hash2<vec3> {
	INLINE u32_t operator() (const vec3 &k)const { return 1; }// ELFHash(k.text, k.size); }
};

//=============================================================================
// KEY/VALUE must have default constructor
// KEY must have defined == operator
template <typename KEY, typename VALUE, typename Hasher1 = hash1<KEY>, typename Hasher2 = hash2<KEY>>
struct HashTable {

	struct node {
		KEY key;
		VALUE value;
		u32_t h1, h2;
		node() :key(), value(), h1(0), h2(0) {}
		void unuse() { h2 = 0; }// do delete
		INLINE bool is_valid() const{ return h2 != 0; }// check if it deleted
	};

	const Hasher1 hasher1;
	const Hasher2 hasher2;

	u32_t total, used;
		node **E;
	
	HashTable(u32_t start_size = 64) { init(start_size); }
	void init(u32_t start_size = 64) {
		total = start_size;
		if (isPowerOfTwo(total) == false) total = round_up_power2(total);
		used = 0;
		E = new node*[total];
		memset(E, 0, total * sizeof(node*));
	}
	~HashTable() { loop0i(total) if (E[i]) delete E[i]; delete[] E; }

	void clear() {
		loop0i(total) if (E[i]) delete E[i];
		memset(E, 0, total * sizeof(node*));
		used = 0;
	}

	void rehash(u32_t new_total) {
		u32_t new_pot = new_total;
		if (isPowerOfTwo(new_pot) == false) new_pot = round_up_power2(new_pot);
		node **NE = new node*[new_pot];
		memset(NE, 0, new_pot * sizeof(node*));
		//LOG::msg("--------------------rehash -> %i (%i/%i = %f)", new_total, used, total, (float)used / total);
		used = 0;
		loop0j(total) {
			if (!E[j] || E[j]->is_valid() == false) continue;
			//u32_t h1 = hasher1(OLDE->key);//u32_t h1=JSHash(OLDE->name.text, OLDE->name.size), h2=ELFHash(OLDE->name.text, OLDE->name.size)|1; actually stays same
			u32_t i = E[j]->h1 & (new_pot - 1);//% new_total;
			while (NE[i] && NE[i]->is_valid()) i = (i + E[j]->h2) & (new_pot - 1);//% new_total;
			NE[i] = E[j];
			//NEWE->h1=h1, NEWE->h2=h2;//renew only hashes - they same as before rehash
			E[j] = NULL;
			++used;
		}
		total = new_pot;
		delete [] E;//PVS
		E = NE;
		//LOG::msg("CRC --------- ");
		//loop0i(total) {
		//	if (E[i]) LOG::msg("CRC E[%i]=%i", i, E[i]->key);
		//}
	}

	INLINE VALUE &operator[](const KEY &k) { return get(k)->value; }
	
	node *get(const KEY &k) {
		if (used && (float)used / total > 0.666f) rehash(total * 2);

		u32_t h1 = hasher1(k);
		u32_t h2 = hasher2(k) | 1;
		u32_t i = h1 & (total - 1);

		node *ELEM = E[i];
		while (ELEM && ELEM->is_valid()) {
			if (ELEM->h1 == h1 && ELEM->h2 == h2 && ELEM->key == k) return ELEM;
			i = (i + h2) & (total - 1);// % total;
			ELEM = E[i];
		}

		if (!ELEM) { E[i] = new node(); ELEM = E[i]; }
		ELEM->key = k;//copy
		ELEM->h1 = h1, ELEM->h2 = h2;
		++used;

		return ELEM;
	}
	/*usage:
		HashTable<vec3, int> vmap;
		HashTable<vec3, int>::node *vnode;
		if(vmap.insert(sv, vnode)){// test
			vnode->value = i;// save
		}else{
			int j = vnode->value;// load
		}*/
	bool can_insert(const KEY &k, node *&n){
		if(used && (float) used / total > 0.666f) rehash(total * 2);

		u32_t h1 = hasher1(k);
		u32_t h2 = hasher2(k) | 1;
		u32_t i = h1 & (total - 1);

		node *ELEM = E[i];
		while(ELEM && ELEM->is_valid()) {
			if(ELEM->h1 == h1 && ELEM->h2 == h2 && ELEM->key == k) { n = ELEM; return false; }
			i = (i + h2) & (total - 1);// % total;
			ELEM = E[i];
		}

		if(!ELEM) { E[i] = new node(); ELEM = E[i]; }
		ELEM->key = k;//copy
		ELEM->h1 = h1, ELEM->h2 = h2;
		++used;

		n = ELEM;
		return true;
	}

	node *find(const KEY &k) const{
		u32_t h1 = hasher1(k);
		u32_t h2 = hasher2(k) | 1;
		u32_t i = h1 & (total - 1);

		node *ELEM = E[i];
		while (E[i]!=nullptr && ELEM->is_valid()) {
			if (ELEM->h1 == h1 && ELEM->h2 == h2 && ELEM->key == k) return ELEM;
			i = (i + h2) & (total - 1);// % total;
			ELEM = E[i];
		}
		return nullptr;
	}

	//u32_t i = 0;
	//while (plugins.iterate(i)) {
	//	plugins.E[i]->value->exit();
	//	++i;
	//}
	bool iterate(u32_t &counter) const{// including deleted
		if (counter >= total)return false;// paranoid?
		while (counter < total) {
			if (E[counter] != nullptr) return true;//&& E[counter]->is_valid()?
			++counter;
		}
		return false;
	}

	u32_t num_probes(const KEY &k) const{
		u32_t probes = 1;
		u32_t h1 = hasher1(k);
		u32_t h2 = hasher2(k) | 1;
		u32_t i = h1 & (total - 1);// % total;
		while (E[i] && E[i]->is_valid()) {
			if (E[i]->h1 == h1 && E[i]->h2 == h2 && E[i]->key == k)	return probes;
			++probes;
			i = (i + h2) & (total - 1);//% total;
		}
		return probes;
	}

	void complexity_info() const{
		LOG::msg(" total=%i used=%i", total, used);
		u32_t *probe_count = new u32_t[100];
		memset(probe_count, 0, 100 * sizeof(u32_t));
		u32_t max_probes = 0;
		loop0i(used) {
			u32_t pn = num_probes(i);
			if (pn > 99) debug_break();
			max_probes = mmax(pn, max_probes);
			++probe_count[pn];
		}
		u32_t reads = 0;
		loopi(1, max_probes) {
			reads += probe_count[i] * i;
			LOG::msg("num probes %i, count = %i", i, probe_count[i]);
		}
		LOG::msg("average element read times = %f ", (float)reads / used);
		LOG::msg("oneshoot access elements %.0f%%", (float)probe_count[1] / used * 100);
		delete[] probe_count;
	}
};
//=============================================================================

//complexity = 58908 (1.963600) hash32, JSHash
//complexity = 59059 (1.968633) hash32, ELFHash
//complexity = 65405 (2.180167) hash32, hash32
//complexity = 79772 (2.659067) JSHash, ELFHash
//complexity = 80354 (2.678467) JSHash, hash32
//complexity = 99413 (3.313767) ELFHash, JSHash
// debug   200k - 7min complexity = 403652 (2.018260) hash32, JSHash
// release 200k - 4min complexity = 403652 (2.018260)
//UM[i] = i;// 200k=0.061703 3M=1.026438
//HT[i] = i;// 200k=0.042695 3M=1.282597, [%->& == -088ms] 3M=1.194058, [E[i]->ELEM == -020ms] 1.173824, [h1->1 == -190ms] 0.983489

#endif
