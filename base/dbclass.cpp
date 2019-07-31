#include "dbclass.h"

DBClass::DBClass(mongocxx::database *_db)
    :mDB (_db)
{

}

mongocxx::database *DBClass::db()
{
    return mDB;
}
