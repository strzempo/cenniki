#ifdef QLIST_SERIALIZATION_H
#define QLIST_SERIALIZATION_H

#include <QList>
#include <list>
//#include <boost/archive/xml_iarchive.hpp>
//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/serialization/string.hpp>

#include <boost/config.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>

#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>

///\file document is based on "boost/serialization/list.hpp"

namespace boost {
    namespace serialization {

        //---------------------------------------------------------------------------
        /// Saves a QList object to a collection
        template<class Archive, class U >
        inline void save(Archive &ar, const QList< U > &t, const uint /* file_version */ )
        {
            //boost::serialization::stl::save_collection< Archive, QList<U> >(ar, t);
            ar << boost::serialization::make_nvp("QList", t.toStdList());
        }

        //---------------------------------------------------------------------------
        /// Loads a QList object from a collection
        template<class Archive, class U>
        inline void load(Archive &ar, QList<U > &t, const uint /* file_version */ )
        {
            std::list<U> list;
            ar >> list;
            t = QList<U>::fromStdList(list);
            /*
                boost::serialization::stl::load_collection<
                    Archive,
                    QList<U>,
                    boost::serialization::stl::archive_input_seq<Archive, QList<U> >,
                    boost::serialization::stl::no_reserve_imp< QList<U> > >(ar, t);

            item_version_type item_version(0);
                    ar >> BOOST_SERIALIZATION_NVP(item_version);

            collection_size_type count;
            ar >> BOOST_SERIALIZATION_NVP(count);
            boost::serialization::stl::collection_load_impl(ar, t, count, item_version);
*/
        }

        //---------------------------------------------------------------------------
        /// split non-intrusive serialization function member into separate
        /// non intrusive save/load member functions
        template<class Archive, class U >
        inline void serialize(Archive &ar, QList<U> &t, const uint file_version )
        {
            boost::serialization::split_free( ar, t, file_version);
        }

    } // namespace serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(QList)

#endif // QLIST_SERIALIZATION_H
