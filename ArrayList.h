/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "Utility.h"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, it means
 * the length of the array of your inner implemention
 * For example, even if the capacity is 10, the method "isEmpty()" may still return true.
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class E>
class ArrayList
{
public:
    E *data;
    int capacity;
    int size1;

public:
    class ConstIterator
    {
    public:
            //E *pos;
            ArrayList<E> *which;
            int pos;
            //E *prev;
    public:

        /*ConstIterator(ArrayList<E> *whichone):which(whichone)
        {
            pos = which->data-1;

        }*/
        /**
         * Returns true if the iteration has more elements.
         * O(1)
         */
        bool hasNext()
        {
            if (pos == -1 && which->size1 != 0) return true;
            if (pos < which->size1 - 1) return true;
            return false;
            /*if (pos >= which->data + which->size1 - 1) return false;
            else return true;*/
        }

        /**
         * Returns the next element in the iteration.
         * O(1)
         * @throw ElementNotExist
         */
        const E& next()
        {
            if (/**pos == data[size1 - 1]*/!hasNext()) throw ElementNotExist();
            pos = pos + 1;
            return which->data[pos];
        }
    };

    class Iterator
    {
    public:
        //E *pos;
        bool removed;
        //ArrayList *arr;
        int pos;
        ArrayList<E> *which;
    public:

        /*Iterator(ArrayList<E> *whichone,E *obj = NULL):which(whichone)
        {
            pos = obj;
            removed = false;
        }*/
        /**
         * Returns true if the iteration has more elements.
         * O(1)
         */
        bool hasNext()
        {
            //if (pos >= which->data + which->size1 - 1) return false;
            //else return true;
            if (pos == -1 && which->size1 != 0) return true;
            if (pos < which->size1 - 1) return true;
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(1)
         * @throw ElementNotExist
         */
        E& next()
        {
            if (!hasNext()) throw ElementNotExist();
            pos = pos + 1;
            removed = true;
            return which->data[pos];
        }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(n)
         * @throw ElementNotExist
         */
        void remove()
        {
            if (removed == false) //throw ElementNotExist("Element not exist.");
            throw ElementNotExist();
            else
            {
                removed = false;
                int i;
                //for (i = 0;which->data[i] != *pos;++i);
                //*pos = data[i - 1];
                //for (int j = i;j < size1 - 1;++j)
                //data[j] = data[j + 1];
                //E *tmp=pos;
                /*while (hasNext())
                {
                    *pos=*(pos+1);
                    pos++;
                }*/
                for (int i = pos;i < which->size1;++i)
                which->data[i] = which->data[i + 1];
                --pos;
                --which->size1;

            }
        }
    };

    /**
     * Constructs an empty list with an initial capacity of ten.
     */
    ArrayList()
    {
        capacity = 10;
        data = new E[10];
        size1 = 0;
    }

    void doubleSpace()
    {
        E *tmp = new E[capacity];
        for (int i = 0;i < size1;++i) tmp[i] = data[i];
        delete[]data;
        capacity *= 2;
        data = new E[capacity];
        for (int i = 0;i < size1;++i) data[i] = tmp[i];
        //data = new E(2 * capacity);
        //delete []data;

        //for (int i = 0;i < size1;++i) data[i] = tmp[i];
        delete[]tmp;

    }

    /**
     * Constructs a list containing the elements of the specified collection, in
     * the order they are returned by the collection's iterator.
     */
    template <class E2>
    explicit ArrayList(const E2& x) {
        size1 = 0;
        capacity=2 * x.size();
        data=new E[capacity];
        addAll(*this,x);
        //ArrayList<E> a;
        //addAll(a,x);
        //data = a.data;
        //size1 = a.size1;
        //capacity = a.capacity;

    }

    /**
     * Constructs an empty list with the specified initial capacity.
     */
    ArrayList(int initialCapacity)
    {
        capacity = initialCapacity;
        data = new E[capacity];
        size1 = 0;
    }

    /**
     * Destructor
     */
    ~ArrayList()
    {
        delete []data;
    }

    /**
     * Assignment operator
     */
    ArrayList& operator=(const ArrayList& x)
    {
        capacity = x.capacity;
        size1 = x.size1;
        data = new E[capacity];
        for (int i = 0;i < size1;++i)
        data[i] = x.data[i];
        return *this;
    }

    /**
     * Copy-constructor
     */
    ArrayList(const ArrayList& x)
    {
        capacity = x.capacity;
        size1 = x.size1;
        data = new E[capacity];
        for (int i = 0;i < size1;++i)
        data[i] = x.data[i];
    }

    /**
     * Returns an iterator over the elements in this list in proper sequence.
     */
    Iterator iterator()
    {
        Iterator *a = new Iterator;
        a->which = this;
        a->pos = -1;
        a->removed = false;
        return *a;
    }

    /**
     * Returns an CONST iterator over the elements in this list in proper sequence.
     */
    ConstIterator constIterator() const
    {
        ConstIterator *a = new ConstIterator;
        a->which = this;
        a->pos = -1;

        return (*a);
    }

    /**
     * Appends the specified element to the end of this list.
     * O(1)
     */
    bool add(const E& e)
    {
        if (size1 == capacity - 1) doubleSpace();
        data[size1++] = e;
        return true;
    }

    /**
     * Inserts the specified element at the specified position in this list.
     * The range of index is [0, size].
     * O(n)
     * @throw IndexOutOfBound
     */
    void add(int index, const E& element)
    {
        if(index < 0||index > size1) throw IndexOutOfBound();
        if(size1 == capacity) doubleSpace();
        for (int j = size1;j > index;--j) data[j] = data[j -1];
        data[index] = element;
        ++size1;
    }

    /**
     * Removes all of the elements from this list.
     */
    void clear()
    {
        size1 = 0;
    }

    /**
     * Returns true if this list contains the specified element.
     * O(n)
     */
    bool contains(const E& e) const
    {
        int i=0;
        for (;i < size1 &&data[i] != e; ++i);
        if (i ==size1) return false;
        else return true;
    }

    /**
     * Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
     */
    void ensureCapacity(int minCapacity)
    {
        if (capacity < minCapacity)
        {
            E *tmp = new E[minCapacity];
            for (int i = 0;i < size1;++i) tmp[i] = data[i];
            delete []data;
            data = new E[minCapacity];
            for (int i = 0;i < size1;++i) data[i] = tmp[i];
            delete []tmp;
            capacity = minCapacity;
        }

    }

    /**
     * Returns a reference to the element at the specified position in this list.
     * O(1)
     * @throw IndexOutOfBound
     */
    E& get(int index)
    {
        if (index < 0 || index >= size1) throw IndexOutOfBound();
        return data[index];
    }

    /**
     * Returns a const reference to the element at the specified position in this list.
     * O(1)
     * @throw IndexOutOfBound
     */
    const E& get(int index) const
    {
        if (index < 0 || index >= size1) throw IndexOutOfBound();
        return data[index];
    }

    /**
     * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * O(n)
     */
    int indexOf(const E& e) const
    {
        int i;
        for (i = 0;i < size1 && data[i] != e;++i);
        if (i == size1) return -1;
        else return i;

    }

    /**
     * Returns true if this list contains no elements.
     * O(1)
     */
    bool isEmpty() const
    {
        return size1 == 0;
    }

    /**
     * Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
     * O(n)
     */
    int lastIndexOf(const E& e) const
    {
        int i;
        for (i = size1 - 1;i >= 0&&data[i] != e;--i);
        return i;
    }

    /**
     * Removes the element at the specified position in this list.
     * Returns the element that was removed from the list.
     * O(n)
     * @throw IndexOutOfBound
     */
    E removeIndex(int index)
    {
        if (index < 0 || index >= size1) throw IndexOutOfBound();
        E tmp = data[index];
        for (int i = index;i < size1 - 1;++i) data[i] = data[i + 1];
        --size1;
        return tmp;
    }

    /**
     * Removes the first occurrence of the specified element from this list, if it is present.
     * O(n)
     */                     //????????????????????bool类型的，什么时候返回true？什么时候返回false？
    bool remove(const E& e)
    {
        for (int i = 0;i < size1;++i)
        {
            if(data[i] == e)
            {
                for (int k = i;k < size1 - 1;++k)
                data[k] = data[k + 1];
                --size1;
                return true;
            }
        }
        return false;
    }

    /**
     * Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
     * O(n)
     * @throw IndexOutOfBound
     */                                  //???????????????如果toindex<=fromindex如何throw错误？
    void removeRange(int fromIndex, int toIndex)
    {
        if(fromIndex < 0 ||toIndex > size1) throw IndexOutOfBound();
        for (int i = fromIndex;i < size1 - (toIndex - fromIndex);++i) data[i] = data[i+(toIndex - fromIndex)];
        size1 -= (toIndex - fromIndex);
    }

    /**
     * Replaces the element at the specified position in this list with the specified element.
     * Returns the element previously at the specified position.
     * O(1)
     * @throw IndexOutOfBound
     */
    E set(int index, const E& element)
    {
        if (index < 0 || index >= size1) throw IndexOutOfBound();
        E tmp = data[index];
        data[index] = element;
        return tmp;
    }

    /**
     * Returns the number of elements in this list.
     * O(1)
     */
    int size() const
    {
        return size1;
    }

    /**
     * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
     * O(n)
     * @throw IndexOutOfBound
     */
    ArrayList subList(int fromIndex, int toIndex) const
    {
        ArrayList<E> tmp;
        tmp.data = new E[2*(toIndex - fromIndex)];
        tmp.capacity = 2*(toIndex - fromIndex);
        tmp.size1 = toIndex - fromIndex;
        for (int i = 0;i < tmp.size1;++i)
        tmp.data[i] = data[fromIndex + i];
        return tmp;
    }
};
#endif

