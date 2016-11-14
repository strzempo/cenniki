#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>
//#include <boost/serialization/deque.hpp>
//#include <boost/serialization/shared_ptr.hpp>

#include "qstring_serialization.h"
#include "qlist_serialization.h"

/*
in h:

protected:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_NVP(member);
    } 

in cpp;

BOOST_CLASS_EXPORT_IMPLEMENT(class)
*/
#endif
