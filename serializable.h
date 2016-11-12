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

/*! Klasa abstrakcyjna reprezentująca obiekt.
 *
 * Wszystkie obiekty dynamiczne w projekcie dziedziczą z tej klasy. Każdy obiekt musi mieć nazwę.
 */
class Serializable
{
public:
    Serializable();
    explicit Serializable(const std::string& name);
    virtual ~Serializable()=0;

    /*!
     * \brief Funkcja zwraca nazwę obiektu
     * \return Stała referencja do std::string z nazwą obiektu
     */
    const std::string& name() const;

    /*!
     * \brief Ustawiacz nazwy obiektu
     */
    void setName(const std::string& name);

    /*!
     * \brief Funkcja odpowiedzialna za zapis obiektu do pliku.
     * Zapisuje ona obiekt do pliku o nazwie takiej jak nazwa obiektu wykorzystując mechanizm serializacji z biblioteki boost
     */
    void save();

    /*!
     * \brief Funkcja odpowiedzialna za odczyt obiektu z pliku.
     * Wczytuje ona obiekt z pliku o nazwie podanej jako argument metody wykorzystując mechanizm serializacji z biblioteki boost
     * \param fileName Nazwa pliku do wczytania
     * \return Wskaźnik na utworzony obiekt
     */
    static Serializable* load(const std::string& fileName);

protected:
    /*!
     * \brief Funkcja odpowiedzialna za zobsługę serializacji z biblioteki boost.
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(m_name);
    }

    friend class boost::serialization::access;

    ///Nazwa obiektu, jednocześnie pliku po serializacji
    std::string m_name;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Serializable)

#endif // OBJECT_H
