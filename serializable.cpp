#include "serializable.h"
#include <fstream>

BOOST_CLASS_EXPORT_IMPLEMENT(Serializable)

Serializable::Serializable()
{
}

Serializable::Serializable(const std::string &name)
{
    m_name = name;
}

const std::string& Serializable::name() const
{
    return m_name;
}

void Serializable::setName(const std::string &name)
{
    m_name = name;
}

void Serializable::save()
{
    std::ofstream ofs((m_name + ".xml").c_str());
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(this);
}

Serializable* Serializable::load(const std::string &fileName)
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
