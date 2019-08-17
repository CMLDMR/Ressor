#include "stokdepomodel.h"



StokDepoModel::StokDepoModel(mongocxx::database *_db)
    :ItemBaseModel<StokDepo::StokDepo> (_db)
{
    this->initModel();
}
