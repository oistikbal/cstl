#pragma once

namespace cstl
{
template <typename T> class list
{
  private:
    struct node
    {
        T value;
        node *prev;
        node *next;

        node(const T &val) : value(val), prev(nullptr), next(nullptr)
        {
        }
        node(T &&val) : value(static_cast<T &&>(val)), prev(nullptr), next(nullptr)
        {
        }
    };

  public:
    constexpr list() noexcept = default;

    constexpr void push_back(const T &value)
    {
        node *new_node = new node(value);
        if (m_tail)
        {
            m_tail->next = node;
            new_node->prev = m_tail;
            m_tail = node;
        }
        else
        {
            m_head = m_tail = node;
        }
        ++m_size;
    }

    constexpr void push_back(T &&value)
    {
        node *new_node = new node(static_cast<T &&>(value));
        if (m_tail)
        {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        else
        {
            m_head = m_tail = new_node;
        }
        ++m_size;
    }

    constexpr void push_front(const T &value)
    {
        node *new_node = new node(value);
        if (m_head)
        {
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }
        else
        {
            m_head = m_tail = new_node;
        }
        ++m_size;
    }

    constexpr void push_front(T &&value)
    {
        node *new_node = new node(static_cast<T &&>(value));
        if (m_head)
        {
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }
        else
        {
            m_head = m_tail = new_node;
        }
        ++m_size;
    }

    constexpr void pop_back()
    {
        assert(m_tail && "cstl::list::pop_back, empty list");
        node *temp = m_tail;
        m_tail = m_tail->prev;
        if (m_tail)
            m_tail->next = nullptr;
        else
            m_head = nullptr;
        delete temp;
        --m_size;
    }

    constexpr void pop_front()
    {
        assert(m_head && "cstl::list::pop_front, empty list");
        node *temp = m_head;
        m_head = m_head->next;
        if (m_head)
            m_head->prev = nullptr;
        else
            m_tail = nullptr;
        delete temp;
        --m_size;
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return m_size == 0;
    }

    [[nodiscard]] constexpr size_t size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] constexpr T &front() noexcept
    {
        assert(m_head && "cstl::list::front, empty list");
        return m_head->value;
    }

    [[nodiscard]] constexpr const T &front() const noexcept
    {
        assert(m_head && "cstl::list::front, empty list");
        return m_head->value;
    }

    [[nodiscard]] constexpr T &back() noexcept
    {
        assert(m_tail && "cstl::list::back, empty list");
        return m_tail->value;
    }

    [[nodiscard]] constexpr const T &back() const noexcept
    {
        assert(m_tail && "cstl::list::back, empty list");
        return m_tail->value;
    }

  private:
    node *m_head = nullptr;
    node *m_tail = nullptr;
    size_t m_size = 0;
};
} // namespace cstl