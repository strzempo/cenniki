#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "qarchive/qarchive.hpp"

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>

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
