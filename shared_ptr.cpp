#include <iostream>
/*智能指针基本都会用到所谓的"资源分配即初始化",也就是effective c++中提过的raii机制,
 *资源的释放一般是个棘手的问题,通过对象自动调用析构函数的特点,我们用析构函数实现资源的释放
 *
 *shared_smart_ptr通过共享引用计数实现资源管理,当shared_smart_ptr对象指向的引用计数为0时,析构函数就会释放对象管理的资源
 *                                
 */
template <typename Type>
class shared_smart_ptr final
{

public:
    //默认构造函数
    shared_smart_ptr()noexcept
    :pointer(nullptr),refer_counter(nullptr)
    {

    }
    //带参数的构造函数
    shared_smart_ptr(const Type * ptr)noexcept
    :pointer(ptr),refer_counter(nullptr)
    {
        this->add_refer();
    }
    //拷贝构造函数
    shared_smart_ptr(const shared_smart_ptr<Type> & other)noexcept
    :pointer(other.pointer),refer_counter(other.refer_counter)
    {
        other.add_refer();
    }
    //析构函数    
    ~shared_smart_ptr()noexcept{
        if ( *(this->refer_counter) == 0) {
            delete this->pointer;
            delete this->refer_counter;
        }
    }
    //重载赋值运算符
    shared_smart_ptr<Type> operator =(const shared_smart_ptr<Type> & other) const noexcept{
        if (*this != other){
            this->dec_refer();
            other.add_refer();
            this->pointer = other.pointer;
            this->refer_counter = other.refer_counter;
        }
    }
    //重载判等运算符
    bool operator ==(const shared_smart_ptr<Type> & other) const noexcept{
        return this->pointer == other.pointer;
    }
    //重载不等运算符
    bool operator !=(const shared_smart_ptr<Type> & other) const noexcept{
        return !(this->pointer == other.pointer);
    }
    //重载*
    Type operator *() const noexcept{
        return *this;
    }
    //重载->
    Type* operator ->() const noexcept{
        return this->pointer;
    }

private:
    //对象管理的资源
    Type *pointer;
    //对象间需要共享的引用计数
    std::size_t *refer_counter;
    //引用计数加1
    void add_refer() noexcept(false){
        (refer_counter != nullptr) 
        ? (*refer_counter)++
        : refer_counter = new int(1);
    }
    //引用计数减1
    void dec_refer()noexcept{
    
        if (refer_counter != nullptr){
            if (*refer_counter == 0){
                delete refer_counter;
                delete pointer;
            } else {
                (*refer_counter)--;
            }
        }
                
    }

};

