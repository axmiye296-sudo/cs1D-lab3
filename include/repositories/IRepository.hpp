#ifndef I_REPOSITORY_HPP
#define I_REPOSITORY_HPP

#include "../V.hpp"

template<typename T>
class IRepository {
public:
    virtual ~IRepository() = default;
    
    // CRUD operations
    virtual bool save(T& entity) = 0;
    virtual bool load(int id, T& entity) = 0;
    virtual bool remove(int id) = 0;
    virtual V<T> findAll() = 0;
    
    // Transaction support
    virtual bool beginTransaction() = 0;
    virtual bool commitTransaction() = 0;
    virtual bool rollbackTransaction() = 0;
};

#endif