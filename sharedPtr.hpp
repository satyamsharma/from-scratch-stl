namespace stl
{
    template <typename T>
    class SharedPtr
    {
        public:
            SharedPtr(T* input) : data{input}, refCount{new int{1}}
            {}

            SharedPtr(const SharedPtr& sharedPtr)
            {
                data = sharedPtr.data;
                (*sharedPtr.refCount)++;
                refCount = sharedPtr.refCount;
            }

            SharedPtr(SharedPtr&& sharedPtr) noexcept
            {
                data = sharedPtr.data;
                refCount = sharedPtr.refCount;

                sharedPtr.data = nullptr;
                sharedPtr.refCount = nullptr;
            }

            SharedPtr& operator=(const SharedPtr& sharedPtr)
            {
                if (this != &sharedPtr)
                {
                    if (refCount) (*refCount)--;

                    if (refCount && *refCount == 0)
                    {
                        delete refCount;
                        refCount = nullptr;

                        delete data;
                        data = nullptr;
                    }

                    data = sharedPtr.data;
                    (*sharedPtr.refCount)++;
                    refCount = sharedPtr.refCount;
                }

                return *this;
            }

            SharedPtr& operator=(SharedPtr&& sharedPtr) noexcept
            {
                if (this != &sharedPtr)
                {
                    if (refCount) (*refCount)--;

                    if (refCount && *refCount == 0)
                    {
                        delete refCount;
                        refCount = nullptr;

                        delete data;
                        data = nullptr;
                    }
                 
                    data = sharedPtr.data;
                    refCount = sharedPtr.refCount;

                    sharedPtr.data = nullptr;
                    sharedPtr.refCount = nullptr;
                }

                return *this;
            }

            ~SharedPtr()
            {
                if (refCount) (*refCount)--;
                
                if (refCount && *refCount == 0)
                {
                    delete refCount;
                    delete data;

                    refCount = nullptr;
                    data = nullptr;
                }
            }

        private:
            int* refCount{nullptr};
            T* data{nullptr};
    };
}