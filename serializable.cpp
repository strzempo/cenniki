#include "serializable.h"
#include <fstream>

BOOST_CLASS_EXPORT_IMPLEMENT(Serializable)

Serializable::Serializable()
{
    i = 1;
}

void Serializable::save(const char * fileName)
{
    std::ofstream ofs(fileName);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(this);
}

Serializable* Serializable::load(const char * fileName)
{
    Serializable* ob;
    std::ifstream ifs(fileName);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(ob);
    assert(ob);
    return ob;
}

Serializable::~Serializable(){}
