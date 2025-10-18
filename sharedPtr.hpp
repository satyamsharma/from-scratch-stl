#include <iostream>

namespace stl
{
    template <typename T>
    class SharedPtr
    {
        public:
            SharedPtr(T* input) : data{input}, refCount{new int{0}}
            {}

            SharedPtr(SharedPtr& sharedPtr)
            {
                data = sharedPtr.data;
                *sharedPtr.refCount++;
                refCount = sharedPtr.refCount;
            }

            SharedPtr(SharedPtr&& sharedPtr)
            {
                data = sharedPtr.data;
                refCount = sharedPtr.refCount;


                sharedPtr.data = nullptr;
                sharedPtr.refCount = nullptr;
            }

            SharedPtr& operator=(SharedPtr& sharedPtr)
            {
                data = sharedPtr.data;
                *sharedPtr.refCount++;
                refCount = sharedPtr.refCount;

                return *this;
            }

            SharedPtr& operator=(SharedPtr&& sharedPtr)
            {
                data = sharedPtr.data;
                refCount = sharedPtr.refCount;


                sharedPtr.data = nullptr;
                sharedPtr.refCount = nullptr;

                return *this;
            }

            ~SharedPtr()
            {
                delete refCount;
                delete data;
                refCount = nullptr;
                data = nullptr;
            }
        private:
            int* refCount{nullptr};
            T* data{nullptr};
    };
}