#pragma once
#include <atomic>
#include <memory>

namespace util
{

/* Wrapper for std::shared_ptr<T> with enforced single use */
template <typename T>
class consumable
{
public:
    explicit consumable(std::shared_ptr<T>&& val);

    consumable(const consumable&) = default;
    consumable(consumable&&) = default;

    consumable& operator=(const consumable&) = default;
    consumable& operator=(consumable&&) = default;

    T* operator->() { return m_value.get(); }

    [[nodiscard]] T&& consume();

private:
    std::shared_ptr<T> m_value;
    std::shared_ptr<std::atomic<bool>> m_isConsumed = std::make_shared<std::atomic<bool>>(false);
};

// #################################################################

template <typename T, typename... Args>
consumable<T> make_consumable(Args&&... args)
{
    return consumable<T>(std::make_shared<T>(std::forward<Args>(args)...));
}

// #################################################################

class EmptyConsumableError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

// #################################################################

template <typename T>
consumable<T>::consumable(std::shared_ptr<T>&& val)
    : m_value(std::move(val)) { }

template <typename T>
T&& consumable<T>::consume()
{
    if (m_isConsumed->exchange(true))
        throw EmptyConsumableError("Consumable already consumed");

    return std::move(*m_value);
}

}
