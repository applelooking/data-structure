/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "Utility.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T>
class LinkedList {
private:
    struct node{
        T data;
        node * prev,*next;

        node (const T &x,node *p = NULL,node *n = NULL)
            {
                data = x;
                prev = p;
                next = n;
            }
        node ():next(NULL),prev(NULL){}
        ~node(){}
    };

    node *head,*tail;
public:
    int size1;

    node * move(int i) const
    {
        node * p = head->next;

        if (i < 0||i > size1) throw IndexOutOfBound("Out of bound.");
        while(i--) p = p->next;
        return p;
    }

public:
    class ConstIterator {
    private:
        node *cur;
        const LinkedList<T> *which;
    public:
        ConstIterator(const LinkedList<T> *whichone):which(whichone)
        {
            cur = which->head;


        }
        /**
         * Returns true if the iteration has more elements.
         * O(1).
         */
        bool hasNext()
        {
            if (cur==NULL || cur->next==NULL || cur->next->next == NULL) return false;
            return true;
        }

        /**
         * Returns the next element in the iteration.
         * O(1).
         * @throw ElementNotExist exception when hasNext() == false?????????????????????????????
         */
        const T& next()
        {
            if (!hasNext()) throw ElementNotExist("element not exist");
            cur=cur->next;
            return cur->data;
        }
    };

    class Iterator {
    private:
        node *cur;
        bool removed;
        LinkedList<T> *which;
    public:
        Iterator(LinkedList<T> *whichone,node *obj = NULL):which(whichone)
        {
            cur = obj;
            removed=false;
        }
        /**
         * Returns true if the iteration has more elements.
         * O(1).
         */
        bool hasNext()
        {
            if (cur==NULL || cur->next==NULL || cur->next->next == NULL) return false;
            else return true;
        }

        /**
         * Returns the next element in the iteration.
         * O(1).
         * @throw ElementNotExist exception when hasNext() == false
         */
        T& next()
        {
            if (!hasNext()) throw ElementNotExist("element not exist");
            cur=cur->next;
            removed=true;
            return cur->data;
        }

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator
         * O(1).
         * @throw ElementNotExist
         */
        void remove()
        {
            if (removed == false) throw ElementNotExist();
            else
            {
                node *tmp;
                tmp = cur;
                cur = tmp->prev;
                cur->next = tmp->next;
                tmp->next->prev=cur;
                removed = false;
                --which->size1;
            }
        }
    };

    /**
     * Constructs an empty list
     */
    LinkedList()
    {
        head = new node;
        head -> next = tail = new node;
        tail ->prev = head;
        size1 = 0;
    }

    /**
     * Copy constructor
     * You may utilize the ``addAll'' function from Utility.h
     */
    LinkedList(const LinkedList<T> &c)
    {
        head = new node;
        tail = new node;
        //size1 = 0;
        //addAll(*this,c);
        //head = c.head;
        //tail = c.tail;
        node *tmp;
        tmp = (c.head)->next;
        node *tmp1,*tmp2,*r = head;
        while (tmp != c.tail)
        {
            tmp1=new node(tmp->data,r,tail);
            //tmp1->data = tmp->data;
            //tmp2 = new node;
            //tmp1->next = tmp2;
            //tmp2->prev = tmp1;
            //tmp = tmp->next;
            //tmp1=tmp2;
            r->next=tmp1;
            r=r->next;
            tmp=tmp->next;
        }
        /*tmp1->next = tail;*/
        tail->prev = tmp1;
        tail->next=NULL;
        size1=c.size1;


    }

    /**
     * Assignment operator
     * You may utilize the ``addAll'' function from Utility.h
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) {
        clear();
        head = new node;
        tail = new node;
        //size1 = 0;
        //addAll(*this,c);
        //head = c.head;
        //tail = c.tail;
        node *tmp;
        tmp = (c.head)->next;
        node *tmp1,*tmp2,*r = head;
        while (tmp != c.tail)
        {
            tmp1=new node(tmp->data,r,tail);
            //tmp1->data = tmp->data;
            //tmp2 = new node;
            //tmp1->next = tmp2;
            //tmp2->prev = tmp1;
            //tmp = tmp->next;
            //tmp1=tmp2;
            r->next=tmp1;
            r = r->next;
            tmp = tmp->next;
        }
        /*tmp1->next = tail;*/
        tail->prev = tmp1;
        tail->next = NULL;
        size1=c.size1;

        return *this;
    }


    /**
     * Constructs a list containing the elements of the specified
     * collection, in the order they are returned by the collection's
     * const iterator.
     * You may utilize the ``addAll'' function from Utility.h
     */
    template <class C> LinkedList(const C& c) {
        head = new node;
        head -> next = tail = new node;
        tail ->prev = head;
        size1 = 0;
        addAll(*this,c);
    }

    /**
     * Desturctor
     */
    ~LinkedList()
    {
        clear();
        delete head;
        delete tail;
    }

    /**
     * Inserts the specified element at the specified position in
     * this list.
     * O(n)
     * @throw IndexOutOfBound exception when index is out of bound
     */
    void add(int index, const T& elem)
    {
        node *pos,*tmp;

        pos = move(index);
        tmp = new node(elem,pos->prev,pos);
        pos->prev->next = tmp;
        pos->prev = tmp;

        ++size1;
    }

    /**
     * Appends the specified element to the end of this list.
     * O(1).
     * Always returns true;
     */
    bool add(const T& elem)
    {
        node *tmp = new node(elem,tail->prev,tail);
        tail->prev->next = tmp;
        tail->prev = tmp;
        ++size1;
        return true;
    }

    /**
     * Inserts the specified element at the beginning of this list.
     * O(1).
     */
    void addFirst(const T& elem)
    {
        node *tmp = new node(elem,head,head->next);
        head->next->prev = tmp;
        head->next = tmp;
        ++size1;
        return ;
    }

    /**
     * Removes all of the elements from this list.
     * O(n).
     */
    void clear()
    {
        node *p = head->next,*q;
        head->next = tail;
        tail->prev = head;
        while (p != tail)
        {
            q = p->next;
            delete p;
            p = q;
        }
        size1 = 0;
    }

    /**
     * Returns true if this list contains the specified element.
     * O(n).
     */
    bool contains(const T& elem) const
    {
        node *p = head;
        while (p != tail)
        {
            if (p->data == elem) return true;
            else p = p->next;
        }
        if (p == tail)
        return false;
    }

    /**
     * Returns a reference to the element at the specified position.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T& get(int index)
    {
        if (index < 0 || index > size1) throw IndexOutOfBound();
        node *p = move(index);
        return p->data;
    }

    /**
     * Returns a const reference to the element at the specified position.
     * O(n).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const
    {
        if (index < 0|| index > size1) throw IndexOutOfBound();
        node *p = move(index);
        return p->data;
    }

    /**
     * Returns a reference to the first element.
     * O(1).
     * @throw ElementNotExist
     */
    T& getFirst()
    {
        if (head->next == tail) throw ElementNotExist();
        node *p = head->next;
        return p->data;
    }

    /**
     * Returns a const reference to the first element.
     * O(1).
     * @throw ElementNotExist
     */
    const T& getFirst() const
    {
        if (head->next == tail) throw ElementNotExist();
        node *p = head->next;
        return p->data;
    }

    /**
     * Returns a reference to the last element.
     * O(1).
     * @throw ElementNotExist
     */
    T& getLast()
    {
        if (tail->prev == head) throw ElementNotExist();
        node *p = tail->prev;
        return p->data;
    }

    /**
     * Returns a const reference to the last element.
     * O(1).
     * @throw ElementNotExist
     */
    const T& getLast() const
    {
        if (tail->prev == head) throw ElementNotExist();
        node *p = tail->prev;
        return p->data;
    }

    /**
     * Returns the index of the first occurrence of the specified element
     * O(1).?????????????????????????????
     * in this list, or -1 if this list does not contain the element.
     */
    int indexOf(const T& elem) const
    {
        node *p = head->next;
        int value = 0;
        for (;p != head;++value,p = p->next)
        {
            if (p->data == elem) return value;
        }
        if (p == tail) return -1;

    }

    /**
     * Returns true if this list contains no elements.
     * O(1).
     */
    bool isEmpty() const
    {
        return size1 == 0;
    }

    /**
     * Returns an iterator
     * O(1).
     */
    Iterator iterator() {return Iterator(this,head);}

    /**
     * Returns an const iterator
     * O(1).
     */
    ConstIterator constIterator() const {return ConstIterator(this);}

    /**
     * Removes the element at the specified position in this list.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T removeIndex(int index)
    {
        if (index < 0||index > size1) throw IndexOutOfBound();
        node *p = move(index);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        --size1;
        return p->data;

    }

    /**
     * Removes the first occurrence of the specified element from this
     * O(n).
     * list, if it is present.
     */
    bool remove(const T& elem)
    {
        node *p = head->next;
        while (p != tail)
        {
            if (p->data == elem)
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                --size1;
                return true;
            }
            else p = p->next;
        }
        if (p == tail) return false;
    }

    /**
     * Removes and returns the first element from this list.
     * O(1).
     * @throw ElementNotExist
     */
    T removeFirst()
    {
        if (head->next == tail) throw ElementNotExist();
        node *p = head->next;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        --size1;
        return p->data;
    }

    /**
     * Removes and returns the last element from this list.
     * O(1).
     * @throw ElementNotExist
     */
    T removeLast()
    {
        if (tail->prev == head) throw ElementNotExist();
        node *p = tail->prev;
        tail->prev = p->prev;
        p->prev->next = tail;
        --size1;
        return p->data;
    }

    /**
     * Replaces the element at the specified position in this list with
     * the specified element.
     * O(n).
     * @throw IndexOutOfBound exception when index is out of bound
     */
    T set(int index, const T& elem)
    {
        if (index < 0 || index > size1) throw IndexOutOfBound();
        node *p = move(index);
        T tmp = p->data;
        p->data = elem;
        return tmp;
    }

    /**
     * Returns the number of elements in this list.
     */
    int size() const
    {
        return size1;
    }

    /**
     * Returns a view of the portion of this list between the specified
     * fromIndex, inclusive, and toIndex, exclusive.
     * O(n).
     * @throw IndexOutOfBound
     */
    LinkedList<T> subList(int fromIndex, int toIndex)
    {
        if (fromIndex < 0 || toIndex > size1) throw IndexOutOfBound();
        LinkedList<T> tmptmp;
        node *tmp;
        tmp = move(fromIndex);
        node *tmp1,*tmp2,*r = tmptmp.head;
        while (tmp != move(toIndex))
        {
            tmp1=new node(tmp->data,r,tmptmp.tail);
            //tmp1->data = tmp->data;
            //tmp2 = new node;
            //tmp1->next = tmp2;
            //tmp2->prev = tmp1;
            //tmp = tmp->next;
            //tmp1=tmp2;
            r->next=tmp1;
            r=r->next;
            tmp=tmp->next;
        }
        /*tmp1->next = tail;*/
        (tmptmp.tail)->prev = tmp1;
        (tmptmp.tail)->next=NULL;
        tmptmp.size1=toIndex-fromIndex;

        return tmptmp;
    }
};
#endif

