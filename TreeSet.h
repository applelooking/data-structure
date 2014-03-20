/** @file */

#ifndef __TREESET_H
#define __TREESET_H

#include "Utility.h"
#include <ctime>
#include <cstdlib>

//用的是最小堆，treap实现

/**
 * A set implemented by balanced tree,
 * the elements being putted must guarantee operator'<'
 *
 * The iterator must iterates in the order defined by the operator'<' (from the smallest to the biggest)
 */

template <class E>
class TreeSet
{
private:
    struct node
    {
        E data;
        node *left;
        node *right;
        node *father;
        int key;
        node ()
        {
            father = left = right = NULL;
            key = rand();
        }
        node (E &d,node *f = NULL,node *l = NULL,node *r = NULL):data(d),father(f),left(l),right(r)
        {
            key = rand();

        }
    };

    node *root;
public:
    int size1;
public:
    class ConstIterator
    {
    public:
        const TreeSet<E> *which;
        node *pos;
        node *prev;

    public:

        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
        bool hasNext()
        {
            if (pos->left == pos && pos->right != NULL) return true;
            if (pos->left == pos && pos->right == NULL) return false;
            node *tmp = which->root;
            //if (pos->right == tmp) return true;
            if (tmp==NULL) return false;
            while (tmp->right != NULL) tmp = tmp->right;
            E tmp1 = tmp->data;
            if (pos->data < tmp1) return true;
            else return false;
        }

        /**
         * Returns a const reference to the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next()
        {
            /*E tmpdata;
            E tmpdata1;
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();
            node *tmp1 = pos->right;
            node *tmptmp1;
            while (tmp1 != NULL)
            {
                tmptmp1 = tmp1;
                tmpdata = tmp1->data;
                tmp1 = tmp1->left;
            }

            node *tmp2 = pos->father;
            bool flagfather = false;
            while (tmp2 != NULL)
            {
                if (tmp2->data > pos->data)
                {
                    tmpdata1 = tmp2->data;
                    flagfather = true;
                    break;
                }
                else tmp2 = tmp2->father;
            }
            if (pos->right != NULL && flag == true)
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
            }*/
            if (pos->left == pos)
            {
                pos = pos->right;
                return pos->data;
            }
            E tmpdata;
            E tmpdata1;
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();

            node *tmp1 = pos->right;
            node *tmptmp1;
            while (tmp1 != NULL)
            {
                tmptmp1 = tmp1;
                tmpdata = tmp1->data;
                tmp1 = tmp1->left;
            }

            node *tmp2 = pos->father;
            bool flagfather = false;
            while (tmp2 != NULL)
            {
                if (pos->data < tmp2->data )
                {
                    tmpdata1 = tmp2->data;
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

    class Iterator
    {
    public:
        TreeSet<E> *which;
        node *pos;
        node *last;
        node *prev;


    public:
        /**
         * Returns true if the iteration has more elements.
         * O(logn)
         */
         /*Iterator()
         {
            last = NULL;
         }*/

        bool hasNext()
        {
            if (pos->left == pos && pos->right != NULL) return true;
            if (pos->left == pos && pos->right == NULL) return false;

            node *tmp = which->root;
            //if (pos->right == tmp) return true;
            if (tmp == NULL) return false;
            while (tmp->right != NULL) tmp = tmp->right;
            E tmp1 = tmp->data;
            if (pos->data < tmp1) return true;
            else return false;
        }

        /**
         * Returns a const reference the next element in the iteration.
         * O(logn)
         * @throw ElementNotExist
         */
        const E& next()
        {
            if (pos->left == pos)
            {
                last = pos;
                pos = pos->right;
                return pos->data;
            }

            E tmpdata;
            E tmpdata1;
            bool flag = hasNext();
            if (flag == false) throw ElementNotExist();
            node *tmp1 = pos->right;
            node *tmptmp1;
            while (tmp1 != NULL)
            {
                tmptmp1 = tmp1;
                tmpdata = tmp1->data;
                tmp1 = tmp1->left;
            }

            node *tmp2 = pos->father;
            bool flagfather = false;
            while (tmp2 != NULL)
            {
                if (pos->data < tmp2->data)
                {
                    tmpdata1 = tmp2->data;
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
                    //flagnext = true;
                    return pos->data;
                }
                else
                {
                    last = pos;
                    pos = tmp2;
                    //flagnext = true;
                    return pos->data;
                }
            }
            else if (pos->right != NULL)
            {
                last = pos;
                pos = tmptmp1;

                //flagnext = true;
                return pos->data;
            }
            else
            {
                last = pos;
                pos = tmp2;
                //flagnext = true;
                return pos->data;
            }
        }

        /**
         * Removes from the underlying collection the last element returned by the iterator (optional operation).
         * O(logn)
         * @throw ElementNotExist
         */
        void remove()
        {
            if (last == NULL) throw ElementNotExist();
            which->remove(pos->data);
            pos = last;
            last = NULL;
        }
    };

    /**
     * Constructs a new, empty tree set, sorted according to the natural ordering of its elements.
     */
    TreeSet()
    {
        srand(time(0));
        root = NULL;
        size1 = 0;
    }

    /**
     * Constructs a set containing the elements of the specified collection, in
     * the order they are returned by the collection's iterator.
     */
    template <class E2>
    explicit TreeSet(const E2& x)
    {
        size1 = 0;
        root=NULL;
        addALL(*this,x);
    }

    void remove1(node *&t)
    {
        node *tmp = t;
        if (tmp->right != NULL) remove1(tmp->right);
        if (tmp->left != NULL) remove1(tmp->left);
        delete tmp;
    }

    /**
     * Destructor
     */
    ~TreeSet()
    {
        remove1(root);
        size1 = 0;
    }

    /**
     * Assignment operator
     */
    TreeSet& operator=(const TreeSet& x)
    {
        size1=0;
        clear();
        root=NULL;
        addAll(*this,x);
        return *this;
    }

    /**
     * Copy-constructor
     */
    TreeSet(const TreeSet& x)
    {
        root=NULL;
        size1=0;
        addAll(*this,x);
    }

    /**
     * Returns an iterator over the elements in this set in proper sequence.
     */
    Iterator iterator()
    {
        Iterator *a= new Iterator;
        a->which = this;
        node *tmp = root;
        while (tmp->left != NULL)
        tmp = tmp->left;
        //a->pos = tmp;

        a->prev = new node;
        a->prev->right = tmp;
        a->prev->left = a->prev;
        a->last = NULL;
        a->pos = a->prev;
        //a->pos = root;
        return *a;
    }

    /**
     * Returns an CONST iterator over the elements in this set in proper sequence.
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

        a->prev = new node;
        a->prev->left = a->prev;
        a->prev->right = tmp;
        a->pos = a->prev;
        return *a;
    }

    void LL(node *&p)
    {
        //if (root == p)
        //root = p->left;

        node *father = p->father;
        //node *tmp = p;
        node *child = p->left;

        child->father = father;
        if (child->right != NULL)
        child->right->father = p;
        p->father = child;

        p->left = child->right;
        child->right = p;

        //p = child;
        p = child;
        if (father != NULL)
        {
            if (p->data < father->data) father->left = p;
            else father->right = p;
        }
    }

    void RR(node *&p)
    {
        //if (root == p)
        //root = p->right;

        //node *tmp = p;
        node *father = p->father;
        node *child = p->right;

        child->father = father;
        p->father = child;
        if (child->left != NULL) child->left->father = p;


        p->right = child->left;
        child->left = p;

        p = child;
        if (father != NULL)
        {
            if (p->data < father->data) father->left = p;
            else father->right = p;

        }
    }

    /**
     * Adds the specified element to this set if it is not already present.
     * Returns true if this set did not already contain the specified element.
     * O(logn)
     */
    void add(E &e,node *&p)
    {
        if (p == NULL) return ;
        if (p->data < e)
        {
            if (p->right == NULL) p->right = new node(e,p);
            else add(e , p->right);
            if (p->right->key < p->key) RR(p);
        }
        else
        {
            if (p->left == NULL) p->left = new node(e,p);
            else add(e , p->left);
            if (p->left->key < p->key) LL(p);
        }
    }
    bool add(const E& e)
    {
        //bool flag = false;
        /*node *tmp = root;
        node *tmp2 = root;
        while (tmp != NULL)
        {
            tmp2 = tmp;
            if (tmp->data < e) tmp = tmp->right;
            else if (tmp->data > e) tmp = tmp->left;
            else
            {
                flag = true;
                break;
            }
        }
        if (flag == true) return false;*/
        if (contains(e)) return false;
        E tmp=e;
        if (root == NULL) root = new node(tmp);
        else add(tmp ,root);
        ++size1;
        return true;
        /*E eee=e;
        node *father = tmp2;
        node *child = new node(eee,father);

        if (eee < father->data) father->left = child;
        else father->right = child;

        while (father->key > child->key)
        {
            if (child->data < father->data)
            {
                node *tmp = father->father;
                LL(father);
                child = father;
                father = tmp;
            }
            else
            {
                node *tmp = father->father;
                RR(father);
                child = father;
                father = tmp;
            }
        }
        ++size1;
        return true;*/
    }

    /**
     * Removes all of the elements from this set.
     */
    void clear()
    {
        remove1(root);
        root = NULL;
        size1 = 0;
    }

    /**
     * Returns true if this set contains the specified element.
     * O(logn)
     */
    bool contains(const E& e) const
    {
        node *tmp = root;
        while (tmp != NULL)
        {
            if (e < tmp->data) tmp = tmp->left;
            else if ( tmp->data < e) tmp = tmp->right;
            else return true;
        }
        return false;
    }

    /**
     * Returns a const reference to the first (lowest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& first() const
    {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->left != NULL) tmp = tmp->left;
        return tmp->data;
    }

    /**
     * Returns true if this set contains no elements.
     * O(1)
     */
    bool isEmpty() const
    {
        if (size == 0) return true;
        else return false;
    }

    /**
     * Returns a const reference to the last (highest) element currently in this set.
     * O(logn)
     * @throw ElementNotExist
     */
    const E& last() const
    {
        if (root == NULL) throw ElementNotExist();
        node *tmp = root;
        while (tmp->right != NULL) tmp = tmp->right;
        return tmp->data;
    }

    /**
     * Removes the specified element from this set if it is present.
     * O(logn)
     */
    bool remove(node *&p)
    {
        if (p->left != NULL && p->right != NULL)
        {
            if (p->left->key < p->right->key)
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
                    //node *tmp = p->father;
                    p->father->left = NULL;
                    delete p;
                    //tmp->left = NULL;
                }
                else
                {
                    //node *tmp = p->father;
                    p->father->right = NULL;
                    delete p;
                    //tmp->right = NULL;
                }
            }
            return true;
        }
    }


bool remove(node *& k , const E& e)
{
     if( k == NULL) return false;
     if( k->data == e)
     {
         remove(k);
         return true;
     }
     if( e <  (k->data))
     return remove(k->left, e);
     else
     return remove(k->right,e);
}


    bool remove(const E& e)
    {
        /*if (root->data = e)
        remove(root);
        else
        node *tmp = root;
        while (tmp != NULL && tmp->data != e)
        {
            if (e < tmp->data)
            tmp = tmp->left;
            else tmp = tmp->right;
        }
        if (tmp == NULL)
        return false;
        //node *&tmp1 = tmp;

        remove(tmp);*/
        node *tmp = root;
        while (tmp != NULL && tmp->data != e)
        {
            if (e < tmp->data)
            tmp = tmp->left;
            else tmp = tmp->right;
        }
        if (tmp == NULL)
        return false;

        remove(root,e);
    }

    /**
     * Returns the number of elements in this set (its cardinality).
     * O(1)
     */
    int size() const
    {
        return size1;
    }
};
#endif
