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
    consumable(T val);
    consumable(const consumable&) = default;
    consumable(consumable&&) = default;

    [[nodiscard]] T&& consume();

private:
    struct State
    {
        explicit State(T&& v) : value(std::move(v)) {}

        T value;
        std::atomic<bool> consumed = false;
    };

    std::shared_ptr<State> m_state;
};

// #################################################################

class EmptyConsumableError final : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

// #################################################################

template <typename T>
consumable<T>::consumable(T val)
    : m_state(std::make_shared<State>(std::move(val))) { }

template <typename T>
T&& consumable<T>::consume()
{
    if (m_state->consumed.exchange(true))
        throw EmptyConsumableError("Consumable already consumed");

    return std::move(m_state->value);
}

}
