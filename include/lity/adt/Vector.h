/*===- lity/adt/Vector.h -------------------------------------------------===

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==----------------------------------------------------------------------===*/
#ifndef LITY_ADT_VECTOR_H
#define LITY_ADT_VECTOR_H

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <vector>

namespace lity{

/** \class Vector
 *  \brief Vector is a container with continuous memory
 */
template<class ElementType>
class Vector {
public:

    class iterator : public std::iterator<std::random_access_iterator_tag, ElementType>{
        ElementType *ptr;
    public:
        iterator(ElementType *x = nullptr):ptr(x) {}
        iterator(const ElementType &r):ptr(r.ptr) {}
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        iterator& operator++(int) {
            iterator t(*this);
            ++ptr;
            return t;
        }
        iterator& operator--() {
            --ptr;
            return *this;
        }
        iterator operator+(size_t i) {
            return iterator(ptr + i);
        }
        iterator operator-(size_t i) {
            return iterator(ptr - i);
        }
        size_t operator-(iterator i) {
            return ptr - i.ptr;
        }
        iterator& operator--(int) {
            iterator t(*this);
            --ptr;
            return t;
        }
        bool operator==(const iterator &r) const {
            return ptr == r.ptr;
        }
        bool operator!=(const iterator &r) const {
            return ptr != r.ptr;
        }
        ElementType& operator*() {
            return *ptr;
        }
    };

    class bad_alloc : public std::bad_alloc{
        int err;
    public:
        bad_alloc(int e):err(e){}
        const char* what() const throw(){
            std::string errStr("bad_alloc: ");
            errStr += strerror(err);
            return errStr.c_str();
        }
    };

    Vector();
    Vector(size_t n);
    Vector(size_t n, const ElementType &value);
    Vector(std::vector<ElementType> &stdVector);
    Vector(Vector &x);
    Vector(std::initializer_list<ElementType> ilist);

    ~Vector();

    Vector& operator=(const Vector &x);
    Vector& operator=(std::initializer_list<ElementType> ilist);

    iterator begin();
    iterator end();

    size_t size();
    size_t max_size();
    void resize(size_t n);
    void resize(size_t n, const ElementType &value);

    bool empty();
    size_t capacity();
    void reserve(size_t n);
    void shrink_to_fit();

    ElementType &operator[](size_t index);
    ElementType &at(size_t index);
    ElementType &front();
    ElementType &back();
    ElementType *data();

    void assign(iterator first, iterator last);
    void assign(std::vector<ElementType> &stdVector);
    void assign(size_t n, const ElementType &value);
    void assign(std::initializer_list<ElementType> ilist);
    void push_back(const ElementType &value);
    ElementType pop_back();

    iterator insert(iterator position, const ElementType &value);
    iterator insert(iterator position, size_t n, const ElementType &value);
    iterator insert(iterator position, std::vector<ElementType> &stdVector);
    iterator insert(iterator position, std::initializer_list<ElementType> ilist);
    void insert(size_t index, const ElementType &value);
    void insert(size_t index, size_t n, const ElementType &value);
    void insert(size_t index, std::vector<ElementType> &stdVector);
    void insert(size_t index, std::initializer_list<ElementType> ilist);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void erase(size_t position);
    void erase(size_t first, size_t last);

    void swap(Vector &x);
    void clear();

protected:
    virtual void grow_memory();

private:
    ElementType *dataArr;
    size_t elementSize;
    size_t allocatedSize;
};

#include "Bits/Vector.tcc"

}

#endif
