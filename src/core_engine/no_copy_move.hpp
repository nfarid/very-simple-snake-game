
#ifndef NO_COPY_MOVE_HPP_11
#define NO_COPY_MOVE_HPP_11

namespace Core {

class NoMove {
public:
    NoMove(NoMove&& rhs) = delete;
    NoMove& operator=(NoMove&& rhs) = delete;
protected:
    NoMove() = default;
    ~NoMove() = default;
    NoMove(const NoMove& rhs) = default;
    NoMove& operator=(const NoMove& rhs) = default;
};

class NoCopy {
public:
    NoCopy(const NoCopy& rhs) = delete;
    NoCopy& operator=(const NoCopy& rhs) = delete;
protected:
    NoCopy() = default;
    ~NoCopy() = default;
    NoCopy(NoCopy&& rhs) = default;
    NoCopy& operator=(NoCopy&& rhs) = default;
};

}
#endif //NO_COPY_MOVE_HPP_11
