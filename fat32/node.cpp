#include "node.h"
#include <iostream>

using namespace std;

Node::Node(string name, unique_ptr<Stream>& s, const NodeType type, const long actual_size)
    : m_stream{std::move(s)}
    , m_name{std::move(name)}
    , m_path{std::move(name)}
    , m_actual_size{actual_size}
    , m_alloc_size{m_stream->size()}
    , m_type{type}
{
}

Node::~Node()
{
    for (auto e : m_children)
        delete e;
}

auto Node::set_path(const string& pwd) -> void
{
    m_path = pwd + "/" + m_name;
}

auto Node::add_child(Node* child) ->void
{
    m_children.push_back(child);
}

auto Node::is_expandable() const -> bool
{
    return is_dir() && m_name != "." && m_name != "..";
}

auto Node::to_s() -> string
{
    return format("name : {}, size: 0x{:X}",m_name, m_alloc_size);
}

auto Node::read_all() const -> core::io::byte_buffer
{
    const auto buf = new char[m_alloc_size];
    m_stream->read(buf, m_alloc_size);
    core::io::byte_buffer bb(reinterpret_cast<uint8_t*>(buf), static_cast<int>(m_alloc_size), true);

    return bb;
}

auto Node::export_to(const string& path) const -> bool
{
     ofstream ofs(path, ios::binary);
     if (!ofs.is_open())
         return false;

     char buf[0x1000] {};
     auto remained = m_actual_size;

     while (remained > 0)
     {
         const auto to_read = remained > 0x1000 ? 0x1000 : remained;
         const auto rd = m_stream->read(buf, to_read);
         ofs.write(buf, to_read);
         ofs.flush();

         remained -= rd;
     }

     return true;
}