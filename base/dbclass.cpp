#include "dbclass.h"

DBClass::DBClass(mongocxx::database *_db)
    :mDB (_db)
{

}

DBClass::DBClass(const DBClass &dbclass)
    :mDB(dbclass.mDB)
{

}

mongocxx::database *DBClass::db()
{
    return mDB;
}
