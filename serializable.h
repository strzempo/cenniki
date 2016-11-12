#ifndef OBJECT_H
#define OBJECT_H

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "qstring_serialization.h"

class Serializable
{
public:
    Serializable();
    virtual ~Serializable()=0;

    void save(const char *fileName);
    static Serializable* load(const char *fileName);

protected:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_NVP(i);
    }
    int i;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Serializable)

#endif // OBJECT_H
