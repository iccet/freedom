#ifndef COMMON_HPP
#define COMMON_HPP
#include <QtGlobal>

#define NON_COPY_AND_MOVE_CLASS_DECL(Class) \
    Class() = default;\
    virtual ~Class() = default;\
    Q_DISABLE_COPY_MOVE(Class);

template <typename TStream>
void
reopen(TStream& /*stream*/,
       const char */*file_name*/,
       std::ios_base::openmode mode = std::ios_base::out);

template<typename ... Args>
std::string
stringify(Args&& ... /*args*/);

#endif // COMMON_HPP
