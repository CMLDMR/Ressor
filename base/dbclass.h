#ifndef DBCLASS_H
#define DBCLASS_H

#include "mongoheaders.h"
#include <boost/optional.hpp>

class DBClass
{
public:
    explicit DBClass(mongocxx::database* _db);
    DBClass( const DBClass &dbclass);


    mongocxx::database* db();


private:
    mongocxx::database* mDB;
};

#endif // DBCLASS_H
