// file: 2jjalloc.h
#ifndef _JJALLOC_

#define _JJALLOC_


#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace JJ
{
    /* ptrdiff_t 
     * signed integer type of the result of subtracting two pointers   
    */
    // 
    template<class T>
    inline T* _allocate(ptrdiff_t size, T *){
        // ����new���������ڴ�ʧ��ʱ���õĺ���ָ��
        std::set_new_handler(nullptr);
        // ͨ��ȫ��new�����ڴ�
        T * tmp = (T *) (::operator new ((size_t)(size * sizeof(T))));
        if(tmp == 0){
            std::cerr<<"out of memory"<<std::endl;
            exit(1);
        }
        return tmp;
    }

    template <class T>
    inline void _deallocate(T *buffer){
        ::operator delete(buffer);
    }

    // 
    template <class T1, class T2>
    inline void _construct(T1 * p, const T2 & value){
        // palcement new --- new(p)
        // ��pָ���λ��newһ������,���������ֵΪvalue
        // ���캯�� --- ��T2��ֵͨ��T1�Ĺ��캯������T1�Ķ���
        new (p) T1(value); // 
    }

    //
    template <class T>
    inline void _destroy(T *ptr){
        ptr->~T();
    }

    template<class T>
    class allocator{
        // ������allocator�ı�Ҫ�ӿ�
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T *   const_pointer;
        typedef T &         reference;
        typedef const T &   const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

        // rebind allocator of type Up
        // һ��Ƕ�׵�class template
        // ��Ψһ�ĳ�Աother,����allocator<U>
        // ʵ��allocator��Ƕ��
        template <class U>
        struct rebind{
            typedef allocator<U> other;
        };

        // allocator�����ṩ�������ڴ�Ľӿ�
        pointer allocate(size_t n, const void * hint = 0){
            return _allocate((difference_type)n, (pointer)0);
        }

        // 
        void deallocate(pointer p, size_type n){_deallocate(p);}

        void construct(pointer p, const T & value){
            _construct(p, value);
        }

        // ���ö������������
        void destroy(pointer p){_destroy(p);}

        pointer address(reference x){ return (pointer) &x;}

        const_pointer cosnt_address(const_reference x){
            return (const_pointer)&x;
        }

        size_type max_size() const{
            return size_type(UINT_MAX / sizeof(T));
        }
    }; // end of class allocator
} // end of namespace JJ


#endif
