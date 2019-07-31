#ifndef DBCLASS_H
#define DBCLASS_H


class DBClass : public mongocxx::database
{
public:
    DBClass();
};

#endif // DBCLASS_H
