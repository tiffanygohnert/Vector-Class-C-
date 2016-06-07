#ifndef  VECTOR_H
#define VECTOR_H
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

// forward declaration for ContainerIterator
template <class T>
class VectorIterator;

//vector class
template <class T>
class Vector
{
 
  public: 

   //default constructor 
  Vector():  Size(0),Capacity(0), vector(0x00000000){} 
  
   //destructor
   ~Vector(){};
 // { if (Size) delete [] vector; }
   
   //non-default constructor Needed for test 1
   Vector(int capacity) throw (const char *);
 
  //copy constructor
Vector(const Vector& rhs)throw (const char *); 


//operator=
	 // assignment operator
    Vector & operator = (const Vector & rhs)throw (const char *)
    {
     try
       {  Vector temp = rhs;
   Capacity = temp.Capacity;
   vector = temp.vector;
   Size = temp.Size;
   return *this;        
       }
       catch (std::bad_alloc)
       {
          throw "ERROR: Unable to allocate a new buffer for Vector";
       }
	   
    }

//empty()
   bool empty()const {return Size ==0;  }
//clear()
   void clear(){Size =0; }

   //size()
    int size()const{return Size; }
   //capacity()
  int capacity()const {   return Capacity;}

//push_back
 void push_back(const T & t) throw (const char *);
 
  // return an iterator to the beginning of the list
    VectorIterator <T> begin() { return VectorIterator<T>(vector); }

    // return an iterator to the end of the list
    VectorIterator <T> end() { return VectorIterator<T>(vector + Size);};

	

    // operators[]
       T & operator [](int& index) const throw(const char *)
    {
     if (Capacity < 0 || Capacity < Size)
         throw "ERROR: Invalid index\n";
       return vector[index];
    }

	    T & operator [](int& index) throw(const char *)
    {
       if (Capacity < 0 || Capacity < Size)
          throw "ERROR: Invalid index\n";
       return vector[index];
    }

   

       
private:

 int Size;
T * vector; 
int Capacity; 

 
}; 

//iterator class
template <class T> 
class VectorIterator
{
public:
    // default constructor
   VectorIterator() : p(0x00000000) {}

    // initialize to direct p to some item
   VectorIterator(T * p) : p(p) {}

    // copy constructor
    VectorIterator(const VectorIterator & rhs) { *this = rhs; }

    // assignment operator
    VectorIterator & operator = (const VectorIterator & rhs)
    {
       this->p = rhs.p;
       return *this;
    }

    // not equals operator
    bool operator != (const VectorIterator & rhs) const
    {
       return rhs.p != this->p;
    }

    // dereference operator
    T & operator * ()
    {
       return *p;
    }

    // prefix increment
    VectorIterator <T> & operator ++ ()
    {
       p++;
       return *this;
    }

    // postfix increment
    VectorIterator <T> operator++(int postfix)
    {
       VectorIterator tmp(*this);
       p++;
       return tmp;
    }
    
   private:
    T * p;
   

};

/**********************************************
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(Capacity >= 0);

   // do nothing if there is nothing to do
   if (Capacity == 0)
  {
    this->Capacity = this->Size = 0;
    this->vector = 0x00000000;
  return; 
  }

   // attempt to allocate
         try
         {
             vector = new T[capacity];
			 
         }
        catch (std::bad_alloc)
         {
		  //problem for test 1
           throw "ERROR: Unable to allocate buffer";
		   
			 
         }


          // copy over the stuff
          this->Capacity = capacity;
          this->Size = 0;
		   
}

/*******************************************
 * Vector:: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
  assert(rhs.Capacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.Capacity == 0)
   {
      Capacity = Size = 0;
      vector = 0x00000000;
      return;
   }

   // attempt to allocate
       try
       {
          vector = new T[rhs.Capacity];
       }
       catch (std::bad_alloc)
       {
          throw "ERROR: Unable to allocate buffer";
       }

       // copy over the stuff
       assert(rhs.Size >= 0 && rhs.Size <= rhs.Capacity);
       Capacity = rhs.Capacity;
       Size = rhs.Size;
       for (int i = 0; i < Size; i++)
          vector[i] = rhs.vector[i];
}



/***************************************************
 * Vector :: push back
 * Insert an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
  try
{
if (Capacity==0 || Capacity ==Size)
{
if (Capacity==0)
Capacity=1;
else
Capacity *=2;
T *temp = new T[Capacity];

int index=0;
VectorIterator<T> it;
for (VectorIterator <T> it = this->begin(); it != this->end(); ++it)
{
temp[index++]= *it;
}
vector=temp;
}
}
catch (std::bad_alloc)
{
throw "ERROR: Unable to allocate buffer\
";
}
vector[Size++]=t;
   
}

#endif
