#ifndef __XML_H__
#define __XML_H__

#include "Str.h"
#include "vector.h"

struct BUFFER;//FD

struct DLL_API XML {
	
	XML *parent;
	Vector<XML*> childs;

	str name;
	struct xml_args { str name, val; };
	Vector<xml_args> args;
	mutable str data;

	//-------------------------------------------------------------------------

	XML();
	XML(const char *fname);
	XML(BUFFER *B);
	XML(const char *new_name, const char *new_args);
	~XML() { clear(); }

	void copy(const XML &xml);
	void clear();
	
	//-------------------------------------------------------------------------

	bool load(BUFFER *B);
	bool load(const char *fname);
	
	int get_num_named_childs() const;
	bool get_text_sub_tree(str &dest, int offset = 0) const;
	bool save(BUFFER *B);
	bool save(const char *fname);

	//-------------------------------------------------------------------------

	static void get_text_lines(const XML *xml, str &lines);

	//------------------------------------------------------------------------- parsing

	static str encode(const char *src);
	static str decode(const char *src);
	static int skip_spaces(const char *src);
	static int skip_comments(const char *src);
	int read_string(const char *src, str &dest) const;
	int read_element(const char *src, str &dest) const;
	int read_args(const char *src, Vector<xml_args> &args) const;
	int parse(const char *src);

	//------------------------------------------------------------------------- hierarchy

	const XML *do_find(const char *path) const;
	XML *find(const char *path);
	const XML *find(const char *path) const;
	XML *addChild(XML *xml);
	XML *addChild(const char *name, const char *args);
	XML *removeChild(XML *xml);
	XML *removeChild(const char *path);

	//-------------------------------------------------------------------------

	bool isChild(const char *name) const;
	int getNumChilds() const;
	const XML *getChild(int num) const;
	XML *getChild(int num);
	const XML *getChild(const char *name) const;
	XML *getChild(const char *name);
	void setName(const char *n);
	const str &getName() const;

	//------------------------------------------------------------------------- set ARG

	void setArg(const char *name, const char *value);
	void setBoolArg(const char *name, int value);
	void setIntArg(const char *name, int value);
	void setIntArrayArg(const char *name, const int *src, int size);
	void setIntArrayArg(const char *name, const Vector<int> &src);
	void setFloatArg(const char *name, float value);
	void setFloatArrayArg(const char *name, const float *src, int size);
	void setFloatArrayArg(const char *name, const Vector<float> &src);
	void setStringArrayArg(const char *name, const Vector<str> &src);

	//------------------------------------------------------------------------- get ARG

	bool isArg(const char *name) const;
	int getNumArgs() const;
	const str &getArgName(int num) const;
	const str &getArgValue(int num) const;
	const str &getArg(const char *name) const;
	bool getBoolArg(const char *name) const;
	int getIntArg(const char *name) const;
	bool getIntArrayArg(const char *name, int *dest, int size) const;
	bool getIntArrayArg(const char *name, Vector<int> &dest) const;
	float getFloatArg(const char *name) const;
	bool getFloatArrayArg(const char *name, float *dest, int size) const;
	bool getFloatArrayArg(const char *name, Vector<float> &dest) const;
	bool getStringArrayArg(const char *name, Vector<str> &dest) const;

	//------------------------------------------------------------------------- set DATA

	bool setData(const char *d);
	bool setRawData(const char *d);
	bool setBoolData(int value);
	bool setIntData(int value);
	bool setIntArrayData(const int *src, int size);
	bool setIntArrayData(const Vector<int> &src);
	bool setFloatData(float value);
	bool setFloatArrayData(const float *src, int size);
	bool setFloatArrayData(const Vector<float> &src);
	bool setStringArrayData(const Vector<str> &src);

	//------------------------------------------------------------------------- get DATA

	const str &getData() const;
	bool getBoolData() const;
	int getIntData() const;
	bool getIntArrayData(int *dest, int size) const;
	bool getIntArrayData(Vector<int> &dest) const;
	float getFloatData() const;
	bool getFloatArrayData(float *dest, int size) const;
	bool getFloatArrayData(Vector<float> &dest) const;
	bool getStringArrayData(Vector<str> &dest) const;

};

#endif