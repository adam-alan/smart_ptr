#include <iostream>

template <typename Type>
class shared_smart_ptr
{

public:
    shared_smart_ptr()noexcept
    :pointer(nullptr),refer_counter(nullptr)
    {

    }
    shared_smart_ptr(const Type * ptr)noexcept
    :pointer(ptr),refer_counter(nullptr)
    {
        this->add_refer();
    }

    shared_smart_ptr(const shared_smart_ptr<Type> & other)noexcept
    :pointer(other.pointer),refer_counter(other.refer_counter)
    {
        other.add_refer();
    }
    virtual ~shared_smart_ptr()noexcept{
        if ( *(this->refer_counter) == 0) {
            delete this->pointer;
        }
    }

    shared_smart_ptr<Type> operator =(const shared_smart_ptr<Type> & other) const noexcept{
        if (*this != other){
            this->dec_refer();
            other.add_refer();
            this->pointer = other.pointer;
            this->refer_counter = other.refer_counter;
        }
    }

    bool operator ==(const shared_smart_ptr<Type> & other) const noexcept{
        return this->pointer == other.pointer;
    }

    bool operator !=(const shared_smart_ptr<Type> & other) const noexcept{
        return !(this->pointer == other.pointer);
    }

    Type operator *() const noexcept{
        return *this;
    }
    Type* operator ->() const noexcept{
        return this->pointer;
    }

    

private:
    Type *pointer;
    std::size_t *refer_counter;

    void add_refer() noexcept(false){
        (refer_counter != nullptr) 
        ? (*refer_counter)++
        : refer_counter = new int(1);
    }

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

