/*	Renegade Scripts.dll
	Container classes
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
//forward declarations

class GenericMultiListClass;
class MultiListObjectClass;

template <class T> class VectorClass {
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
public:
	virtual ~VectorClass()
	{
	}
	int Length()
	{
		return VectorMax;
	}
	T &operator[](int index)
	{
		return Vector[index];
	}
	virtual bool operator==(VectorClass<T> &vector)
	{
		return false;
	}
	virtual bool Resize(int newsize,T *array)
	{
		return false;
	}
	virtual void Clear()
	{
	}
	virtual int ID(T &object)
	{
		return 0;
	}
	virtual int ID(T *ptr)
	{
		return 0;
	}
};

template <class T> class DynamicVectorClass : public VectorClass<T> {
private:
	int ActiveCount;
	int GrowthStep;
public:
	void Reset_Active()
	{
		ActiveCount = 0;
	}
	int Count()
	{
		return ActiveCount;
	}
	virtual ~DynamicVectorClass()
	{
	}
	virtual bool Resize(int newsize,T *array)
	{
		return false;
	}
	virtual void Clear()
	{
	}
	virtual int ID(T &object)
	{
		return 0;
	}
	virtual int ID(T *ptr)
	{
		return 0;
	}
	bool Add(T& object)
	{
		if (ActiveCount >= VectorMax)
		{
			if ((IsAllocated || !VectorMax) && (GrowthStep > 0))
			{
				if (!Resize(GrowthStep + VectorMax,0))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		Vector[ActiveCount++] = object;
		return true;
	}
	bool Delete(int pos)
	{
		if (pos >= ActiveCount)
		{
			return false;
		}
		ActiveCount--;
		if (pos >= ActiveCount)
		{
			return true;
		}
		memmove(&Vector[pos],&Vector[pos+1],(ActiveCount - pos) * sizeof(T));
		return true;
	}
	bool Delete(T& object)
	{
		int pos = ID(object);
		if (pos != -1)
		{
			return Delete(pos);
		}
		return false;
	}
};
#ifdef DEBUG
#include <intrin.h>
#pragma intrinsic (_ReturnAddress)
#endif
template <class T> class SimpleVecClass {
protected:
	T *Vector;
	int VectorMax;
public:
	SimpleVecClass()
	{
		Vector = 0;
		VectorMax = 0;
	}
	SimpleVecClass(unsigned int size)
	{
		Vector = 0;
		VectorMax = 0;
		if (size > 0)
		{
			Resize(size);
		}
	}
	virtual bool Uninitialised_Grow(int newsize)
	{
		if ((newsize > 0) && (newsize > VectorMax))
		{
			if (Vector)
			{
				delete[] Vector;
			}
			Vector = new T[newsize];
#ifdef DEBUG
			log("[I] SimpleVecClass allocate from 0x%08X",_ReturnAddress());
#endif
			VectorMax = newsize;
		}
		return true;
	}
	SimpleVecClass(const SimpleVecClass<T> &cl)
	{
		VectorMax = cl.VectorMax;
		Vector = new T[VectorMax];
#ifdef DEBUG
		log("[I] SimpleVecClass allocate from 0x%08X",_ReturnAddress());
#endif
		memcpy(Vector,cl.Vector,VectorMax*sizeof(T));
	}
	int Length()
	{
		return VectorMax;
	}
	T &operator[](int index)
	{
		return Vector[index];
	}
	virtual ~SimpleVecClass()
	{
		if (Vector)
		{
			delete[] Vector;
			Vector = 0;
			VectorMax = 0;
		}
	}
	virtual bool Resize(int newsize)
	{
		T *vec;
		if (VectorMax == newsize)
		{
			return true;
		}
		if (newsize > 0)
		{
			vec = new T[newsize];
#ifdef DEBUG
			log("[I] SimpleVecClass allocate from 0x%08X",_ReturnAddress());
#endif
			if (Vector)
			{
				int count = VectorMax;
				if (newsize < count)
				{
					count = newsize;
				}
				memcpy(vec,Vector,count*sizeof(T));
				delete[] Vector;
				Vector = 0;
			}
			Vector = vec;
			VectorMax = newsize;
		}
		else
		{
			VectorMax = 0;
			if (Vector)
			{
				delete[] Vector;
				Vector = 0;
			}
		}
		return true;
	}
	SimpleVecClass &operator=(const SimpleVecClass<T> &cl)
	{
		if (Vector)
		{
			delete[] Vector;
		}
		VectorMax = cl.VectorMax;
		Vector = new T[VectorMax];
#ifdef DEBUG
		log("[I] SimpleVecClass allocate from 0x%08X",_ReturnAddress());
#endif
		memcpy(Vector,cl.Vector,VectorMax*sizeof(T));
		return *this;
	}
};

template <class T> class SimpleDynVecClass : public SimpleVecClass<T> {
protected:
	int ActiveCount;
public:
	SimpleDynVecClass() : SimpleVecClass<T>(0)
	{
		ActiveCount = 0;
	}
	SimpleDynVecClass(int size) : SimpleVecClass<T>(size)
	{
		ActiveCount = size;
	}
	SimpleDynVecClass(const SimpleDynVecClass<T> &cl) : SimpleVecClass<T>(cl)
	{
		ActiveCount = cl.ActiveCount;
	}
	int Count()
	{
		return ActiveCount;
	}
	virtual ~SimpleDynVecClass()
	{
		if (Vector)
		{
			delete[] Vector;
			Vector = 0;
		}
	}
	virtual bool Resize(int newsize)
	{
		if (SimpleVecClass<T>::Resize(newsize))
		{
			if (VectorMax < ActiveCount)
			{
				ActiveCount = VectorMax;
			}
			return true;
		}
		return false;
	}
	int Add(T& data)
	{
		for (int i = 0;i < VectorMax;i++)
		{
			if (!Vector[i])
			{
				Vector[i] = data;
				return i;
			}
		}
		Resize(VectorMax+1);
		Vector[VectorMax-1] = data;
		ActiveCount++;
		return VectorMax-1;
	}
	void Clear(int position)
	{
		Vector[position] = 0;
	}
	void ClearAll()
	{
		memset(Vector,0,VectorMax*sizeof(T));
	}
	void Delete(int position)
	{
		if (position < (ActiveCount - 1))
		{
			int size = ((ActiveCount - position) * sizeof(T)) - sizeof(T);
			memmove(&Vector[position],&Vector[position+1],size);
		}
		ActiveCount--;
		Vector[ActiveCount] = 0;
	}
	void Delete_All()
	{
		ActiveCount = 0;
		VectorMax = 0;
		if (Vector)
		{
			delete[] Vector;
			Vector = 0;
		}
	}
	SimpleDynVecClass &operator=(const SimpleDynVecClass<T> &cl)
	{
		SimpleVecClass<T>::operator =(cl);
		ActiveCount = cl.ActiveCount;
		return *this;
	}
};

class GenericNode {
	GenericNode* NextNode;
	GenericNode* PrevNode;
public:
	virtual ~GenericNode();
};

class GenericList {
	GenericNode FirstNode;
	GenericNode LastNode;
public:
	virtual ~GenericList();
};

template <class T> class List : GenericList {
public:
	virtual ~List();
};

template <typename T1,class T2> class IndexClass {
	struct NodeElement {
		int ID;
		T2 Data;
	};
	NodeElement* IndexTable;
	int IndexCount;
	int IndexSize;
	unsigned char IsSorted;
	NodeElement* Archive;
};

class MultiListNodeClass {
	MultiListNodeClass* Prev;
	MultiListNodeClass* Next;
	MultiListNodeClass* NextList;
	MultiListObjectClass* Object;
	GenericMultiListClass* List;
};

class GenericMultiListClass {
	MultiListNodeClass Head;
public:
	MultiListObjectClass *Internal_Remove_List_Head();
	virtual ~GenericMultiListClass();
};

class MultiListObjectClass {
	MultiListNodeClass* ListNode;
public:
	virtual ~MultiListObjectClass();
};

template <class t> class MultiListClass : public GenericMultiListClass {
public:
	~MultiListClass();
};

template <class t> class RefMultiListClass : public GenericMultiListClass {
public:
	~RefMultiListClass();
};

#ifdef WIN32
struct GenericSLNode {
	GenericSLNode *NodeNext;
	void *NodeData;
};
#elif defined RH8
struct GenericSLNode {
	GenericSLNode *NodeNext;
	void *NodeData;
};
#else
struct GenericSLNode {
	void *unknown;
	GenericSLNode *NodeNext;
	void *NodeData;
};
#endif

template <class T> class SList {
public:
	GenericSLNode *HeadNode;
	GenericSLNode *TailNode;
	virtual ~SList();
	virtual bool Add_Head(T *data);
	virtual bool Add_Head(SList<T> &list);
	virtual bool Add_Tail(T *data);
	virtual bool Add_Tail(SList<T> &list);
	virtual T *Remove_Head();
	virtual T *Remove_Tail();
	virtual bool Remove(T *element);;
	virtual void Remove_All();
	virtual bool Insert_Before(T *newnode,T *oldnode);
	virtual bool Insert_After(T *newnode,T *oldnode);
	virtual bool Is_Empty();
	virtual long Get_Count();
};

#ifndef WIN32
template <class T> class DataNode: public GenericNode {
public:
	T *Ref;
};
#endif

class RefCountClass {
public:
	long NumRefs;
#ifndef WIN32
	DataNode<RefCountClass*> Node;
	const char* RefFile;
	unsigned int RefLine;
#endif
	virtual void Delete_This()
	{
		delete this;
#ifdef DEBUG
		log("[I] RefCountClass delete from 0x%08X",_ReturnAddress());
#endif
	}
	virtual ~RefCountClass()
	{
	}
	void Release_Ref()
	{
#ifdef WIN32
		if (!InterlockedDecrement(&NumRefs))
#else
		if (!--NumRefs)
#endif
		{
			Delete_This();
		}
	}
	void Add_Ref()
	{
#ifdef WIN32
		InterlockedIncrement(&NumRefs);
#else
		NumRefs++;
#endif
	}
};

template <class t> class ShareBufferClass : public RefCountClass {
	t* Array;
	int Count;
public:
	t *Get_Array()
	{
		return Array;
	}
	int Get_Count()
	{
		return Count;
	}
	t &Get_Element(int element)
	{
		return Array[element];
	}
	~ShareBufferClass();
};

template <class T> class EnlargeableBufferClass
{
	T* Buffer;
	unsigned int BufferSize;
public:
	EnlargeableBufferClass()
	{
		Buffer = 0;
		BufferSize = 0;
	}
	EnlargeableBufferClass(unsigned int size)
	{
		Buffer = new T[size];
		BufferSize = size;
	}
	~EnlargeableBufferClass()
	{
		delete[] Buffer;
	}
	T* GetBuffer()
	{
		return Buffer;
	}	
	unsigned int GetCurrentBufferSize()
	{
		return BufferSize;
	}
	T* Enlarge(unsigned int newsize)
	{
		if (newsize > BufferSize)
		{
			delete[] Buffer;
			Buffer = new T[newsize];
			BufferSize = newsize;
		}
		return Buffer;
	}
	T &operator[](int index)
	{
		return Buffer[index];
	}
};
