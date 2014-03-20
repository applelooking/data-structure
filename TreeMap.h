/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"
#include <ctime>
#include <cstdlib>

/**
 * A map is a sequence of (key, value) entries that provides fast retrieval
 * based on the key. At most one value is held for each key.
 *
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V>
class TreeMap {
private:
    struct node
    {
        Entry<K,V> data;
        int rand1;
        node *left;
        node *right;
        node *father;
        /*node()
        {
            K k;
            V v;
            Entry<K,V> t(k,v);
            data = t;
            left = right = father = NULL;
            rand1 = rand();
        }*/
        node (Entry<K,V> d,node *f = NULL):data(d),father(f)
        {
            left = right = NULL;
            rand1 = rand();
        }
    };

    node *root;
public:
    int size1;
public:
    class ConstIterator {
    public:

    const TreeMap<K,V> *which;
    node *pos;
    node *prev;

    public:
        /**
         * Returns true if the iteration has more elements.
         * Amortized O(1).
         */
        bool hasNext()
        {
            if (pos->left == pos && pos->right != NULL) return true;
            if (pos->left == pos && pos->right == NULL) return false;
            node *tmp = which->root;
            //if (pos->right == tmp) return true;
            if (tmp == NULL) return false;
            while (tmp->right != NULL) tmp = tmp->right;
            K tmp1 = tmp->data.key;
            if (pos->data.key < tmp1) return true;
            else return false;
        }

        /**
         * Returns a const reference to the next element in the iteration.
         * Amortized O(1).
         * @throw ElementNotExist
         */
        const Entry<K, V>& next()
        {
            if (pos->left == pos)
            {
                pos = pos->right;
                return pos->data;
            }
            K tmpdata;
            K tmpdata1;
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();

            node *tmp1 = pos->right;
            node *tmptmp1;
            while (tmp1 != NULL)
            {
                tmptmp1 = tmp1;
                tmpdata = tmp1->data.key;
                tmp1 = tmp1->left;
            }

            node *tmp2 = pos->father;
            bool flagfather = false;
            while (tmp2 != NULL)
            {
                if (tmp2->data.key > pos->data.key)
                {
                    tmpdata1 = tmp2->data.key;
                    flagfather = true;
                    break;
                }
                else tmp2 = tmp2->father;
            }
            if (pos->right != NULL && flagfather == true)
            {
                if (tmpdata < tmpdata1)
                {
                    pos = tmptmp1;
                    return pos->data;
                }
                else
                {
                    pos = tmp2;
                    return pos->data;
                }
            }
            else if (pos->right != NULL)
            {
                pos = tmptmp1;
                return pos->data;
            }
            else
            {
                pos = tmp2;
                return pos->data;
            }
        }
    };

    class Iterator {
    public:
    TreeMap<K,V> *which;
    node *pos;
    node *prev;
    node *last;

    public:
        /**
         * Returns true if the iteration has more elements.
         * Amortized O(1).
         */
        bool hasNext()
        {
            if (pos->left == pos && pos->right != NULL)
            return true;
            if (pos->left == pos && pos->right == NULL)
            return false;
            node *tmp = which->root;
            //if (pos->right == tmp) return true;
            if (tmp == NULL) return false;
            while (tmp->right != NULL)
            tmp = tmp->right;
            K tmp1 = tmp->data.key;
            if (pos->data.key < tmp1) return true;
            else return false;
        }

        /**
         * Returns a reference to the next element in the iteration.
         * Amortized O(1).
         * @throw ElementNotExist
         */
        Entry<K, V>& next()
        {
            if (pos->left == pos)
            {
                last = pos;
                pos = pos->right;
                return pos->data;
            }
            K tmpdata;
            K tmpdata1;
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();

            node *tmp1 = pos->right;
            node *tmptmp1;
            while (tmp1 != NULL)
            {
                tmptmp1 = tmp1;
                tmpdata = tmp1->data.key;
                tmp1 = tmp1->left;
            }

            node *tmp2 = pos->father;
            bool flagfather = false;
            while (tmp2 != NULL)
            {
                if (tmp2->data.key > pos->data.key)
                {
                    tmpdata1 = tmp2->data.key;
                    flagfather = true;
                    break;
                }
                else tmp2 = tmp2->father;
            }
            if (pos->right != NULL && flagfather == true)
            {
                if (tmpdata < tmpdata1)
                {
                    last = pos;
                    pos = tmptmp1;
                    return pos->data;
                }
                else
                {
                    last = pos;
                    pos = tmp2;
                    return pos->data;
                }
            }
            else if (pos->right != NULL)
            {
                last = pos;
                pos = tmptmp1;
                return pos->data;
            }
            else
            {
                last = pos;
                pos = tmp2;
                return pos->data;
            }
        }

        /**
         * Removes from the underlying collection the last element
         * returned by the iterator
         * Amortized O(1).
         * @throw ElementNotExist
         */
        void remove()
        {
            if (last == NULL) throw ElementNotExist();
            which->remove(pos->data.key);
            pos = last;
            last = NULL;
        }
    };
    void remove1(node *&t)
    {
        node *tmp = t;
        if (tmp->right != NULL) remove1(tmp->right);
        if (tmp->left != NULL) remove1(tmp->left);
        delete tmp;
    }

    /**
     * Constructs an empty map
     */
    TreeMap()
    {
        srand(time(0));
        root = NULL;
        size1 = 0;
    }

    /**
     * Copy constructor
     */
    TreeMap(const TreeMap &c)
    {
        root=NULL;
        size1=0;
        addAll(*this,c);
    }

    /**
     * Destructor
     */

    ~TreeMap()
    {
        remove1(root);
        size1 = 0;
    }

    /**
     * Assignment operator
     */
    TreeMap& operator=(const TreeMap &c)
    {
        size1=0;
        clear();
        root=NULL;
        addAll(*this,c);
        return *this;
    }

    /**
     * Constructs a new tree map containing the same mappings as the
     * given map
     */
    template <class C>
    TreeMap(const C& c)
    {
        size1 = 0;
        root=NULL;
        addALL(*this,c);
    }

    /**
     * Returns an iterator over the elements in this map.
     * O(1).
     */
    Iterator iterator()
    {
        Iterator *a= new Iterator;
        a->which = this;
        node *tmp = root;
        while (tmp->left != NULL)
        tmp = tmp->left;
        //a->pos = tmp;

        K k;
        V v;
        Entry<K,V> t(k,v);
        a->prev = new node(t);
        a->prev->right = tmp;
        a->prev->left = a->prev;
        a->last = NULL;
        a->pos = a->prev;
        //a->pos = root;
        return *a;
    }

    /**
     * Returns an const iterator over the elements in this map.
     * O(1).
     */
    ConstIterator constIterator() const
    {
        ConstIterator *a=new ConstIterator;
        a->which = this;
        //a->pos = root;
        node *tmp = root;
        while (tmp->left != NULL)
        tmp = tmp->left;
        //a->pos = tmp;

        K k;
        V v;
        Entry<K,V> t(k,v);
        a->prev = new node(t);
        a->prev->left = a->prev;
        a->prev->right = tmp;
        a->pos = a->prev;
        return *a;
    }

    void LL(node *&p)
    {
        node *father = p->father;
        node *tmp = p;
        node *child = p->left;

        child->father = father;
        if (child->right != NULL)
        child->right->father = tmp;
        tmp->father = child;

        tmp->left = child->right;
        child->right = tmp;

        tmp = child;
        p = child;
        if (father != NULL)
        {
            if (p->data.key < father->data.key) father->left = p;
            else father->right = p;
        }
    }

    void RR(node *&p)
    {
        node *tmp = p;
        node *father = p->father;
        node *child = p->right;

        child->father = father;
        tmp->father = child;
        if (child->left != NULL) child->left->father = tmp;


        tmp->right = child->left;
        child->left = tmp;

        p = child;
        if (father != NULL)
        {
            if (p->data.key < father->data.key) father->left = p;
            else father->right = p;

        }
    }

    /**
     * Removes all of the mappings from this map.
     * O(n).
     */
    void clear()
    {
        remove1(root);
        root = NULL;
        size1 = 0;
    }

    /**
     * Returns true if this map contains a mapping for the specified key.
     * O(logn).
     */
    bool containsKey(const K& e) const
    {
        node *tmp = root;
        while (tmp != NULL)
        {
            if (e < tmp->data.key) tmp = tmp->left;
            else if (e > tmp->data.key) tmp = tmp->right;
            else return true;
        }
        return false;
    }

    /**
     * Returns true if this map contains a mapping for the specified value.
     * O(n).
     */
    /*bool containsvalue1(const V& v,node *&p)
    {
        node *tmp = p;
        if (p == NULL) return false;
        if (v < tmp->data.value )
        containsvalue1(v,tmp->left);
        else if(v > tmp->data.value)
        containsvalue1(v,tmp->right);
        else if (v == tmp->data.value)
        return true;
    }*/



    bool containsvalue1 (const V& v,node *p) const
    {
        bool flag = false;

        if (p == NULL) {}
        if (p->data.value == v) flag = true;
        else
        {

            if (p->right != NULL) containsvalue1(v,p->right);
            else if (p->left != NULL) containsvalue1(v,p->left);
        }
        if (flag == true) return true;
        else return false;
    }


    bool containsValue(const V& v) const
    {

        return containsvalue1(v,root);
    }

    /**
     * Returns a key-value mapping associated with the least key in
     * this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const Entry<K, V>& firstEntry() const
    {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->left != NULL) tmp = tmp->left;
        return tmp->data;
    }

    /**
     * Returns the first (lowest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& firstKey() const
    {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->left != NULL) tmp = tmp->left;
        return tmp->data.key;
    }

    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    V& get(const K& k)
    {
        node *tmp = root;
        while (tmp->data.key != k)
        {
            if (k < tmp->data.key) tmp = tmp->left;
            else if(k > tmp->data.key) tmp = tmp->right;
        }
        return tmp->data.value;
    }

    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    const V& get(const K& k) const
    {
        node *tmp = root;
        while (tmp->data.key != k)
        {
            if (k < tmp->data.key) tmp = tmp->left;
            else if(k > tmp->data.key) tmp = tmp->right;
        }
        return tmp->data.value;
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const Entry<K, V>& lastEntry() const
    {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->right != NULL) tmp = tmp->right;
        return tmp->data;
    }

    /**
     * Returns the last (highest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& lastKey() const
    {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->right != NULL) tmp = tmp->right;
        return tmp->data.key;
    }

    /**
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the
     * default-constructor.
     * O(logn).
     */
    void add(const K& k, const V& v,node *&p)
    {
        if (p == NULL) return ;
        if (p->data.key < k)
        {
            if (p->right == NULL)
            {
                Entry<K,V> t(k,v);
                p->right = new node(t,p);
                //p->right->data.key = k;
                //p->right->data.value = v;
                //p->right->father = p;
            }

            else add( k,v, p->right);
            if (p->right->rand1 < p->rand1) RR(p);
        }
        else
        {
            if (p->left == NULL)
            {
                Entry<K,V> t(k,v);
                p->left = new node(t,p);
                //p->left->data.key = k;
                //p->left->data.value = v;
                //p->left->father = p;

            }
            else add(k,v , p->left);
            if (p->left->rand1 < p->rand1) LL(p);
        }
    }


    V put(const K& k, const V& v)
    {
        node *tmp = root;
        while (tmp != NULL&&tmp->data.key != k )
        {
            if (k < tmp->data.key) tmp = tmp->left;
            else tmp = tmp->right;
        }
        if (tmp != NULL)
        {
            V tmptmp = tmp->data.value;
            tmp->data.value = v;
            return tmptmp;
        }
        else if (tmp == NULL)
        {
            if (root == NULL)
            {
                Entry<K,V> t(k,v);
                root = new node(t);
            }
            else add(k,v,root);
            V v1 = v;
            ++size1;
            return v1;

        }
    }

    /**
     * Removes the mapping for this key from this TreeMap if present.
     * O(logn).
     * @throw ElementNotExist
     */
    bool remove(node *&p)
    {
        if (p->left != NULL && p->right != NULL)
        {
            if (p->left->rand1 < p->right->rand1)
            {
                LL(p);
                remove(p->right);
            }
            else
            {
                RR(p);
                remove(p->left);
            }
        }
        else if(p->right != NULL && p->left == NULL)
        {
            RR(p);
            remove(p->left);
        }
        else if (p->left != NULL && p->right == NULL)
        {
            LL(p);
            remove(p->right);
        }
        else
        {
            --size1;
            if (p->father == NULL)
            {
                delete p;
                p = NULL;
            }
            else
            {
                if (p->father->left == p)
                {
                    p->father->left = NULL;
                    delete p;
                }
                else
                {
                    p->father->right = NULL;
                    delete p;
                }
            }
            return true;
        }
    }
bool remove(node *& k , const K& e)
{
     if( k == NULL) return false;
     if( k->data.key == e)
     {
         remove(k);
         return true;
     }
     if( e <  (k->data.key))
     return remove(k->left, e);
     else
     return remove(k->right,e);
}

    V remove(const K& k)
    {
        node *tmp = root;

        while (k != tmp->data.key && tmp!= NULL)
        {
            if (k < tmp->data.key) tmp = tmp->left;
            else tmp = tmp->right;
        }
        if (tmp == NULL) throw ElementNotExist();
        else
        {
            V v1 = tmp->data.value;
            bool flag = remove(root,k);
            return v1;
        }
    }

    /**
     * Returns the number of key-value mappings in this map.
     * O(logn).
     */
    int size() const
    {
        return size1;
    }


    void add(const Entry<K, V>& entry,node *&p)
    {
        Entry<K,V> e = entry;
        if (p == NULL) return ;
        if (p->data.key < e.key)
        {
            if (p->right == NULL) p->right = new node(e,p);
            else add(e , p->right);
            if (p->right->rand1 < p->rand1) RR(p);
        }
        else
        {
            if (p->left == NULL) p->left = new node(e,p);
            else add(e , p->left);
            if (p->left->rand1 < p->rand1) LL(p);
        }
    }

    bool add(const Entry<K, V>& entry)
    {
        //if (contains(e)) return false;
        Entry<K,V> tmp=entry;
        if (root == NULL)
        {
            root = new node(tmp);
            //root->data = tmp;
            root->father = root->left = root->right = NULL;
            root->rand1 = rand();
        }
        else add(tmp ,root);
        ++size1;
        return true;
    }
};

#endif

