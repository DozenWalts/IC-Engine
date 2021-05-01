#ifndef __BASETYPE_H__
#define __BASETYPE_H__

#include <math.h>// not for platform toolset (v141,v140); works with (v120, v120_xp, v140_xp, v141_xp); SDK 7.0 -> SDK 10.xx
#include <stdio.h>// FILE vsnprintf 
//#include <stdlib.h>// malloc, calloc, realloc, free
#include <stdarg.h>// va_list, va_start, va_arg, va_end
#include <string.h>// memset, memcpy, strcmp, strlen

#ifdef _WIN32
	#include <windows.h>
#endif

//============================================================================= ASSERT

#ifdef _WIN32
#define FUNC_NAME __FUNCTION__//__FUNCSIG__
#else
#define FUNC_NAME __PRETTY_FUNCTION__
#endif
//#if defined(_MSC_VER)
//#define ABSL_PRETTY_FUNCTION __FUNCSIG__
//#elif defined(__GNUC__)
//#define ABSL_PRETTY_FUNCTION __PRETTY_FUNCTION__
//#else
//#error "Unsupported compiler"
//#endif
////#if defined(__GNUC__)
////#	define FUNCTION __PRETTY_FUNCTION__
////#elif defined(_MSC_VER)
////#	define FUNCTION __FUNCSIG__
////#else
////#	define FUNCTION __func__
////#endif

#ifdef _WIN32
#define INLINE		__forceinline
#define FASTCALL	__fastcall
#define RESTRICT	__restrict
#else
#define INLINE		__inline__
#define FASTCALL
#define RESTRICT	__restrict
#endif

//https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak

#ifdef NDEBUG
#define DEBUG_BREAK ;
#else
#ifdef _WIN32
#define DEBUG_BREAK DebugBreak();
#elif __linux
#define DEBUG_BREAK __debugbreak();
#endif
#endif

static void error_stop(const char *e) {
#ifdef _WIN32
	if (MessageBoxA(0, e, "Error", MB_OKCANCEL) == IDOK) exit(0);
#else
	abort();
#endif
}

//C4996: 'vsprintf': This function or variable may be unsafe. 
//Consider using vsprintf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.	
//e:\code\handy\handy\str.cpp:28
//#define _CRT_SECURE_NO_WARNINGS

#define USE_ASSERT

#ifdef USE_ASSERT
#include "Sys/Log.h"
#ifdef assert
#undef assert
#endif
#ifdef NDEBUG
#define assert(EXP)	(static_cast<void>(0))
#else
	//#ifdef __linux
	//	#define assert(EXP) { if(EXP) { } else { LOG::err("[%s:%d:%s] Assert: [%s]",__FILE__,__LINE__,FUNC_NAME,#EXP); __debugbreak();} }
	//#else
#define assert(EXP) { if(EXP) { } else { LOG::err("[%s:%d:%s] Assert: [%s]",__FILE__,__LINE__,FUNC_NAME,#EXP); DEBUG_BREAK} }
//#endif
#endif
#endif

#ifdef _WIN32

#include <signal.h>
INLINE void signal_handler(int signum) {
	//_Tracer.print();
	// print out all the frames to stderr
	LOG::err("Error: signal ", signum);
	switch (signum) {
		case SIGABRT: LOG::err(" SIGABRT");  break;
		case SIGSEGV: LOG::err(" SIGSEGV");  break;
			//case SIGBUS:  name = " SIGBUS";   break;
		case SIGILL:  LOG::err(" SIGILL");   break;
		case SIGFPE:  LOG::err(" SIGFPE");   break;
	}
	system("notepad engine_log.html");
	exit(1);
}

#define ERROR_CATCHER catch (std::exception &e) { \
	LOG::err("in [%s] exeption [%s] std err [%s]", __FUNCTION__ ,e.what(), strerror(errno)); signal_handler(100);\
	} catch (...) {\
		LOG::err("unknown error at ", __FUNCTION__ ); signal_handler(200);\
	}

static void init_ExeptionCatcher() {
	/* 1) SIGHUP       2) .SIGINT       3) SIGQUIT      4) .SIGILL       5) SIGTRAP
	 6) .SIGABRT      7) SIGEMT       8) .SIGFPE       9) SIGKILL     10) SIGBUS
	11) .SIGSEGV     12) SIGSYS      13) SIGPIPE     14) SIGALRM     15) .SIGTERM
	16) SIGURG      17) SIGSTOP     18) SIGTSTP     19) SIGCONT     20) SIGCHLD
	21) SIGTTIN     22) SIGTTOU     23) SIGIO       24) SIGXCPU     25) SIGXFSZ
	26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGPWR      30) SIGUSR1*/
	for (int i = 1; i < NSIG; i++) {
		// An invalid parameter was passed to a function that considers invalid parameters fatal.
		// Processor Feature FastCall
		if (i == 5)continue;
		if (i == 7)continue;
		if (i == 9)continue;
		if (i == 10)continue;
		if (i == 12)continue;
		if (i == 14)continue;
		if (i == 18)continue;
		if (i == 19)continue;
		if (i == 20)continue;
		//LOG::msg("set signal %i",i);
		signal(i, signal_handler);
	}
	//_set_se_translator([](unsigned int u, EXCEPTION_POINTERS *pExp) {
	//	std::string error = "SE Exception: ";
	//	switch (u) {
	//		case 0xC0000005:
	//			error += "Access Violation";
	//			break;
	//		default:
	//			char result[11];
	//			sprintf_s(result, 11, "0x%08X", u);
	//			error += result;
	//	};
	//	throw std::exception(error.c_str());
	//});
}
#endif

//============================================================================= MEMORY

// ! WARNING ! resizing structs with !internal pointers! to resizing array cauze invalidation
#define RESIZE(ptr,type,size){\
type *tmp=(type*)realloc(ptr,sizeof(type)*(size));\
if(!tmp){LOG::err("can't resize [%i]x[%i] at [%s:%i][%s]",size,sizeof(type),__FILE__,__LINE__,FUNC_NAME);}\
ptr=(type*)tmp;}//

#define ALLOC(ptr,type,size){\
type *tmp = (type*)malloc(sizeof(type)*(size));\
if(!tmp){LOG::err("can't alloc [%i]x[%i] at [%s:%i][%s]",size,sizeof(type),__FILE__,__LINE__,FUNC_NAME);}\
ptr=(type*)tmp;}//

#define FREE(ptr)\
if(ptr){free(ptr);ptr=NULL;};

// DELETE(nullptr) - ok
#undef DELETE
#define DELETE(ptr)\
delete ptr;ptr=NULL;

#define NEW(type,size)\
 new type[size];

 //#define FREEARR(ptr)\
//if(ptr){delete [] ptr;delete ptr};

	  /*https://github.com/i-saint/scribble/blob/master/memset.cpp
	  $ cl /Ox /GL /arch:SSE2 memset.cpp
	  $ ./memset
	  fill 4194304 byte, 1024 times
	  memset: 137.229843ms	 +3ms
	  std::fill_n<uint16>: 135.547592ms	+1ms
	  std::fill_n<uint32>: 134.988266ms		 <- fastest
	  std::fill_n<uint64>: 912.609436ms
	  std::fill_n<uint128>: 451.081573ms
	  memset64: 172.819122ms	+45ms
	  memset128: 172.916916ms
	  */

#ifndef mmin
#define mmin(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef mmax
#define mmax(a,b) ((a)>(b)?(a):(b))
#endif

//============================================================================= TYPES
#include <cstdint> // limits
//============================================================================= INTEGER

// 8 bits 1 byte
#define I8_MIN	INT8_MIN// ((int8_t)_I8_MIN)
#define I8_MAX	INT8_MAX// _I8_MAX
#define U8_MAX	UINT8_MAX//_UI8_MAX
typedef int8_t  i8_t;// 1byte [-128 .. 127] -(2^7) .. 2^7-1
typedef uint8_t u8_t;// 1byte [0 .. 255] 2^8-1

// 16 bits 2 byte
#define I16_MIN	INT16_MIN//((int16_t)_I16_MIN)
#define I16_MAX	INT16_MAX//_I16_MAX
#define U16_MAX UINT16_MAX//  _UI16_MAX
typedef int16_t   i16_t;// 2byte [-32,768 .. 32,767] -(2^15) .. 2^15-1
typedef uint16_t  u16_t;// 2byte [0 .. 65,535] 2^16-1

// 32 bits 4 byte
#define I32_MIN	INT32_MIN//((int32_t)_I32_MIN)
#define I32_MAX	INT32_MAX//_I32_MAX
#define U32_MAX UINT32_MAX
typedef int32_t  i32_t;// 4byte [-2,147,483,648 .. 2,147,483,647] -(2^31) .. 2^31-1
typedef uint32_t  u32_t;// 4byte [0 .. 4,294,967,295] (2<<32)-1 == 2^32-1 == 1024^3*4 - 4Gb?

// 64 bits 8 byte
#define I64_MIN	INT64_MIN//((int64_t)_I64_MIN)
#define I64_MAX	INT64_MAX//_I64_MAX
#define U64_MAX UINT64_MAX//  _UI64_MAX											//  3.485.338.198.035.398.655
typedef int64_t   i64_t;// 8byte [-9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807] -(2^63) .. 2^63-1
typedef uint64_t  u64_t;// 8byte [0 .. 18.446.744.073.709.551.615] 2^64-1 1024^6*16 - 18Eb?
//										2.224.430.241.965.670.399
//UINT64_MAX 18446744073709551615ULL

//#ifndef Oword	  
// /*128bit:Signed: From ?170,141,183,460,469,231,731,687,303,715,884,105,728 to 170,141,183,460,469,231,731,687,303,715,884,105,727, from ?(2^127) to 2^127 ? 1
//		  Unsigned: From 0 to 340,282,366,920,938,463,463,374,607,431,768,211,455 which equals 2^128 ? 1*/
// #define Oword long long long long   ???
//#endif

// a=target variable, b=bit number to act upon 0-n
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) (((a) & (1<<(b)))!=0)
// x=target variable, y=mask
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK(x,y) ((x) & (y))

//shr >> divide   (16>>2= 4)==(16/4= 4)
//shl << multiply (16<<2=64)==(16*4=64)
//2^x=y -> x=ln(y)/ln(2)
//i * 2 = i << 1
//i * 3 = (i << 1) + i;
//i * 10 = (i << 3) + (i << 1)
//i & ~3 - целая часть от деления на 4,8,16...2^n
//i &  3 - остаток деления на 4

//The last 3 bits of the integer are: x & 0x7
//The five bits starting from the eight-last bit are: x >> 3  // all but the last three bits
//													  & 0x1F  // the last five bits.
//first 5 bits:				  (x >> 3) & ((1 << 5)-1); or (x >> 3) & 31;
//To fetch the lower three bits: (x >> 0) & ((1 << 3)-1); or x & 7;

//typedef __int128_t int128;
//typedef __uint128_t uint128;
//
//int print_uint128(uint128_t n) {		https://gist.github.com/zed/7f7e7451b60aff301fe0
//	if (n == 0)  return printf("0\n");
//
//	char str[40] = { 0 }; // log10(1 << 128) + '\0'
//	char *s = str + sizeof(str) - 1; // start at the end
//	while (n != 0) {
//		if (s == str) return -1; // never happens
//
//		*--s = "0123456789"[n % 10]; // save last digit
//		n /= 10;					 // drop it
//	}
//	return printf("%s\n", s);
//}
//void print_uint128(uint128_t n){
//	if (n == 0) {return;}
//	print_uint128(n / 10);
//	putchar(n % 10 + 0x30);
//}
//char * sprintf_int128(__int128_t n) {
//	static char str[41] = { 0 };		// sign + log10(2**128) + '\0'
//	char *s = str + sizeof(str) - 1;  // start at the end
//	bool neg = n < 0;
//	if (neg)
//		n = -n;
//	do {
//		*--s = "0123456789"[n % 10];	// save last digit
//		n /= 10;				// drop it
//	} while (n);
//	if (neg)
//		*--s = '-';
//	return s;
//}

//uint128  x = (uint128)123;
//
//printf("__int128 max  %016"PRIx64"%016"PRIx64"\n", (uint64)(x >> 64), (uint64)x);
//typedef unsigned __int128 uint128_t;
//#define I128_MIN 
//typedef __m128i i128_t;
// ...... [0 .. 340,282,366,920,938,463,463,374,607,431,768,211,455] 2^128-1

//Round down to even x & ~1
//Round up to even (x + 1) & ~1
// If n is a power of 2, (i/n) is equivalent to (i >> log2(n)) and (i%n) is equivalent to (i & (n-1)). 

// static inline?
static int GCD(int a, int b) { return b ? GCD(b, a%b) : a; }// greatest common divisor of A and B
static int MaxDivPow2(int n) { return n & -n; }// max power_of_two number, inside n

//Round up to the next highest power of 2
static u32_t round_up_power2(u32_t v) { // compute the next highest power of 2 of 32-bit v
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
static inline bool isPowerOfTwo(u32_t x) { return ((x & (x - 1)) == 0); };//constant time, data independent

static u32_t flp2(u32_t x) {//Rounding Down power2 http://www.pearsonhighered.com/samplechapter/0201914654.pdf
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x - (x >> 1);
}
static u32_t clp2(u32_t x) {//Rounding Up power2
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x + 1;
}
static u8_t msb(u32_t v) {// Find the log base 2 of an N-bit integer in O(lg(N)) operations   /// Return the most significant on bit of the given 32-bit value.
	v |= v >> 1; // first round down to one less than a power of 2  
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	static const u8_t MultiplyDeBruijnBitPosition[32] = {
		0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
		8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
	};
	return MultiplyDeBruijnBitPosition[(u32_t)(v * 0x07C4ACDDU) >> 27];
}

static u8_t lsb(u32_t v) {//Count the consecutive zero bits (trailing) on the right	/// Return the least significant on bit of the given 32-bit value.
	//u32_t x=v;
	//x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	//x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	//x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	//x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	//v=((x >> 16) | (x << 16));//resersed v
	static const u8_t MultiplyDeBruijnBitPosition[32] = {
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};
	return MultiplyDeBruijnBitPosition[((u32_t)((v & -int(v)) * 0x077CB531U)) >> 27];
}

/// Return the number of on bits in the given 32-bit value.  https://github.com/dreamworksanimation/openvdb/blob/master/openvdb/util/NodeMasks.h
static inline u32_t CountOn(u32_t v) {
	v = v - ((v >> 1) & 0x55555555U);
	v = (v & 0x33333333U) + ((v >> 2) & 0x33333333U);
	return (((v + (v >> 4)) & 0xF0F0F0FU) * 0x1010101U) >> 24;
}
//u64_t countOnes64(u64_t n) {
//	n -= (n >> 1) & 0x5555555555555555llu;
//	n = ((n >> 2) & 0x3333333333333333llu) + (n & 0x3333333333333333llu);
//	n = ((((n >> 4) + n) & 0x0F0F0F0F0F0F0F0Fllu) * 0x0101010101010101) >> 56;
//	return n;
//}

static u32_t reverse_bits(register u32_t x) {// register is deprecated in c++17
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	return((x >> 16) | (x << 16));
}

static u32_t ChangeEndianness(u32_t value) {//https://en.wikipedia.org/wiki/Endianness#Method_of_mapping_registers_to_memory_locations
	u32_t result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return result;
}

//inline uint32_t endian_swap(uint32_t value){
//	return ((value & 0xff) << 24) | ((value & 0xff00) << 8) | ((value & 0xff0000) >> 8) | (value >> 24);
//}
//
//inline uint16_t endian_swap(uint16_t value){
//	return static_cast<uint16_t>(((value & 0xff) << 8) | (value >> 8));
//}
//bool is_little_endian(){
//	unsigned int ui = 1;
//	return *reinterpret_cast<unsigned char*>(&ui) == 1;
//}

//============================================================================= MACRO LOOP

//rloop
#define iloop0i(end_l)for(int i=(end_l)-1;i>=0;i--)

#define loop0i(end_l) for(u32_t i=0;i<(end_l);++i)
#define loop0j(end_l) for(u32_t j=0;j<(end_l);++j)
#define loop0k(end_l) for(u32_t k=0;k<(end_l);++k)
#define loop0l(end_l) for(u32_t l=0;l<(end_l);++l)
#define loop0m(end_l) for(u32_t m=0;m<(end_l);++m)
#define loop0n(end_l) for(u32_t n=0;n<(end_l);++n)
#define loopi(start_l,end_l) for(i32_t i=(start_l);i<(end_l);++i)
#define loopj(start_l,end_l) for(i32_t j=(start_l);j<(end_l);++j)
#define loopk(start_l,end_l) for(i32_t k=(start_l);k<(end_l);++k)
#define loopl(start_l,end_l) for(i32_t l=(start_l);l<(end_l);++l)
#define loopm(start_l,end_l) for(i32_t m=(start_l);m<(end_l);++m)
#define loopn(start_l,end_l) for(i32_t n=(start_l);n<(end_l);++n)

//============================================================================= FLOATING POINT
//Assuming IEEE 754 representation: http://www.learncpp.com/cpp-tutorial/25-floating-point-numbers/
//Size					Range									Precision
//4 bytes				±1.18 x 10 - 38 to ±3.4 x 1038			6 - 9 significant digits, typically 7
//8 bytes				±2.23 x 10 - 308 to ±1.80 x 10308		15 - 18 significant digits, typically 16
//80 - bits(12 bytes)	±3.36 x 10 - 4932 to ±1.18 x 104932		18 - 21 significant digits
//16 bytes				±3.36 x 10 - 4932 to ±1.18 x 104932		33 - 36 significant digits

//Maximum digit counts for select IEEE floating - point formats
//			Max Integer Digits	|		Max Fraction Digits
//Format	Total / Significant	| Total		Leading Zero	Significant
//float		39					| 149		37				112
//double	309					| 1074		307				767
//quad		4933				| 16494		4931			11563
//https://www.cs.mcgill.ca/~chang/teaching/cs350/doc/overton_ieee.pdf

//============================================================================= FLOAT
// 32 bits 4 byte, [1-sign|8-exp|23-mant]
typedef float f32_t;// 4byte [±1.18x10-38 .. ±3.4x1038] -(2^126) .. 2^127-1 (Precision: 6-9 significant digits, typically 7)
const float F32_MAX = 0x7f7fffff;//std::numeric_limits<float>::max();//(float) 0x7f7fffff;//3.40282347E+38F;//FLT_MAX;
const float F32_MIN = -F32_MAX;//std::numeric_limits<float>::lowest();//(float)0x00800000;//1.17549435E-38F;//FLT_MIN;	0x1p-126;//
const float EPSILON = 1e-6f;
const float iEPSILON = 1.0f - EPSILON;
const float EPSILONSQ = EPSILON * EPSILON;
const float F32_TOLERANCE = 1e-8f;

#define	F_NAN(x)			(((*(const u64_t*)&x) & 0x7f800000) == 0x7f800000)
#define F_INF(x)			(((*(const u64_t*)&x) & 0x7fffffff) == 0x7f800000)
#define F_IND(x)			 ((*(const u64_t*)&x) == 0xffc00000)
#define	FLOAT_IS_DENORMAL(x)(((*(const u64_t*)&x) & 0x7f800000) == 0x00000000 && \
					   		 ((*(const u64_t*)&x) & 0x007fffff) != 0x00000000 )

// gap num = 2^(p-1)
// gap size = 2^(e+1-p)

//============================================================================= DOUBLE

// 64 bits 8 byte, [1-sign|11-exp|52-mant]
typedef double f64_t;// 8byte [±2.23x10-308 .. ±1.80x10308] -(2^1022) .. 2^1023-1 (Precision: 15-18 significant digits, typically 16)
//const f64_t f46_eps = 2 ^ (-52);
//const f64_t f64_min = 2 ^ (-1022);
//const f64_t f64_max = (2-f64_eps) * (2 ^ 1023);
const double F64_TOLERANCE = 1e-15;

//typedef ??? f128_t;//

#include <math.h>

static const float PI = 3.14159f;// - 7 accurate digits// 3.14159265358979323846264338327950288f;//3.14159265358979323846f
//static const f64_t PI = 3.14159265358979;// - 16 accurate digits

 //const double PI = 4 * atan(1);//atan2(0, -1)//acos(-1)
 //#define pi_times(n) (((n) * 22) / 7) Return approximation of n * PI; n is integer //For more accuracy use 355 / 113
static const float HPI = 1.57079632679489661923132169163975144f;//1.57079632679489661923f //HALF PI
//#define HPI PI/2.0f
static const float TAU = 6.28318530717958647692528676655900577f;//6.283185307f
static const float PI_SQR = 9.86960440108935861883449099987615114f;//9.86960440108935861883449099987615114f;
//sin(double(pi)) = +0.0000000000000001224646799147353207
//pi - double(pi) = +0.0000000000000001224646799147353177
//sin(float(pi)) = -0.000000087422776
//pi - float(pi) = -0.000000087422780

//============================================================================= COMPARE FLOATS
#define SK_ScalarNearlyZero (1.0f / (1 << 12))

inline bool isApproxEqual(const float a, const float b){
	return !(fabs(a - b) > F32_TOLERANCE);
}
static inline bool equal(float a, float b) { const float d = a - b; return (d<0.001f && d>-0.001f); }
/*// aUnitsInLastPlace is the allowed difference between the least significant digits
// of the numbers' floating point representation
// Please read refernce paper before trying to use isUlpsEqual
// http://www.cygnus-software.com/papers/comparingFloats/comparingFloats.htm
inline bool isUlpsEqual(const double aLeft, const double aRight, const int64_t aUnitsInLastPlace)
{
	int64_t longLeft = doubleToInt64(aLeft);
	// Because of 2's complement, must restore lexicographical order
	if (longLeft < 0) {
		longLeft = INT64_C(0x8000000000000000) - longLeft;
	}

	int64_t longRight = doubleToInt64(aRight);
	// Because of 2's complement, must restore lexicographical order
	if (longRight < 0) {
		longRight = INT64_C(0x8000000000000000) - longRight;
	}

	int64_t difference = labs(longLeft - longRight);
	return (difference <= aUnitsInLastPlace);
}

inline bool isUlpsEqual(const float aLeft, const float aRight, const int32_t aUnitsInLastPlace)
{
	int32_t intLeft = floatToInt32(aLeft);
	// Because of 2's complement, must restore lexicographical order
	if (intLeft < 0) {
		intLeft = 0x80000000 - intLeft;
	}

	int32_t intRight = floatToInt32(aRight);
	// Because of 2's complement, must restore lexicographical order
	if (intRight < 0) {
		intRight = 0x80000000 - intRight;
	}

	int32_t difference = abs(intLeft - intRight);
	return (difference <= aUnitsInLastPlace);
}*/

//============================================================================= HALF FLOAT
/*void half::setFloat(float v) {
	unsigned int i = IntFloat(v).ui;
	unsigned int e = (i >> 23) & 0x00ff;
	unsigned int m = i & 0x007fffff;
	if(e <= 127 - 15) {
		h = ((m | 0x00800000) >> (127 - 14 - e)) >> 13;
	} else {
		h = (i >> 13) & 0x3fff;
	}
	h |= (i >> 16) & 0xc000;
}

float half::getFloat() const {
	unsigned int f = (h << 16) & 0x80000000;
	unsigned int em = h & 0x7fff;
	if(em > 0x03ff) {
		f |= (em << 13) + ((127 - 15) << 23);
	} else {
		unsigned int m = em & 0x03ff;
		if(m != 0) {
			unsigned int e = (em >> 10) & 0x1f;
			while((m & 0x0400) == 0) {
				m <<= 1;
				e--;
			}
			m &= 0x3ff;
			f |= ((e + (127 - 14)) << 23) | (m << 13);
		}
	}
	return IntFloat(f).f;
}*/

//============================================================================= VECTOR
#define Y_UP
//#define Z_UP
#ifdef Y_UP
	#define YAW   0 //around up
	#define ROLL  1 //around dir
	#define PITCH 2 //around right

	#define VRT 0
	#define VUP 1
	#define VDR 2
#endif

#ifdef Z_UP
	#define ROLL  0
	#define PITCH 1
	#define YAW   2
	#define VDR 0
	#define VRT 1
	#define VUP 2
#endif
//============================================================================= ANGLE
#define D2R (PI/180.0f)
#define R2D (180.0f/PI)

//inline float wrapAngle( float angle ){return angle - TAU * floor( angle / TAU );}//http://stackoverflow.com/questions/11980292/how-to-wrap-around-a-range
static inline float wrapAngle(float a) {//0..tau
	return a - TAU * floor(a / TAU);
	//a = fmod(a, TAU);
	//if (a < 0.0) a += TAU;
	//return fmod(a + 8 * PI, TAU);
	//return NormRad(a);
	//while ( a >  PI ) a -= TAU;  
	//while ( a < -PI ) a += TAU;
// return a;
}
//float normalizeAngle(float angle) {
//	if(angle < 0.0f || angle >= 360.0f) angle -= Math::floorf(angle * (1.0f / 360.0f)) * 360.0f;
//	if(angle > 180.0f) angle -= 360.0f;
//	return angle;
//} 
INLINE float normAngle(const float &a, const float &period) {
	float r = a;
	float hper = period / 2;
	while (r >= hper) r -= period;
	while (r < -hper) r += period;
	return r;
}
static float normRAD(const float &a) {return normAngle(a, TAU);}
static float normDEG(const float &a) {return normAngle(a, 360);}

static float angleMod(float angle){// from openvdb, openexr
	angle = fmod(angle, TAU);
	if (angle < -PI) angle += TAU;
	if (angle > +PI) angle -= TAU;
	return angle;
}
// no negative values
static inline float anglemod(float a) { a = (360.f / 65536) * ((int)(a*(65536.f / 360.0f)) & 65535);	return a; }

static float cfmod(float a, float n) {
	return a - floor(a / n) * n;
}

static float DegAngleDiff(float angle1, float angle2) {
	float diff = cfmod((angle2 - angle1 + 180), 360 - 180);
	return diff < -180 ? diff + 360 : diff;
}
static float RadAngleDiff(float angle1, float angle2) {
	float adif = angle2 - angle1;
	//if(abs(adif) < PI) return adif;
	float diff = cfmod(adif, TAU);
	if (diff > PI) diff -= TAU;
	return diff;
	//LOG::msg("diff(%f %f) = %f(%f)", angle1, angle2, diff,(diff < -PI ? diff + TAU : diff));
	//return diff < -PI ? diff + TAU : diff;
}


//============================================================================= CONVERT
// dtoa https://www.ampl.com/netlib/fp/dtoa.c

//============================================================================= F32->I32
//union FloatInt {
//	float f;
//	i32_t i;
//};
//i32_t floatToInt(float f){
//	i32_t r;
//	memcpy(&r, &f, sizeof(float));
//	return r;
//}
//inline int ftoi_fast(float f){// x64 cant
//	int i;
//	__asm{
//		fld f
//		fistp i
//	}
//	return i;
//}

/* See
https://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/		https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
for the potential portability problems with the union and bit-fields below.
*/
//#include <stdint.h> // For int32_t, etc.
//
//union Float_t{
//	Float_t(float num = 0.0f) : f(num) {}
//	// Portable extraction of components.
//	bool Negative() const { return i < 0; }
//	int32_t RawMantissa() const { return i & ((1 << 23) - 1); }
//	int32_t RawExponent() const { return (i >> 23) & 0xFF; }
//
//	int32_t i;
//	float f;
//#ifdef _DEBUG
//	struct{   // Bitfields for exploration. Do not use in production code.
//		uint32_t mantissa : 23;
//		uint32_t exponent : 8;
//		uint32_t sign : 1;
//	} parts;
//#endif
//};
//
//bool AlmostEqualUlps(float A, float B, int maxUlpsDiff){
//	Float_t uA(A);
//	Float_t uB(B);
//
//	// Different signs means they do not match.
//	if (uA.Negative() != uB.Negative()){
//		// Check for equality to make sure +0==-0
//		if (A == B) return true;
//		return false;
//	}
//
//	// Find the difference in ULPs.
//	int ulpsDiff = abs(uA.i - uB.i);
//	if (ulpsDiff <= maxUlpsDiff)
//		return true;
//
//	return false;
//}

#ifdef _WIN32
	//#pragma warning(disable : 4996)
//	INLINE float floor(float f) { return floorf(f); }
	int INLINE floor_fast(const float x) { return x < 0 ? (int)x == x ? (int)x : (int)x - 1 : (int)x; }
	//INLINE float sqrt(float f) { return sqrtf(f); }
	//INLINE float cos(float f) { return cosf(f); }
	//INLINE float sin(float f) { return sinf(f); }
	//INLINE float asin(float f) { return asinf(f); }
	//INLINE float acos(float f) { return acosf(f); }
	//INLINE float tan(float f) { return tanf(f); }
	//INLINE float atan(float f) { return atanf(f); }
	//INLINE float atan2(float x,float y) { return atan2f(x,y); }
	//INLINE float fabs(float f) { return fabsf(f); }
	//INLINE float atof(float f) { return atof(f); }
#endif

static float sign(float a) { return a < 0.0f ? -1.0f : 1.0f; }//??
static bool sign_bit(float a) { return a < 0.0f; }

//inline float what_power_of_two(u64_t n){return log(n)/log(2);} TODO: test

static inline float lerp(float a, float b, float t){return a+(b-a)*t;}//redo
//inline float ler(float a, float b, float t){return (1.0f-t)*a + t*b;};//http://devblogs.nvidia.com/parallelforall/lerp-faster-cuda/
 
static inline float clamp(const float &x,const float &a,const float &b){return x<a?a:x>b?b:x;}
static inline int   clamp(int x,int a,int b){return x<a?a:x>b?b:x;}
static inline float remap(const float &val,const float &omn,const float &omx,const float &nmn,const float &nmx){return nmn + ((val-omn) * (nmx-nmn)) / (omx-omn);}
static inline float clamp_remap(const float &val,const float &omn,const float &omx,const float &nmn,const float &nmx){return nmn + ((clamp(val,omn,omx)-omn) * (nmx-nmn)) / (omx-omn);}
template<typename T> void Tswap(T &a,T &b){T tmp=a;a=b;b=tmp;}
static inline float fract(float f){ return f-(long)f;}
static inline float smoothstep3( float x ) { return x*x*(3.0f-x*2.0f); }

//  return e >= t ? 0 : t >= n ? 1 : (t = (t - e) / (n - e), t * t * (3 - 2 * t))
//},
//smootherstep: function(t, e, n) {
//	return e >= t ? 0 : t >= n ? 1 : (t = (t - e) / (n - e), t * t * t * (t * (6 * t - 15) + 10))
// inline float min(float a, float b){return (a<b)?a:b;};
// inline float max(float a, float b){return (a>b)?a:b;}
// inline float sqrt(float value){return sqrtf(value);}//assert(value>=0);
 //inline float sin(float radians){return sinf(radians);}
 //inline float cos(float radians){return cosf(radians);}
 //inline float tan(float radians){return tanf(radians);}
 //inline float asin(float value){return asinf(value);}
 //inline float acos(float value){return acosf(value);}
 //inline float atan2(float y, float x){return atan2f(y,x);}
 //inline float floor(float value){return floorf(value);}
 //inline float ceiling(float value){return ceilf(value);}
 //inline float abs(float v){return fabsf( v );}
 //loop0i(50)LOG::ERR("%i - %i",i & ~7,i & 7);

// Remap a value in the range [A,B] to [C,D].
static inline float RemapVal( float val, float A, float B, float C, float D){return C + (D - C) * (val - A) / (B - A);}

//inline float snap(float p, float grid){return grid*floor(p/grid)+0.5;};//return floor((p + grid*0.5f)/grid) * grid;};//grid!=0.0f ? float( floor((p + grid*0.5f)/grid) * grid) : p;};
/*float snap(float val,float dig){//true!
 float pw=10;
 if(dig<0){for(int i=0;i>dig;i--){pw*=0.1f;};}else{for(int i=0;i<dig;i++){pw*=10;};};
 if(val<0){return (((float)((int)(val*pw-0.5f)))/pw);}else{return (((float)((int)(val*pw+0.5f)))/pw);};
};// */
static inline float snap(float v,float g){if(!v || g<EPSILON)return v;return g*(floor(v/g+0.5f));}//	|| g==1
static inline float round10(float v){return powf(10.0f, floorf(log10f(v)));}//----------------------------------- float round to nearest 10 (0.01,0.1,1,10,100...)
//log2==(log(v)/log(2)); http://www.flounder.com/log2.htm
static inline float round2(float v) {return powf( 2.0f, floorf(logf(v)/logf(2.0f)));}//---------------- give multiplayer to nearest power of 2 (0.125,0.25,0.5,1,2,4,8,16)
//inline float Align(float value, float size){
//	// Added std::abs to give correct behaviour for negative values
//	return value - abs(fmod(value, size));
//}
//============================================================================= APPROXIMATIONS
static float ssqrt( float x ) {//2005 Id Software, http://renderfeather.googlecode.com/hg-history/034a1900d6e8b6c92440382658d2b01fc732c5de/Doc/optimized%2520Matrix%2520quaternion%2520conversion.pdf 
	float y = x*0.5f; 
	long i = *(long*)(&x);   // may be not portable cppcheck
	i = 0x5f3759df - (i >> 1); 
	float r = *(float*)(&i);	//warning cppcheck
	r = r*(1.5f - r * r * y); 
	return r; 
}
static float Q_rsqrt( float number ){//http://en.wikipedia.org/wiki/Fast_inverse_square_root
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;					   // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );			   // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return y;
}

//http://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b
//inline float inv(float x){ //1/22	  NOTICEBLY ERROR
// u32_t *i = (u32_t*)&x;// re-interpret as a 32 bit integer
// *i = 0x7F000000 - *i;//error 8% adjust exponent 
// //*i = 0x7EEEEEEE - *i;//error 4% - better, but can't inverse 1
// return x;
//};
static inline float isqrf(float x){//error 5% 
	u16_t *i = (u16_t*) &x;// access float with integer logic
	*i = 0x5F375A86 - (*i>>1);// approximation with empirically found "magic number"
	return x;
}
static inline float isqr(float x){//error 5% 
	float xHalf = 0.5f*x;// for Newton iteration
	u16_t *i = (u16_t*) &x;// same as above
	*i = 0x5F375A86 - (*i>>1);
	return x * (1.5f - xHalf*x*x);// one Newton iteration, repeating further improves precision
}
static inline float sqr(float x) { return x * x; }
//static inline float sqr(float x){//error 5% test - this->sqr(80.8) != sqr(80.8)
//	u16_t i = *(u16_t*) &x;
//	i  += (u16_t)(127 << 23);// adjust bias
//	i >>= 1;// approximation of square root
//	return *(float*) &i;
//}
static inline i32_t ftol(const float &f){
	//return i32_t(f);			
	float y = f + 1.f;		  //  http://stereopsis.com/FPU.html
	return ((unsigned long&)y) & 0x7FFFFF;	// last 23 bits
}

//============================================================================= clip 2d line with AABB
/*/ p is denominator in division and q is numerator
// t1 is t entering and t2 is t leaving
int cliptest(float p,float q,float *t1,float *t2){
	float t=q/p;
	if(p<0.0f){//potentially entry point ,update te
		if(t>*t1) *t1=t;
		if(t>*t2) return 0; //line portion is outside as in line no 2 where t(entering)
							// has become more than t(leaving)
	}else if(p>0.0f){ //potentially leaving point ,update tl
		if(t<*t2) *t2=t;
		if(t<*t1) return 0; //line portion is outside
	}else if(p==0.0f) if(q<0.0f) return 0;//line parallel to edge but outside
	return 1;
}
void liang_barasky_line_clip(vec2 a,vec2 b,vec4 w,vec4 vp){
	//float dx=x1-x0, dy=y1-y0, te=0.0f, tl=1.0f;
	vec2 d = a-b;
	vec2 uv(0.0f, 1.0f);
	//if(cliptest(-dx,x0-xmin,&te,&tl))// inside test wrt left edge
	if(cliptest(-d.x, a.x-w.x, &uv.x, &uv.y))
	// t for the left edge is t=(xmin-x0) /dx .... order of numerator is reversed and you get -dx
	//if(cliptest(dx,xmax-x0,&te,&tl))// inside test wrt right edge
	if(cliptest( d.x, w.z-a.x, &uv.x, &uv.y))
	// t for the right edge is t=(xmax-x0)/dx.... first parameter becomes q and second p then t=q/p 
	//if(cliptest(-dy,y0-ymin,&te,&tl))// inside test wrt bottom edge
	if(cliptest(-d.y, a.y-w.y, &uv.x, &uv.y))
	// same story numerator by demoninator to find t 
	//if(cliptest(dy,ymax-y0,&te,&tl))// inside test wrt top edge
	if(cliptest( d.y, w.w-a.y, &uv.x, &uv.y)){
		// in one way cohen sutherland and liang barasky are similar 
		if(uv.y<1.0f){
			//b.x=a.x+uv.y*d.x;
			//b.y=a.y+uv.y*d.y;
			b=a+d*uv.y;
		}if(uv.x>0.0f){
			//a.x=a.x+uv.x*d.x;
			//a.y=a.y+uv.x*d.y;
			a=a+d*uv.x;
		}
	}
	//window to viewport mappings
	//double sx= (xvmax-xvmin)/(xmax-xmin);// scale parameters
	//double sy= (yvmax-yvmin)/(ymax-ymin);
	vec2 s = (vec2(vp.z,vp.w)-vec2(vp))/(vec2(vp.z,vp.w)-vec2(vp));
	double vx0= xvmin+(x0-xmin)*sx;
	double vy0= yvmin+(y0-ymin)*sy;
	double vx1= xvmin+(x1-xmin)*sx;
	double vy1= yvmin+(y1-ymin)*sy;
	// draw a red colored viewport
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin,yvmin);
		glVertex2f(xvmax,yvmin);
		glVertex2f(xvmax,yvmax);
		glVertex2f(xvmin,yvmax);
		glEnd();
		glColor3f(0.0,0.0,1.0); //draw blue colored clip line
		glBegin(GL_LINES);
		glVertex2d(vx0,vy0);
		glVertex2f(vx1,vy1);
		glEnd();

}
	}
/*
float Math::sinFast(float a) {
	float a2 = a * a;
	return a * (((((-2.39e-08f * a2 + 2.7526e-06f) * a2 - 1.98409e-04f) * a2 + 8.3333315e-03f) * a2 - 1.666666664e-01f) * a2 + 1.0f);
}
float Math::cosFast(float a) {
	float a2 = a * a;
	return (((((-2.605e-07f * a2 + 2.47609e-05f) * a2 - 1.3888397e-03f) * a2 + 4.16666418e-02f) * a2 - 4.999999963e-01f) * a2 + 1.0f);
}
float Math::asinFast(float v) {
	return PI05 - (((((((-0.0012624911f * v + 0.0066700901f) * v - 0.0170881256f) * v + 0.0308918810f) * v - 0.0501743046f) * v + 0.0889789874f) * v - 0.2145988016f) * v + 1.5707963050f) * Math::sqrtf(1.0f - v);
}
float Math::acosFast(float v) {
	return (((((((-0.0012624911f * v + 0.0066700901f) * v - 0.0170881256f) * v + 0.0308918810f) * v - 0.0501743046f) * v + 0.0889789874f) * v - 0.2145988016f) * v + 1.5707963050f) * Math::sqrtf(1.0f - v);
}
void Math::sincosf(float angle,float &s,float &c) {
	#if defined(_WIN32) && !defined(_WIN64)
		__asm {
			fld angle
			fsincos
			mov edx, s
			mov ecx, c
			fstp dword ptr [ecx]
			fstp dword ptr [edx]
		}
	#elif _LINUX
		double res_0,res_1;
		asm volatile("fsincos" : "=t"(res_0), "=u"(res_1) : "0"(angle));
		s = (float)res_1;
		c = (float)res_0;
	#else
		s = Math::sinf(angle);
		c = Math::cosf(angle);
	#endif
} 
void Math::sincosd(double angle,double &s,double &c) {
	#if defined(_WIN32) && !defined(_WIN64)
		__asm {
			fld angle
			fsincos
			mov edx, s
			mov ecx, c
			fstp qword ptr [ecx]
			fstp qword ptr [edx]
		}
	#elif _LINUX
		asm volatile("fsincos" : "=t"(s), "=u"(c) : "0"(angle));
	#else
		s = Math::sind(angle);
		c = Math::cosd(angle);
	#endif
}

void Math::sincosFast(float angle,float &s,float &c) {
	if(angle < 0.0f || angle >= PI2) {
		angle -= Math::floorf(angle * (1.0f / PI2)) * PI2;
	}
	s = PI - angle;
	if(Math::absf(s) > PI05) {
		s = Math::selectf(s,-PI,PI) - s;
		c = 1.0f;
	} else {
		c = -1.0f;
	}
	float a2 = s * s;
	s *= ((7.610e-03f * a2 - 1.6605e-01f) * a2 + 1.0f);
	c *= ((3.705e-02f * a2 - 4.9670e-01f) * a2 + 1.0f);
}
 
 */
//============================================================================= OLDS
/*void SinCos(float radians,float &sine,float &cosine){
 _asm{
  fld DWORD PTR [radians]
  fsincos
  mov edx,DWORD PTR [cosine]
  mov eax,DWORD PTR [sine]
  fstp DWORD PTR [edx]
  fstp DWORD PTR [eax]
 };
};
float Q_fabs (float f) {//q2  http://fabiensanglard.net/quake2/index.php
 int tmp = * ( int * ) &f;
 tmp &= 0x7FFFFFFF;
 return * ( float * ) &tmp;
};
//Это известная формула Бине. Второй член в ней стремится к нулю, и его можно выкинуть.
//Точности double хватает до 70-го числа 190392490709135 ( 48 битов ).
//int fib(unsigned N) {			http://users.livejournal.com/_winnie/412164.html
//   return int(0.5+(pow(1.618033988749895, N) / 2.23606797749979));
//}
//------------------------------------------ CRT  
 extern "C"{
  //double __cdecl fmod(double,double);
}
//#pragma intrinsic (fmod)		 // fake intrinsic
 //__forceinline double sFMod(double a,double b)   { return fmod(a,b); }
 #pragma function(fmod)   */
/*double __cdecl sfmod(double a,double b){
  __asm  {
	fld   qword ptr [b];
	fld   qword ptr [a];
	fprem;
	fstp  st(1);
	fstp  qword ptr [a];
  }
  return a;
} 
double sfpow(double a,double b){
	__asm	{
		fld		qword ptr [a];
		fld		qword ptr [b];

		fxch	st(1);
		ftst;
		fstsw	ax;
		sahf;
		jz		zero;

		fyl2x;
		fld1;
		fld		st(1);
		fprem;
		f2xm1;
		faddp	st(1), st;
		fscale;

zero:
		fstp	st(1);
		fstp	qword ptr [a];
	}
	return a;
};

double sfexp(double f){
	__asm	{
		fld		qword ptr [f];
		fldl2e;
		fmulp	st(1), st;

		fld1;
		fld		st(1);
		fprem;
		f2xm1;
		faddp	st(1), st;
		fscale;

	fstp  st(1);
		fstp	qword ptr [f];
	}
	return f;
} 
__forceinline int sFtol(const float f){
  __asm{
	fld f
	push eax
	fistp dword ptr [esp]
	pop eax
  }
}

__forceinline float sFRound(const float f){
  __asm{
	fld f
	frndint
  }
}

__forceinline void sFSinCos(const float x,float &sine,float &cosine){
  __asm{
	fld x;
	fsincos;
	mov eax,[cosine];
	fstp dword ptr [eax];
	mov eax,[sine];
	fstp dword ptr [eax];
  }
} 
float sfsin(float a){
 __asm{
  fld dword ptr [a];
  fsin;
 };
 return a;
};
float sfcos(float a){
 __asm{
  fld dword ptr [a];
  fcos;
 };
 return a;
};
/*
float asin(float a){ // assumes correct range
 __asm{
  asinconsts  dd 0.892399, 1.693204, -3.853735, 2.838933 
	fld	 qword [a];
asingo:
	fld	 st0;
	fmul	st0; x x
	mov	 eax, asinconsts;
	fld	 dword [eax+12];
	fmul	st1;
	fadd	dword [eax+8];
	fmul	st1;
	fadd	dword [eax+4];
	fmulp   st1, st0;
	fadd	dword [eax];
	fmulp   st1, st0;
	ret;
 };
};
; ---- sF32 acos(sF32 a) // assumes correct range
global	  _acos
_acos:
	fld	 qword [esp+4]
	call	asingo
	fld	 dword [halfpi]
	fsubrp  st1, st0
	ret
%endif
%if 0
; ---- sF32 atan2(sF32 y, sF32 x)
global	  _atan2@8
_atan2@8:
	fld		dword [esp+4]
	fld		dword [esp+8]
	fpatan
	ret		8
; ---- sF32 sqrt(sF32 a)
global	  _sqrt@4
_sqrt@4:
	fld		dword [esp+4]
	fsqrt
	ret		4
%endif
; ---- sF32 pow(sF32 a, sF32 b)
global	_pow
_pow:
  fld	 qword [esp+4]
  fld	 qword [esp+12]
  call	__CIpow
global	__CIpow
__CIpow:
  fxch	st1
	ftst
	fstsw	ax
	sahf
	jz		  .zero

	fyl2x
	fld1
	fld		  st1
	fprem
	f2xm1
	faddp	  st1, st0
	fscale

.zero:
	fstp	  st1
	ret
; ---- sF32 exp(sF32 a)
%if 0
global	  _exp
_exp:
	fld	 qword [esp+4]
%endif
global	  __CIexp
__CIexp:
	fldl2e
	fmulp   st1, st0
	fld1
	fld	 st1
	fprem
	f2xm1
	faddp   st1, st0
	fscale
	fstp	st1
	ret
; ---- sF32 ceil(sF32 a)
global	  _ceil
_ceil:
	fld	 qword [esp+4]
	frndint
	fcom	qword [esp+4]
	fstsw   ax
	sahf
	je	  .equal
	fld1
	faddp   st1, st0
.equal:
	ret
; ---- sF32 floor(sF32 a)
global	  _floor
_floor:
	fld	 qword [esp+4]
	frndint
	fcom	qword [esp+4]
	fstsw   ax
	sahf
	je	  .equal
	fld1
	fsubp   st1, st0
.equal:
	ret
; ---- void * __cdecl memcpy(void *d, const void *s, sInt c)
global	  _memcpy
_memcpy:
	push	esi
	push	edi

	lea		ecx, [esp+12]
	mov		edi, [ecx]
	mov		esi, [ecx+4]
	mov		ecx, [ecx+8]
	mov		eax, ecx
	and		eax, byte 7
	push	eax

	shr		ecx, 3
	lea		esi, [esi+ecx*8]
	lea		edi, [edi+ecx*8]
	neg		ecx

.cplp:
	mov		eax, [esi+ecx*8]
	mov		edx, [esi+ecx*8+4]
	mov		[edi+ecx*8], eax
	mov		[edi+ecx*8+4], edx
	inc		ecx
	jnz		.cplp

	pop		ecx
	cld
	rep		movsb

	pop		edi
	pop		esi
  mov	 eax, edi
  ret
; ---- void * __cdecl memset(void *d, char c, int count)
global _memset
_memset:
	push	edi
	mov		edi, [esp+8]
	mov		eax, [esp+12]
	mov		ecx, [esp+16]
	mov		ah, al
	mov		edx, eax
	shl		eax, 16
	mov		ax, dx
	push	ecx
	shr		ecx, 2
	jz		.tail
	rep		stosd
.tail:
	pop		ecx
	and		ecx, byte 3
	jz		.done
	rep		stosb
.done:
	pop		edi
	ret
 ; ---- size_t __cdecl strlen(const char *s)
global	  _strlen
_strlen:
	mov		edx, [esp+4]
	xor		eax, eax

.lp:
	cmp		byte [edx+eax], 0
	jz		.end

	inc		eax
	jmp		short .lp

.end:
	ret

/*; ---- sF32 sin(sF32 a)
global	  _sin@4
_sin@4:
	fld		dword [esp+4]
	fsin
	ret		4
; ---- sF32 cos(sF32 a)
global	  _cos@4
_cos@4:
	fld		dword [esp+4]
	fcos
	ret		4
%endif
; ---- sF32 asin(sF32 a) // assumes correct range
%if 0
global	  _asin
_asin:
	fld	 qword [esp+4]
asingo:
	fld	 st0
	fmul	st0			 ; x x
	mov	 eax, asinconsts
	fld	 dword [eax+12]
	fmul	st1
	fadd	dword [eax+8]
	fmul	st1
	fadd	dword [eax+4]
	fmulp   st1, st0
	fadd	dword [eax]
	fmulp   st1, st0
	ret
; ---- sF32 acos(sF32 a) // assumes correct range
global	  _acos
_acos:
	fld	 qword [esp+4]
	call	asingo
	fld	 dword [halfpi]
	fsubrp  st1, st0
	ret
%endif
%if 0
; ---- sF32 atan2(sF32 y, sF32 x)
global	  _atan2@8
_atan2@8:
	fld		dword [esp+4]
	fld		dword [esp+8]
	fpatan
	ret		8
; ---- sF32 sqrt(sF32 a)
global	  _sqrt@4
_sqrt@4:
	fld		dword [esp+4]
	fsqrt
	ret		4
%endif
; ---- sF32 pow(sF32 a, sF32 b)
global	_pow
_pow:
  fld	 qword [esp+4]
  fld	 qword [esp+12]
  call	__CIpow
global	__CIpow
__CIpow:
  fxch	st1
	ftst
	fstsw	ax
	sahf
	jz		  .zero

	fyl2x
	fld1
	fld		  st1
	fprem
	f2xm1
	faddp	  st1, st0
	fscale

.zero:
	fstp	  st1
	ret
; ---- sF32 exp(sF32 a)
%if 0
global	  _exp
_exp:
	fld	 qword [esp+4]
%endif
global	  __CIexp
__CIexp:
	fldl2e
	fmulp   st1, st0
	fld1
	fld	 st1
	fprem
	f2xm1
	faddp   st1, st0
	fscale
	fstp	st1
	ret
; ---- sF32 ceil(sF32 a)
global	  _ceil
_ceil:
	fld	 qword [esp+4]
	frndint
	fcom	qword [esp+4]
	fstsw   ax
	sahf
	je	  .equal
	fld1
	faddp   st1, st0
.equal:
	ret
; ---- sF32 floor(sF32 a)
global	  _floor
_floor:
	fld	 qword [esp+4]
	frndint
	fcom	qword [esp+4]
	fstsw   ax
	sahf
	je	  .equal
	fld1
	fsubp   st1, st0
.equal:
	ret
; ---- void * __cdecl memcpy(void *d, const void *s, sInt c)
global	  _memcpy
_memcpy:
	push	esi
	push	edi

	lea		ecx, [esp+12]
	mov		edi, [ecx]
	mov		esi, [ecx+4]
	mov		ecx, [ecx+8]
	mov		eax, ecx
	and		eax, byte 7
	push	eax

	shr		ecx, 3
	lea		esi, [esi+ecx*8]
	lea		edi, [edi+ecx*8]
	neg		ecx

.cplp:
	mov		eax, [esi+ecx*8]
	mov		edx, [esi+ecx*8+4]
	mov		[edi+ecx*8], eax
	mov		[edi+ecx*8+4], edx
	inc		ecx
	jnz		.cplp

	pop		ecx
	cld
	rep		movsb

	pop		edi
	pop		esi
  mov	 eax, edi
  ret
; ---- void * __cdecl memset(void *d, char c, int count)
global _memset
_memset:
	push	edi
	mov		edi, [esp+8]
	mov		eax, [esp+12]
	mov		ecx, [esp+16]
	mov		ah, al
	mov		edx, eax
	shl		eax, 16
	mov		ax, dx
	push	ecx
	shr		ecx, 2
	jz		.tail
	rep		stosd
.tail:
	pop		ecx
	and		ecx, byte 3
	jz		.done
	rep		stosb
.done:
	pop		edi
	ret
 ; ---- size_t __cdecl strlen(const char *s)
global	  _strlen
_strlen:
	mov		edx, [esp+4]
	xor		eax, eax

.lp:
	cmp		byte [edx+eax], 0
	jz		.end

	inc		eax
	jmp		short .lp

.end:
	ret
*/

/*
%ifndef DEBUG

global	__fltused
__fltused:

%define PAGESIZE 0x1000

global	__chkstk ; wenn das jetzt geht, dann kotze ich.
__chkstk:
  cmp		eax, PAGESIZE
  jae		short .probesetup

  neg		eax
  add		eax, esp
  add		eax, byte 4
  test		dword [eax], eax
  xchg		eax, esp
  mov		eax, dword [eax]
  push		eax
  ret

.probesetup:
  push		ecx
  lea		ecx, [esp+8]

.probepages:
  sub		ecx, PAGESIZE
  sub		eax, PAGESIZE
 
  test		dword [ecx], eax

  cmp		eax, PAGESIZE
  jae		short .probepages

  sub		ecx, eax
  mov		eax, esp

  test		dword [ecx], eax

  mov		esp, ecx
  
  mov		ecx, dword [eax]
  mov		eax, dword [eax+4]
  
  push		eax
  ret

%endif 
 */
/*
// integer

typedef unsigned int size_t;

extern "C"
{
  int __cdecl abs(int);
  void * __cdecl memset( void *dest, int c, size_t count );
  void * __cdecl memcpy( void *dest, const void *src, size_t count );
  int __cdecl memcmp( const void *buf1, const void *buf2, size_t count );
  size_t __cdecl strlen( const char *string );
}

#pragma intrinsic (abs)									   // int intrinsic
#pragma intrinsic (memset,memcpy,memcmp,strlen)			   // memory intrinsic

__forceinline sInt sAbs(sInt i)								 { return abs(i); }
__forceinline void sSetMem(sPtr dd,sInt s,sInt c)			   { memset(dd,s,c); }
__forceinline void sCopyMem(sPtr dd,const void *ss,sInt c)	  { memcpy(dd,ss,c); }
__forceinline sInt sCmpMem(const void *dd,const void *ss,sInt c) { return (sInt)memcmp(dd,ss,c); }
#if !sUNICODE
__forceinline sInt sGetStringLen(const sChar *s)				{ return (sInt)strlen(s); }
#else
__forceinline sInt sGetStringLen(const sChar *s)				{ for(sInt i=0;s[i];i++); return i; }
#endif


// float

#if !sMOBILE

extern "C"
{

  double __cdecl atan(double);
  double __cdecl atan2(double,double);
  double __cdecl cos(double);
  double __cdecl exp(double);
  double __cdecl fabs(double);
  double __cdecl log(double);
  double __cdecl log10(double);
  double __cdecl sin(double);
  double __cdecl sqrt(double);
  double __cdecl tan(double); 

  double __cdecl acos(double);
  double __cdecl asin(double);
  double __cdecl cosh(double);
  double __cdecl fmod(double,double);
  double __cdecl pow(double,double);
  double __cdecl sinh(double);
  double __cdecl tanh(double);
}

#pragma intrinsic (atan,atan2,cos,exp,log,log10,sin,sqrt,tan,fabs) // true intrinsic
#pragma intrinsic (acos,asin,cosh,fmod,pow,sinh,tanh)		 // fake intrinsic

__forceinline sF64 sFATan(sF64 f)		 { return atan(f); }
__forceinline sF64 sFATan2(sF64 a,sF64 b) { return atan2(a,b); }
__forceinline sF64 sFCos(sF64 f)		  { return cos(f); }
__forceinline sF64 sFAbs(sF64 f)		  { return fabs(f); }
__forceinline sF64 sFLog(sF64 f)		  { return log(f); }
__forceinline sF64 sFLog10(sF64 f)		{ return log10(f); }
__forceinline sF64 sFSin(sF64 f)		  { return sin(f); }
__forceinline sF64 sFSqrt(sF64 f)		 { return sqrt(f); }

__forceinline sF64 sFASin(sF64 f)		 { return asin(f); }
__forceinline sF64 sFCosH(sF64 f)		 { return cosh(f); }
__forceinline sF64 sFSinH(sF64 f)		 { return sinh(f); }
__forceinline sF64 sFTanH(sF64 f)		 { return tanh(f); }

__forceinline sF64 sFInvSqrt(sF64 f)	  { return 1.0/sqrt(f); }

#if !sINTRO 
__forceinline sF64 sFACos(sF64 f)		 { return acos(f); }
__forceinline sF64 sFMod(sF64 a,sF64 b)   { return fmod(a,b); }
__forceinline sF64 sFExp(sF64 f)		  { return exp(f); }
__forceinline sF64 sFPow(sF64 a,sF64 b)   { return pow(a,b); }
#endif

#if sINTRO
sF64 sFACos(sF64 f);
sF64 sFPow(sF64 a,sF64 b);
sF64 sFMod(sF64 a,sF64 b);
sF64 sFExp(sF64 f);
#endif 
*/
//=============================================================================
#endif
