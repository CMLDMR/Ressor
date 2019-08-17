#ifndef STOKDEPOMODEL_H
#define STOKDEPOMODEL_H


#include "stokdepo.h"

#include "base/itembasemodel.h"



class StokDepoModel : public ItemBaseModel<StokDepo::StokDepo>
{
public:
    StokDepoModel(mongocxx::database* _db);
};



#endif // STOKDEPOMODEL_H
