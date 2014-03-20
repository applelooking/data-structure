/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "Utility.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your inner implemention, not the current number of the
 * elements.
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
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * We don't require an order in the iteration, but you should
 * guarantee all elements will be iterated.
 */
template <class K, class V, class H>
class HashMap
{
private:
    struct node
    {
        Entry<K,V> data;
        node *next;
        node *circle;
        node (const Entry<K,V> &d):data(d)
        {

            next = NULL;
            circle = NULL;
        }
        /*node () :data(t)
        {
            //K k;
            //V v;
            //Entry<K,V> t(k,v);
            //data = t;
            next = NULL;
            circle = NULL;
        }*/
    };

    node **array;
public:
    int size1;

public:
    class ConstIterator
    {
     public:
        const HashMap<K,V,H> *which;
        int no;
        node *pos;
        node *prev;
    public:
        /**
         * Returns true if the iteration has more elements.
         * O(n) for iterating through the container.
         */
        bool hasNext()
        {
            //bool flag1 = false;
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
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        const Entry<K, V>& next()
        {
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();
            if (pos->circle == pos)
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

    class Iterator
    {
    public:
        HashMap<K,V,H> *which;
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
         * Returns a const reference the next element in the iteration.
         * O(n) for iterating through the container.
         * @throw ElementNotExist
         */
        Entry<K, V>& next()
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
                else for (int i = no;i < which->size1;++i)
                    {
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
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(1)
         * @throw ElementNotExist
         */
        void remove()
        {
            node *tmp;
            if (last == NULL) throw ElementNotExist();
            which->remove(pos->data.key);
            bool flag = false;
            for (int i = 0;i < which->size1;++i)
            {
                if (which->array[i]->next != NULL)
                {
                    tmp = which->array[i]->next;
                    while (tmp != NULL)
                    {
                        if (tmp->data.key == last->data.key)
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
     * Constructs an empty list with an initial capacity.
     * You can construct it with your own initial capacity.
     */
    HashMap()
    {
        size1 = 18;
        K k;
        V v;
        Entry<K,V> t(k,v);
        array = new node*[18];
        for (int i = 0;i < 18;++i)
        array[i] = new node(t);

    }

    /**
     * Copy-constructor
     */
    HashMap(const HashMap& c)
    {
        array = new node*[c.size1];
        K k;
        V v;
        Entry<K,V> t(k,v);
        for (int i = 0;i < c.size1;++i)
        array[i] = new node(t);
        size1 = c.size1;
        addAll(*this,c);
    }

    /**
     * Constructs an empty HashMap with the specified initial capacity
     */
    HashMap(int initialCapacity)
    {
        array = new node*[initialCapacity];
        K k;
        V v;
        Entry<K,V> t(k,v);
        size1 = initialCapacity;
        for (int i = 0;i < size1;++i)
        array[i] = new node(t);
    }

    /**
     * Constructs a new HashMap with the same mappings as the specified Map.
     */
    template <class E2>
    explicit HashMap(const E2 &c)
    {
        array = new node*[c.size1];
        K k;
        V v;
        Entry<K,V> t(k,v);
        size1 = c.size();
        for (int i = 0;i < size1;++i)
        array[i] = new node(t);
        addAll(*this,c);
    }

    /**
     * assignment operator
     */
    HashMap& operator=(const HashMap& c)
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
     * destructor
     */
    ~HashMap()
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
     * Returns an iterator over the elements in this map in proper sequence.
     */
    Iterator iterator()
    {
        Iterator *a = new Iterator;
        K k;
        V v;
        Entry<K,V> t(k,v);
        a->prev = new node(t);
        a->prev->circle = a->prev;
        a->pos = a->prev;
        a->which = this;
        a->last = NULL;
        a->no = -1;
        return *a;
    }

    /**
     * Returns an CONST iterator over the elements in this map in proper sequence.
     */
    ConstIterator constIterator() const
    {
        K k;
        V v;
        Entry<K,V> t(k,v);
        ConstIterator *a = new ConstIterator;
        a->prev = new node(t);
        a->prev->circle = a->prev;
        a->pos = a->prev;
        a->which = this;
        //a->last = NULL;
        a->no = -1;
        return *a;
    }

    /**
     * Removes all of the mappings from this map.
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
     * Returns true if this map contains a mapping for the specified key.
     * O(1) for average
     */
    bool containsKey(const K& elem) const
    {
        K tmp = elem;
        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        while( p != NULL && p->data.key != tmp)
        p = p->next;
        if (p == NULL) return false;
        else return true;
    }

    /**
     * Returns true if this map maps one or more keys to the specified value.
     * O(n)
     */
    bool containsValue(const V& elem) const
    {
        V tmp = elem;
        node *p;
        for (int i = 0;i < size1;++i)
        {
            if (array[i]->next != NULL)
            {
                p = array[i]->next;
                while (p != NULL)
                {
                    if (p->data.value == tmp)
                    return true;

                    p = p->next;
                }
            }
        }
        return false;
    }

    /**
     * Returns a reference to the value to which the specified key is mapped.
     * O(1) for average
     * @throw ElementNotExist
     */
    V& get(const K& k)
    {
        //if (!containsKey(k)) throw ElementNotExist();
        K tmp = k;
        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        while( p != NULL && p->data.key != tmp)
        p = p->next;
        if (p == NULL) throw ElementNotExist();
        else return p->data.value;


    }

    /**
     * Returns a const reference to the value to which the specified key is mapped.
     * O(1) for average
     * @throw ElementNotExist
     */
    const V& get(const K& k) const
    {
        K tmp = k;
        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        while( p != NULL && p->data.key != tmp)
        p = p->next;
        if (p == NULL) throw ElementNotExist();
        else return p->data.value;
    }

    /**
     * Returns true if this map contains no key-value mappings.
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
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the default-constructor.
     * O(1)
     */

    bool add(const Entry<K,V>& elem)
    {
        K tmp=elem.key;

        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        node *q = array[tmp2];
        while (p != NULL && p->data.key != elem.key )
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



    V put(const K& k, const V& v)
    {
        K tmp = k;
        int tmp1 = H::hashcode(tmp);
        int tmp2 = tmp1 % size1;
        node *p = array[tmp2]->next;
        while( p != NULL && p->data.key != tmp)
        p = p->next;
        if (p == NULL)
        {
            V tmpv = v;
            Entry<K,V> t(k,v);
            //p = new node(t);
            add(t);
            return tmpv;
        }
        else
        {
            V tmpv = p->data.value;
            p->data.value = v;
            return tmpv;
        }
    }

    /**
     * Removes the mapping for the specified key from this map if present.
     * Returns the previous value.
     * O(1) for average
     * @throw ElementNotExist
     */
    V remove(const K& elem)
    {
        K tmp = elem;
        int tmptmp = H::hashcode(tmp);
        int tmp1 = tmptmp % size1;
        node *tmpnode = array[tmp1]->next;
        node *tmpprev = array[tmp1];
        while (tmpnode != NULL)
        {
            if (tmpnode->data.key != elem)
            {
                tmpprev = tmpnode;
                tmpnode = tmpnode->next;
            }
            else
            {

                //node *p = tmpnode;
                tmpprev->next = tmpnode->next;
                V tmpvalue = tmpnode->data.value;
                delete tmpnode;
                return tmpvalue;

            }
        }
        throw ElementNotExist();
    }

    /**
     * Returns the number of key-value mappings in this map.
     * O(1)
     */
    int size() const
    {
        node *p;
        int value = 0;
        for (int i = 0;i < size1;++i)
        {
            if (array[i]->next != NULL)
            p = array[i]->next;
            while (p != NULL)
            {
                p = p->next;
                ++value;
            }
        }
        return value;
    }
};
#endif
