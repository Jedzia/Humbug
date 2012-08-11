#ifndef TEMPLATES_DESIGNPATTERNS_FACTORYMETHOD_H
#define TEMPLATES_DESIGNPATTERNS_FACTORYMETHOD_H


#include "../global.h"
//
namespace templates {

namespace designpatterns {

//! See S:\!Nachschlagewerke\Programmieren\MDA-Design\
//!   refactoring-to-patterns-the-addison-wesley-signature-series.9780321213358.26020.chm
//!   Chapter 6
//! and S:\!Nachschlagewerke\UML
//!  Applying_UML_and_Patterns_An_Introduction_to_Object-Oriented_Analysis_and_Design_and_Iterative_Development_3rd_Edition.chm
//!  Section 26.4
//! and S:\!Nachschlagewerke\UML\Visual Paradigm\Tutorials
//!  factorymethod.pdf
//!
class PLATFORM_DECL Product {
};
class PLATFORM_DECL ConcreteProduct : public Product {
};
//! Abstract base class for Product creator.
class PLATFORM_DECL Creator {
  public:
    //! Creates a new instance of a Product.
    /// \abstract Overwrite this method in new Product implementations. 
    virtual Product * FactoryMethod() = 0;

    void anOperation();

    virtual ~Creator();

};
//! The Factory.
/// Creates objects of the Product type.
class PLATFORM_DECL ConcreteCreator : public Creator {
  public:
    //! Creates a new instance of a Product.
    /// \overridden In this implementation this function returns only ConcreteProduct's.
    virtual Product * FactoryMethod();

};

} // namespace templates::designpatterns

} // namespace templates
#endif
