#include "common.hpp"

#include <sstream>

template <typename TStream>
void
reopen(TStream& stream,
       const char *file_name,
       std::ios_base::openmode mode)
{
    stream.close();
    stream.clear();
    stream.open(file_name, mode);
}

template <typename... Args>
std::string stringify(Args&&... args) {
    std::ostringstream oss;
    (oss << ... << std::forward<Args>(args));
    return oss.str();
}
