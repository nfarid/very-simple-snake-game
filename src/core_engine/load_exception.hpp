
#ifndef LOAD_EXCEPTION_HPP_83
#define LOAD_EXCEPTION_HPP_83

#include <string>
#include <exception>
#include "../the_includes.hpp"

namespace Core {

class LoadException : public std::exception {
public:
    const char* what() const noexcept override{
        return messageM.c_str();
    }

    explicit LoadException(const char* msg_) :
        messageM{msg_} {
    }

private:
    const std::string messageM;
};

}

#endif //LOAD_EXCEPTION_HPP-83
