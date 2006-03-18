/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003-2006 Alan Alvarez.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
*/

#ifndef ELECTRONIC_NETWORKS__CACHE_H
#define ELECTRONIC_NETWORKS__CACHE_H

#include <vector>
#include <cstdlib>

namespace eNetworks
{

template<class value_type>
struct node_base
{
   typedef node_base<value_type> self;
   self* M_next;
   self* M_previous;
   time_t M_idle;
   value_type M_object;

   void hit() { M_idle = time(0); }
};


template<class value_type>
class CacheIterator
{

   typedef node_base<value_type> node;
   public:
        typedef value_type* pointer;
        typedef value_type& reference;

        CacheIterator(node* current) : M_current(current)
        {}

        CacheIterator(const CacheIterator& rhs)
        {
            M_current = rhs.M_current;
        }

        CacheIterator operator++()
        {
           M_current = M_current->M_next;
           return *this;
        }

        CacheIterator operator++(int)
        {
           CacheIterator l_CacheIterator(*this);
           M_current = M_current->M_next;
           return l_CacheIterator;
        }

        CacheIterator operator--()
        {
           M_current = M_current->M_previous;
           return *this;
        }

        CacheIterator operator--(int)
        {
           CacheIterator l_CacheIterator(*this);
           M_current = M_current->M_previous;
           return l_CacheIterator;
        }

        CacheIterator operator+=(const unsigned int& sum)
        {
           for (unsigned int i = 0; (M_current != NULL) && i < sum; i++)
           {
                M_current = M_current->M_next;
           }

           return *this;
        }

        CacheIterator operator+(const unsigned int& sum) const
        {
           node* l_copy;
           for (unsigned int i = 0; (l_copy != NULL) && i < sum; i++)
           {
                l_copy = l_copy->M_next;
           }

           return CacheIterator(l_copy);
        }

        CacheIterator operator-=(const unsigned int& sum)
        {
           for (unsigned int i = 0; (M_current != NULL) && i < sum; i--)
           {
                M_current = M_current->M_previous;
           }

           return *this;
        }

        CacheIterator operator-(const unsigned int& sum) const
        {
           node* l_copy;
           for (unsigned int i = 0; (l_copy != NULL) && i < sum; i++)
           {
                l_copy = l_copy->M_previous;
           }

           return CacheIterator(l_copy);
        }

        pointer operator->() const
        {
           return &M_current->M_object;
        }

        reference operator*() const
        {
           return M_current->M_object;
        }

        bool operator==(const CacheIterator& rhs)
        {
           return M_current == rhs.M_current;
        }

        bool operator!=(const CacheIterator& rhs)
        {
           return M_current != rhs.M_current;
        }

   private:
        node* M_current;
};


/*
 *  class Cache defines a class that caches data and gives search
 *  priority to recently requested data as well as new entries.
 *
 *  Data structure used is a double linked-list sorted by last hit object.
 *
 *  Once initialized this cache is intended very fast to maintain.
 *
 *  This class does no memory reallocation.
 *
 *  Search speed depends upon continuous calls of clean_up().
 *  Also on what the MaxSize is and How long MaxIdleTime is set to be.
 *
 */
template<class Key, class Ty>
class Cache
{
   typedef node_base<std::pair<Key, Ty> > node;
   public:
   	typedef std::pair<Key, Ty> value_type;
   	typedef value_type* pointer;
   	typedef const pointer const_pointer;
   	typedef value_type& reference;
   	typedef reference const const_reference;
   	typedef CacheIterator<value_type> iterator;

   	/*
   	 * MaxSize: Maximum amount of objects that we will hold. This is how much memory will be allocated
   	 *   	    throughout the existance of the Cache object. Changing this value will require reallocating 
   	 *  	    memory as well as relocating data to new memory.
   	 *
   	 * MaxIdleTime: Dictates how long an object can stay in the cache before it's removed from it.
      	 *
   	 */
   	Cache(const size_t& MaxSize, const time_t& MaxIdleTime) : M_free(), M_start(NULL), M_end(NULL), M_MaxIdleTime(MaxIdleTime),
   	   	   	   	   	   	   	   	  M_start_allocated(NULL), M_end_allocated(NULL)
   	{
   	   // TODO: Is it still necessary to hold these values?
   	   M_start_allocated = new node[MaxSize];
   	   M_end_allocated = M_start_allocated + MaxSize;

   	   // Get copy of free memory.
   	   M_free.reserve(MaxSize); // Tell std::vector to allocate all the memory at once.
   	   for (size_t i = 0; i < MaxSize; i++)
   	   	M_free.push_back(M_start_allocated + i);
   	}

   	virtual ~Cache()
   	{
   	   delete[] M_start_allocated;
   	}

   	iterator begin() const
   	{
   	   return iterator(M_start);
   	}

   	iterator end() const
   	{
   	   return iterator(NULL);
   	}

   	// Insert an object to the list.
   	void insert(const value_type& object)
   	{
   	   node* l_node = new_object();
   	   l_node->M_object = value_type(object);
   	   put_front(l_node);
   	}

   	// returns an iterator to an object if the object is in the cache.
   	// returns end() otherwise.
   	iterator find(const Key& key)
   	{
   	   for (node* l_node = M_start; l_node != NULL; l_node = l_node->M_next)
   	   {
   	   	if (l_node->M_object.first == key)
   	   	{
   	   	   put_front(l_node);
   	   	   return iterator(l_node);
   	   	}
   	   }

   	   return end();
   	}

   	void erase(const iterator& Iter)
   	{
   	   if (Iter == end())
   	   	return;

   	   node* l_node = &Iter->second;

   	   // Was this in front?
   	   if (l_node == M_start)
   	   {
   	   	M_start = l_node->M_next;
   	   	M_start->previous = NULL;
   	   }
   	   else if (l_node == M_end)
   	   {
   	   	M_end = l_node->M_previous;
   	   	M_end->M_next = NULL;
   	   }
   	   else
   	   {
   	   	l_node->M_previous->M_next = l_node->M_next;
   	   	l_node->M_next->M_previous = l_node->M_previous;
   	   }

   	   free_object(l_node);
   	}

   	// Check for idling nodes.
   	void clean_up()
   	{
   	   while(M_end != M_start)
   	   {
   	   	// Get rid of nodes that have been idling for too long.
   	   	if ((time(0) - M_end->M_idle) > M_MaxIdleTime)
   	   	{
   	   	   pop_back();
   	   	   continue;
   	   	}

   	   	// no more idling nodes.
   	   	break;
   	   }
   	}   	

   	// Get amount of objects being cached.
   	size_t size() const { return max_size() - M_free.size(); }

   	// Get amount of memory allocated on heap.
   	size_t max_size() const { return M_end_allocated - M_start_allocated; }


   private:

   	// Get a space from the allocated heap for a new object.
   	node* new_object()
   	{
   	   if (size() >=  max_size())
   	   	pop_back();
   	  
   	   node* l_node = M_free.back();
   	   M_free.pop_back();
   	   return l_node;
   	}

   	// free object from the allocated heap.
   	void free_object(node* object)
   	{
   	   if (object != NULL)
   	   	M_free.push_back(object);
   	}

   	// put an object in the front of the list.
   	void put_front(node* object)
   	{
   	   // Is this object in the front already?
   	   if (M_start == object)
   	   	return;

   	   if (M_start != NULL)
   	   {
   	   	object->M_next = M_start;
   	   	M_start->M_previous = object;
   	   }
   	   else
   	   {
   	   	// assume M_end is NULL too.
   	   	M_end = object;
   	   	object->M_next = NULL;
   	   }

   	   object->M_previous = NULL;
   	   M_start = object;
   	   object->hit();
   	}

   	// put a new object in the back of the list.
   	void put_back(node* object)
   	{
   	   object->M_next = NULL;
   	   object->M_previous = M_end;
   	   M_start->next = object;
   	   M_start = object;
   	}

   	// pop last object from list.
   	void pop_back()
   	{
   	   node* l_node = M_end->M_previous;
   	   free_object(M_end);
   	   M_end = l_node;
   	}

   	std::vector<node*> M_free; // vector of objects not on the list.
  	node* M_start; // Head of the used list.
   	node* M_end; // Tail of the used list.   	

   	time_t M_MaxIdleTime; // Maximum Idle time for objects.
   	node* M_start_allocated; // start point of allocated memory on heap.
   	node* M_end_allocated; // end point of allocated memory on heap.
};

}

#endif // ELECTRONIC_NETWORKS__CACHE_H

