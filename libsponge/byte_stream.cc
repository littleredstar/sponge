#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) :_capacity(capacity),_rcnt(0),_wcnt(0),_EOF(false),_Q(){}

size_t ByteStream::write(const string &data) {
    size_t num=0;
    for (auto ch:data){
        if (_Q.size()==_capacity) break;
        ++_wcnt;
        _Q.push_back(ch);
        ++num;
    }
    return num;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return string().assign(_Q.begin(),min(_Q.end(),_Q.begin()+len));
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    for (size_t i=0;i<len&&_Q.size();++i){
        ++_rcnt;
        _Q.pop_front();
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string result=peek_output(len);
    pop_output(len);
    return result;
}

void ByteStream::end_input() { _EOF=true; }

bool ByteStream::input_ended() const { return _EOF; }

size_t ByteStream::buffer_size() const { return _Q.size(); }

bool ByteStream::buffer_empty() const { return _Q.empty(); }

bool ByteStream::eof() const { return buffer_empty()&&_EOF; }

size_t ByteStream::bytes_written() const { return _wcnt; }

size_t ByteStream::bytes_read() const { return _rcnt; }

size_t ByteStream::remaining_capacity() const { return _capacity-buffer_size(); }
