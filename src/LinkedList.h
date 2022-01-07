//
// Created by BlackFlage on 05.01.2022.
//

#ifndef STL_ALGOS_LINKEDLIST_H
#define STL_ALGOS_LINKEDLIST_H

class empty_list_exception : public std::runtime_error
{
public:
    empty_list_exception() : std::runtime_error("List is empty.") {}
};

template<typename T>
class LinkedList
{
private:
    struct Node
    {
        Node()
        {
            m_next = nullptr;
            m_prev = nullptr;
        }

        Node(const Node& other)
        {
            m_value = other.m_value;

            if(other.m_next)
                m_next = new Node(*other.m_next);
            else
                m_next = nullptr;

            m_prev = nullptr;
        }

        T     m_value;
        Node* m_next;
        Node* m_prev;
    };

public:
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        explicit Iterator(Node* ptr) : m_ptr(ptr){}

        T& operator*()  const { return m_ptr->m_value; }
        T* operator->() const { return &(m_ptr->m_value); }

        Iterator& operator++() { m_ptr = m_ptr->m_next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr == rhs.m_ptr; }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }
    private:
        Node* m_ptr;
    };

    struct ConstIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        explicit ConstIterator(Node* ptr) : m_ptr(ptr) {}

        const T& operator*()  const { return m_ptr->m_value; }
        const T* operator->() const { return &(m_ptr->m_value); }

        ConstIterator& operator++() { m_ptr = m_ptr->m_next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) { return lhs.m_ptr == rhs.m_ptr; }
        friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) { return !(lhs == rhs); }
    private:
        Node* m_ptr;
    };

    struct ReverseIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        explicit ReverseIterator(Node* ptr) : m_ptr(ptr) {}

        const T& operator*()  const { return m_ptr->m_value; }
        const T* operator->() const { return &(m_ptr->m_value); }

        ReverseIterator& operator++() { m_ptr = m_ptr->m_prev; return *this; }
        ReverseIterator operator++(int) { ReverseIterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.m_ptr == rhs.m_ptr; }
        friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return !(lhs == rhs); }
    private:
        Node* m_ptr;
    };

public:
    LinkedList()
    {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    ~LinkedList()
    {
        clear();
    }

    LinkedList(const LinkedList& other)
    {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;

        *this = other;
    }

    LinkedList(LinkedList&& other) noexcept
    {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;

        *this = std::move(other);
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if(this->m_head == other.m_head)
            return *this;

        clear();

        if(other.m_head)
        {
            m_head = new Node();
            Node* this_current = m_head;
            Node* other_current = other.m_head;

            while(other_current)
            {
                this_current->m_value = other_current->m_value;

                if(other_current->m_next)
                {
                    this_current->m_next = new Node();
                    this_current->m_next->m_prev = this_current;
                }
                else
                {
                    this_current->m_next = nullptr;
                    m_tail = this_current;
                }
                this_current = this_current->m_next;
                other_current = other_current->m_next;
            }

            m_size = other.m_size;
        }

        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept
    {
        if(m_head == other.m_head)
            return *this;

        clear();

        m_head = std::exchange(other.m_head, nullptr);
        m_tail = std::exchange(other.m_tail, nullptr);
        m_size = other.m_size;
        other.m_size = 0;

        return *this;
    }

    Iterator      begin()  const { return Iterator(m_head); }
    Iterator      end()    const { return Iterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(m_head); }
    ConstIterator cend()   const { return ConstIterator(nullptr); }
    ReverseIterator rbegin() const { return ReverseIterator(m_tail); }
    ReverseIterator rend() const { return ReverseIterator(nullptr); }

    void add(const T& value)
    {
        add(value, m_size);
    }

    size_t size() const
    {
        return m_size;
    }

    void add(const T& value, size_t index)
    {
        if(index == 0)
            add_first(value);
        else if(index == m_size)
            add_last(value);
        else if(index > m_size)
            throw std::out_of_range("Index out of range.");
        else
            add(&m_head, value, 0, index);
    }

    void add_first(const T& value)
    {
        if(!m_head)
        {
            Node* head    = new Node();
            head->m_value = value;
            head->m_next  = nullptr;
            head->m_prev  = nullptr;
            m_head        = head;
            m_tail        = head;
            m_size++;

            return;
        }

        Node* new_node    = new Node();
        new_node->m_value = value;
        new_node->m_next  = m_head;
        new_node->m_prev  = nullptr;
        m_head->m_prev    = new_node;
        m_head            = new_node;
        m_size++;
    }

    void add_last(const T& value)
    {
        if(!m_head)
        {
            add_first(value);
            return;
        }

        Node* new_node    = new Node();
        new_node->m_value = value;
        new_node->m_next  = nullptr;
        new_node->m_prev  = m_tail;
        m_tail->m_next    = new_node;
        m_tail            = new_node;
        m_size++;
    }

    T remove_first()
    {
        if(m_size == 0)
            throw empty_list_exception();

        if(m_size == 1)
        {
            T value = m_head->m_value;
            delete m_head;

            m_head = nullptr;
            m_tail = nullptr;
            m_size--;

            return value;
        }

        T value        = m_head->m_value;
        Node* head     = m_head;
        m_head         = head->m_next;
        head->m_next   = nullptr;
        m_head->m_prev = nullptr;
        m_size--;

        delete head;

        return value;
    }

    T remove_last()
    {
        if(m_size == 0)
            throw empty_list_exception();

        if(m_size == 1)
            return remove_first();

        T value        = m_tail->m_value;
        Node* tail     = m_tail;
        m_tail         = tail->m_prev;
        tail->m_prev   = nullptr;
        m_tail->m_next = nullptr;
        m_size--;

        delete tail;

        return value;
    }

    T remove(size_t index)
    {
        if(index >= m_size)
            throw std::out_of_range("Index out of range");
        else if(index == 0)
            return remove_first();
        else if(index == m_size - 1)
            return remove_last();

        return remove(&m_head, 0, index);
    }

    T& get(size_t index)
    {
        if(!m_head)
            throw empty_list_exception();
        else if(index >= m_size)
            throw std::out_of_range("Index out of range.");

        try
        {
            return get(index, m_head, 0);
        }
        catch(const std::out_of_range& exception)
        {
            throw;
        }
    }

    T& get_first()
    {
        if(!m_head)
            throw empty_list_exception();
        else
            return m_head->m_value;
    }

    T& get_last()
    {
        if(!m_tail)
            throw empty_list_exception();
        else
            return m_tail->m_value;
    }

    Iterator find(const T& value)
    {
        auto it = begin();
        for(; it != end(); it++)
        {
            if(*it == value)
            {
                return it;
            }
        }

        return it;
    }

    size_t index_of(const T& value)
    {
        size_t index = 0;
        Node* current = m_head;
        while(current)
        {
            if(current->m_value == value)
                return index;

            current = current->m_next;
            index++;
        }

        return -1;
    }

    T* to_array()
    {
        T* arr = new T[m_size];

        size_t i = 0;
        for(auto it = begin(); it != end(); it++, i++)
        {
            arr[i] = (*it);
        }

        return arr;
    }

    T poll()
    {
        if(!m_head)
            throw empty_list_exception();

        T value = m_head->m_value;
        remove_first();

        return value;
    }

    void clear()
    {
        if(m_head)
        {
            Node* current = m_head;
            for(int i = 0; i < m_size; i++)
            {
                Node* temp = current->m_next;
                delete current;
                current = temp;
            }
        }

        m_size = 0;
        m_head = nullptr;
        m_tail = nullptr;
    }
private:
    void add(Node** node, const T& value, size_t current_index, size_t dest_index)
    {
        if(current_index != dest_index)
        {
            add(&((*node)->m_next), value, current_index + 1, dest_index);
            return;
        }

        Node* new_node          = new Node();
        new_node->m_value       = value;
        new_node->m_prev        = (*node)->m_prev;
        new_node->m_next        = *node;
        (*node)->m_prev->m_next = new_node;
        (*node)->m_next->m_prev = new_node;
        m_size++;
    }

    T& get(size_t index, Node* node, size_t current_index)
    {
        if(!node)
            throw std::out_of_range("Index out of range!");

        if(index == current_index)
            return node->m_value;
        else
            return get(index, node->m_next, current_index + 1);
    }

    T remove(Node** node, size_t current_index, size_t dest_index)
    {
        if(current_index != dest_index)
        {
            return remove(&((*node)->m_next), current_index + 1, dest_index);
        }

        T value                 = (*node)->m_value;
        Node* old               = (*node);
        (*node)                 = (*node)->m_next;
        (*node)->m_prev         = (*node)->m_prev->m_prev;
        (*node)->m_prev->m_next = (*node);
        m_size--;

        delete old;

        return value;
    }

    Node*  m_head;
    Node*  m_tail;
    size_t m_size;
};

#endif //STL_ALGOS_LINKEDLIST_H
