#pragma once

#include <typeinfo>
#include <type_traits>
#include <memory>
#include <stdexcept>

namespace stl
{
    class AnyHolderBase
    {
        public:
            virtual ~AnyHolderBase() = default;
            virtual std::unique_ptr<AnyHolderBase> clone() const = 0;

            virtual const std::type_info& type() const noexcept = 0;
    };

    template <typename T>
    class AnyHolder : public AnyHolderBase
    {
        public:
            explicit AnyHolder(const T& value) : value_(value) {}
            explicit AnyHolder(T&& value) : value_(std::move(value)) {}

            std::unique_ptr<AnyHolderBase> clone() const override
            {
                return std::make_unique<AnyHolder<T>>(value_);
            }

            const std::type_info& type() const noexcept override
            {
                return typeid(T);
            }
            
            T value_;
    };

    class Any
    {
        public:
            Any() noexcept : holder_(nullptr) {}

            Any(const Any& other) : holder_(other.holder_ ? other.holder_->clone() : nullptr) {}

            Any(Any&& other) noexcept : holder_(std::move(other.holder_)) {}

            template <typename T>
            Any(T&& value) : holder_(std::make_unique<AnyHolder<std::decay_t<T>>>(std::forward<T>(value))) {}

            ~Any() = default;

            Any& operator=(const Any& other)
            {
                if (this != &other)
                {
                    holder_ = other.holder_ ? other.holder_->clone() : nullptr;
                }

                return *this;
            }

            Any& operator=(Any&& other) noexcept
            {
                if (this != &other)
                {
                    holder_ = std::move(other.holder_);
                    other.holder_ = nullptr;
                }

                return *this;
            }

            template <typename T>
            Any& operator=(T&& value)
            {
                holder_ = std::make_unique<AnyHolder<std::decay_t<T>>>(std::forward<T>(value));

                return *this;
            }

            bool HasValue() const noexcept
            {
                return holder_ != nullptr;
            }

            void reset() noexcept
            {
                holder_.reset();
            }

            void swap(Any& other) noexcept
            {
                holder_.swap(other.holder_);
            }

            const std::type_info& type() const noexcept
            {
                return holder_ ? holder_->type() : typeid(void);
            }

            template <typename T>
            friend T AnyCast(const Any& operand);

            template <typename T>
            friend T AnyCast(Any& operand);

            template <typename T>
            friend const T AnyCast(Any&& operand);
            
            private:
                std::unique_ptr<AnyHolderBase> holder_;
    };

    template <typename T>
    T AnyCast(const Any& operand)
    {
        auto* holder = dynamic_cast<const AnyHolder<T>*>(operand.holder_.get());

        if (nullptr == operand.holder_ || nullptr == holder)
        {
            throw std::bad_cast();
        }

        return holder->value_;
    }

    template <typename T>
    T AnyCast(Any& operand)
    {
        auto* holder = dynamic_cast<AnyHolder<T>*>(operand.holder_.get());
        
        if (nullptr == operand.holder_ || nullptr == holder)
        {
            throw std::bad_cast();
        }

        return holder->value_;
    }

    template <typename T>
    T AnyCast(Any&& operand)
    {
        auto* holder = dynamic_cast<AnyHolder<T>*>(operand.holder_.get());
        
        if (nullptr == operand.holder_ || nullptr == holder)
        {
            throw std::bad_cast();
        }

        return std::move(holder->value_);
    }
}