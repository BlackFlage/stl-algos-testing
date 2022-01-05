//
// Created by BlackFlage on 05.01.2022.
//

#ifndef STL_ALGOS_LINKEDLIST_H
#define STL_ALGOS_LINKEDLIST_H

class empty_list_exception : public std::runtime_error
{
public:
    empty_list_exception(const char* message) : std::runtime_error(message) {}
};

template<typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        Node() = default;
        ~Node()
        {
            delete m_next;
        }
    public:
        T     m_value;
        Node* m_next;
        Node* m_prev;
    };

public:
    LinkedList()
    {
        m_head = nullptr;
        m_size = 0;
    }

    ~LinkedList()
    {
        delete m_head;
    }

    void append(const T& value)
    {
        if (!m_head)
        {
            m_head = new Node();
            m_head->m_value = value;
            m_head->m_next = nullptr;
            m_head->m_prev = nullptr;
            m_size++;
        }
        else
            append(&m_head, value);
    }

    size_t size() const
    {
        return m_size;
    }

    void add_first(const T& value)
    {
        if(!m_head)
        {
            append(value);
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

    T& get(size_t index)
    {
        if(!m_head)
        {
            throw empty_list_exception("List is empty!");
        }

        try
        {
            return get(index, m_head, 0);
        }
        catch(const std::out_of_range& exception)
        {
            throw;
        }
    }
private:
    void append(Node** node, const T& value)
    {
        if((*node)->m_next != nullptr)
        {
            append(&((*node)->m_next), value);
            return;
        }

        Node* new_node = new Node();

        new_node->m_value = value;
        new_node->m_prev  = *node;
        new_node->m_next  = nullptr;
        (*node)->m_next   = new_node;
        m_size++;
    }

    T& get(size_t index, Node* node, size_t current_index)
    {
        if(!node)
        {
            throw std::out_of_range("Index out of range!");
        }

        if(index == current_index)
            return node->m_value;
        else
            return get(index, node->m_next, current_index + 1);
    }

    Node*  m_head;
    size_t m_size;
};

#endif //STL_ALGOS_LINKEDLIST_H
