#ifndef ITEMBASE_H
#define ITEMBASE_H

#include "dbclass.h"
#include <QStringList>


class ItemBase : public DBClass
{
public:
    explicit ItemBase(mongocxx::database* _db, const std::string &collection);
    ItemBase(mongocxx::database* _db , const std::string &collection , bsoncxx::document::view &_view);

//    virtual ~ItemBase();


    template<typename T>
    bool addElement( const std::string &key , const T &value ){
        return this->setElement(key,value);
    }

    bool addElement( const std::string &key , const QString &value ){
        return this->setElement(key,value.toStdString());
    }

    boost::optional<bsoncxx::types::value> Element( const std::string &key);

    bool isValid() const;

    bsoncxx::oid oid() const;

    boost::optional<document> filter();


    QStringList keyList();

    bsoncxx::document::view view();


    bool deleteItem();


private:

    document doc;

    std::string collectionName;

    bool mIsValid;

    bsoncxx::oid mOid;

    template<typename T>
    bool setElement( const std::string &key , const T& value )
    {
        bool succed = true;

        auto f = this->doc.view().find(key);
        if( *f ){

            auto doc = document{};



            for( auto _f : this->doc.view() )
            {
                if( key != _f.key() )
                {
                    try {
                        doc.append(kvp(_f.key(),_f.get_value()));
                    } catch (bsoncxx::exception &e) {
                        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                        succed = false;
                    }
                }
            }

            if( succed ){

                this->doc.clear();

                for( auto _f : doc.view() )
                {
                    try {
                        doc.append(kvp(_f.key(),_f.get_value()));
                    } catch (bsoncxx::exception &e) {
                        std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                        succed = false;
                    }
                }

                try {
                    doc.append(kvp(key,value));
                } catch (bsoncxx::exception &e) {
                    std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                    succed = false;
                }
            }


        }else{
            try {
                doc.append(kvp(key,value));
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                succed = false;
            }
        }


        if( succed )
        {
            auto filter = document{};

            try {
                filter.append(kvp("_id",mOid));
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                succed = false;
            }

            auto setDoc = document{};

            try {
                setDoc.append(kvp("$set",this->doc.view()));
            } catch (bsoncxx::exception &e) {
                std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                succed = false;
            }


            if( succed ){
                try {
                    auto upt = this->db()->collection(collectionName).update_one(filter.view(),setDoc.view());
                    if( upt )
                    {
                        if( upt.value().modified_count() )
                        {

                        }else{
                            succed = false;
                        }
                    }else{
                        succed = false;
                    }
                } catch (mongocxx::exception &e) {
                    std::cout << "ERROR: " << __LINE__ << " " << __FUNCTION__ << " " << e.what() << std::endl;
                    succed = false;
                }
            }

        }
        return succed;
    }

};

#endif // ITEMBASE_H
