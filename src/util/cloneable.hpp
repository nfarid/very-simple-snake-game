
#ifndef HPP_CLONEABLE_ENUM_
#define HPP_CLONEABLE_ENUM_

#include "./core.hpp"

#include <memory>


namespace Util
{


/*
 * The Cloneable class
 * A simple class for covariant polymorphic cloning
 * Just inherit the class and override the clone_impl method
 * Also one can "override"/replace the public non-virtual clone method to return unique_ptr<MyClass>
 */
class Cloneable {
public:
    virtual ~Cloneable();    // = default
    Cloneable& operator=(Cloneable&&) = delete;    // no copy nor move

    std::unique_ptr<Cloneable> clone() const {
        return std::unique_ptr<Cloneable>{clone_impl()};
    }

private:
    virtual DumbPtr<Cloneable> clone_impl() const = 0;
};


}// namespace Utl

#endif    // HPP_CLONEABLE_ENUM_
