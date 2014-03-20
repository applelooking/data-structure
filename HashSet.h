/** @file */
#ifndef __HASHSET_H
#define __HASHSET_H

#include "Utility.h"

/**
 * A HashSet holds elements using a hash table, providing facilities
 * to insert, remove an element into the container and search an
 * element within the container efficiently.
 *
 * We don't require an order in the iteration, but you should
 * guarantee all elements will be iterated.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashcode'',
 * which takes a parameter of type T and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashcode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashSet<int, Hashint> hash;
 * @endcode
 */
template <class T, class H> class HashSet {
private:
    struct node
    {
        T data;
        node *next;
        node *circle;
        node (const T &d)
        {
            data = d;
            next = NULL;
            circle = NULL;
        }
        node ()
        {
            next = NULL;
            circle = NULL;
        }
    };

    node **array;
public:
int size1;



public:
    class ConstIterator {
    public:
        const HashSet<T,H> *which;
        int no;
        node *pos;
        node *prev;
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container
         */
        bool hasNext()
        {
            //bool flag1 = false;
            if (pos->circle == pos)
            {
                for (int i = 0;i < which->size1;++i)
                    if (which->array[i]->next != NULL) return true;
                return false;
            }

            //node *tmp = which->array[no];
            if (pos->next != NULL) return true;
            else
            {
                for (int i = no + 1;i < which->size1;++i)
                if (which->array[i]->next != NULL) return true;
            }
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        const T& next()
        {
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();
            if (pos->circle == pos)
            {
                if (no == -1)
                {
                    for (int i = no + 1;i < which->size1;++i)
                    {
                        ++no;
                        if (which->array[i]->next != NULL)
                        {
                            pos = which->array[i]->next;
                            return pos->data;
                        }
                    }
                }
                else
                {
                    for (int i = no;i < which->size1;++i)
                    {
                        if (which->array[i]->next != NULL)
                        {
                            pos = which->array[i]->next;
                            return pos->data;
                            return pos->data;
                        }
                    }
                }
            }
            else
            {
                if (pos->next != NULL)
                {
                    pos = pos->next;
                    return pos->data;
                }
                else
                {
                    for(int i = no + 1;i <which->size1;++i)
                    {
                        ++no;
                        if (which->array[i]->next != NULL)
                        {
                            pos = which->array[i]->next;
                            return pos->data;
                        }
                    }
                }
            }
        }
    };

    class Iterator {
    public:
        HashSet<T,H> *which;
        int no;
        node *pos;
        node *prev;
        node *last;
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container.
         */
        bool hasNext()
        {
            if (pos->circle == pos)
            {
                for (int i = 0;i < which->size1;++i)
                {
                    if (which->array[i]->next != NULL)
                    return true;
                }
                return false;
            }

            //node *tmp = which->array[no];
            if (pos->next != NULL) return true;
            else
            {
                for (int i = no + 1;i < which->size1;++i)
                if (which->array[i]->next != NULL) return true;
            }
            return false;
        }

        /**
         * Returns the next element in the iteration.
         * O(n) for iterating through the container
         * @throw ElementNotExist
         */
        const T& next()
        {
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();
            if (pos->circle == pos)
            {
                if (no == -1)
                {
                    for (int i = no + 1;i < which->size1;++i)
                    {
                        ++no;
                        if (which->array[i]->next != NULL)
                        {
                            last = pos;
                            pos = which->array[i]->next;
                            return pos->data;
                        }
                    }
                }
                else
                {
                    for (int i = no;i < which->size1;++i)
                    {
                        if (which->array[i]->next != NULL)
                        {
                            last = pos;
                            pos = which->array[i]->next;
                            return pos->data;
                        }
                    }
                }
            }
            else
            {
                if (pos->next != NULL)
                {
                    last = pos;
                    pos = pos->next;
                    return pos->data;
                }
                else
                {
                    for(int i = no + 1;i <which->size1;++i)
                    {
                        ++no;
                        if (which->array[i]->next != NULL)
                        {
                            last = pos;
                            pos = which->array[i]->next;
                            return pos->data;
                        }
                    }
                }
            }
        }

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator.
         * O(1)
         * @throw ElementNotExist
         */
        void remove()
        {
            node *tmp;
            if (last == NULL) throw ElementNotExist();
            which->remove(pos->data);
            bool flag = false;
            for (int i = 0;i < which->size1;++i)
            {
                if (which->array[i]->next != NULL)
                {
                    tmp = which->array[i]->next;
                    while (tmp != NULL)
                    {
                        if (tmp->data == last->data)
                        {
                            no = i;
                            flag = true;

                            break;
                        }
                        tmp = tmp->next;
                    }
                    if (tmp == NULL) no = -1;
                }
                if (flag == true)
                break;
            }
            pos = last;
            last = NULL;
        }
    };

    /**
     * Constructs a empty set with your own default capacity
     */
    HashSet()
    {
        size1 = 18;
        array = new node*[18];
        for (int i = 0;i < 18;++i)
        array[i] = new node;

    }

    /**
     * Destructor
     */
    ~HashSet()
    {
        node *p;
        node *q;

        for (int i = 0;i < size1;++i)
        {
            p = array[i];
            do
            {
                q = p->next;
                delete p;
                p = q;
            }while(p != NULL);
        }
        delete []array;
    }

    /**
     * Copy constructor
     */
    HashSet(const HashSet &c)
    {
        array = new node*[c.size1];
        for (int i = 0;i < c.size1;++i)
        array[i] = new node;
        size1 = c.size1;
        addAll(*this,c);
    }

    /**
     * Assignment operator
     */
    HashSet& operator=(const HashSet &c)
    {
        node *p;
        node *q;

        for (int i = 0;i < size1;++i)
        {
            p = array[i];
            do
            {
                q = p->next;
                delete p;
                p = q;
            }while(p != NULL);
        }
        delete []array;

        array = new node*[c.size1];
        size1 = c.size1;
        for (int i = 0;i < size1;++i)
        array[i] = new node;
        addAll(*this,c);
        return *this;
    }

    /**
     * Constructs a new set containing the elements in the specified
     * collection.
     */
    template<class C>
    explicit HashSet(const C& c)
    {
        array = new node*[c.size1];
        size1 = c.size();
        for (int i = 0;i < size1;++i)
        array[i] = new node;
        addAll(*this,c);
    }

    /**
     * Constructs a new, empty set; the backing HashMap instance has the
     * specified capacity
     */
    HashSet(int capacity)
    {
        array = new node*[capacity];
        size1 = capacity;
        for (int i = 0;i < size1;++i)
        array[i] = new node;
    }

    /**
     * Adds the specified element to this set if it is not already present.
     * Returns false if element is previously in the set.
     * O(1) for average
     */
    bool add(const T& elem)
    {
        T tmp=elem;
        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        node *q = array[tmp2];
        while (p != NULL && !(p->data == elem))
        {
            q = p;
            p = p->next;
        }
        if (p != NULL) return false;
        else
        {
            p = new node(elem);
            q->next = p;
            return true;
        }
    }

    /**
     * Removes all of the elements from this set.
     */
    void clear()
    {
        node *p;
        node *q;

        for (int i = 0;i < size1;++i)
        {
            /*p = array[i];
            do
            {
                q = p->next;
                delete p;
                p = q;
            }while(p != NULL);*/
            p = array[i]->next;
            while (p != NULL)
            {
                q = p->next;
                delete p;
                p = q;
            }
            array[i]->next = NULL;
        }

    }

    /**
     * Returns true if this set contains the specified element.
     * O(1) for average
     */
    bool contains(const T& elem) const
    {
        T tmp = elem;
        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        while( p != NULL && !(p->data == tmp))
        p = p->next;
        if (p == NULL) return false;
        else return true;

    }

    /**
     * Returns true if this set contains no elements.
     * O(1)
     */
    bool isEmpty() const
    {

        for (int i = 0;i < size1;++i)
        {
            if (array[i]->next != NULL)
            return false;
        }
        return true;
    }

    /**
     * Returns an iterator over the elements in this set.
     */
    Iterator iterator()
    {
        Iterator *a = new Iterator;
        a->prev = new node;
        a->prev->circle = a->prev;
        a->pos = a->prev;
        a->which = this;
        a->last = NULL;
        a->no = -1;
        return *a;
    }

    /**
     * Returns an const iterator over the elements in this set.
     */
    ConstIterator constIterator() const
    {
        ConstIterator *a = new ConstIterator;
        a->prev = new node;
        a->prev->circle = a->prev;
        a->pos = a->prev;
        a->which = this;
        //a->last = NULL;
        a->no = -1;
        return *a;
    }

    /**
     * Removes the specified element from this set if it is present.
     * O(1) for average
     */
    bool remove(const T& elem)
    {
        T tmp = elem;
        int tmptmp = H::hashcode(tmp);
        int tmp1 = tmptmp % size1;
        node *tmpnode = array[tmp1]->next;
        node *tmpprev = array[tmp1];
        while (tmpnode != NULL)
        {
            if (tmpnode->data != elem)
            {
                tmpprev = tmpnode;
                tmpnode = tmpnode->next;
            }
            else
            {

                //node *p = tmpnode;
                tmpprev->next = tmpnode->next;
                delete tmpnode;
                return true;

            }
        }
        return false;
    }

    /**
     * Returns the number of elements in this set (its cardinality).
     * O(1)
     */
    int size() const
    {
        int value = 0;
        for (int i = 0;i < size1;++i)
        {
            node *p = array[i]->next;
            while(p != NULL)
            {
                ++value;
                p = p->next;
            }
        }
        return value;
    }
};

#endif

