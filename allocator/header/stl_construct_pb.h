#include <new.h>

template <class T1, class T2>
inline void construct(T1 *p, const T2 &value){
    // 利用placement new;调用T1::T1(value);
    new (p) T1(value);
}

// destory的第一个版本,接收一个指针
template <class T>
inline void destory(T *pointer){
    pointer->~T(); // 调用dtor ~T
}

//destory的第二个版本,接收两个迭代器
template <class ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last){
    _destory(first, last, value_type(first));
}

template <class ForwardIterator, class T>
inline void _destory(ForwardIterator first, ForwardIterator last, T *){
    typedef typename _type_traits<T>::has_trivial_destructor trivial_destructor;
    _destory_aux(first, last, trivial_destructor());
}

template <class ForwardIterator>
inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _false_type){
    for(;first < last; ++first){
        destory(&*first);
    }
}

template <class ForwardIterator>
inline void _destory_aux(ForwardIterator, ForwardIterator, _true_type){}

inline void destroy(char *, char *){}

inline void destroy(wchar_t *, wchar_t *){}

