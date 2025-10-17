template <typename T>
class UniquePtr
{
    public:
        explicit UniquePtr(T* inputPtr) : data{inputPtr} {}

        ~UniquePtr()
        {
            delete data;
        }

        UniquePtr(UniquePtr& uniquePtr) = delete;

        UniquePtr(UniquePtr&& uniquePtr)
        {
            data = uniquePtr.data;
            uniquePtr.data = nullptr;
        }

    private:
        T* data{nullptr};
};

