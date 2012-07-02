// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "AssetList.hxx"

// rowset
// 

const rowset::row_sequence& rowset::
row () const
{
  return this->row_;
}

rowset::row_sequence& rowset::
row ()
{
  return this->row_;
}

void rowset::
row (const row_sequence& s)
{
  this->row_ = s;
}

const rowset::name_type& rowset::
name () const
{
  return this->name_.get ();
}

rowset::name_type& rowset::
name ()
{
  return this->name_.get ();
}

void rowset::
name (const name_type& x)
{
  this->name_.set (x);
}

void rowset::
name (::std::auto_ptr< name_type > x)
{
  this->name_.set (x);
}

const rowset::key_type& rowset::
key () const
{
  return this->key_.get ();
}

rowset::key_type& rowset::
key ()
{
  return this->key_.get ();
}

void rowset::
key (const key_type& x)
{
  this->key_.set (x);
}

void rowset::
key (::std::auto_ptr< key_type > x)
{
  this->key_.set (x);
}

const rowset::columns_type& rowset::
columns () const
{
  return this->columns_.get ();
}

rowset::columns_type& rowset::
columns ()
{
  return this->columns_.get ();
}

void rowset::
columns (const columns_type& x)
{
  this->columns_.set (x);
}

void rowset::
columns (::std::auto_ptr< columns_type > x)
{
  this->columns_.set (x);
}


// row
// 

const row::rowset_optional& row::
rowset () const
{
  return this->rowset_;
}

row::rowset_optional& row::
rowset ()
{
  return this->rowset_;
}

void row::
rowset (const rowset_type& x)
{
  this->rowset_.set (x);
}

void row::
rowset (const rowset_optional& x)
{
  this->rowset_ = x;
}

void row::
rowset (::std::auto_ptr< rowset_type > x)
{
  this->rowset_.set (x);
}

const row::typeID_type& row::
typeID () const
{
  return this->typeID_.get ();
}

row::typeID_type& row::
typeID ()
{
  return this->typeID_.get ();
}

void row::
typeID (const typeID_type& x)
{
  this->typeID_.set (x);
}

const row::singleton_type& row::
singleton () const
{
  return this->singleton_.get ();
}

row::singleton_type& row::
singleton ()
{
  return this->singleton_.get ();
}

void row::
singleton (const singleton_type& x)
{
  this->singleton_.set (x);
}

const row::quantity_type& row::
quantity () const
{
  return this->quantity_.get ();
}

row::quantity_type& row::
quantity ()
{
  return this->quantity_.get ();
}

void row::
quantity (const quantity_type& x)
{
  this->quantity_.set (x);
}

const row::locationID_optional& row::
locationID () const
{
  return this->locationID_;
}

row::locationID_optional& row::
locationID ()
{
  return this->locationID_;
}

void row::
locationID (const locationID_type& x)
{
  this->locationID_.set (x);
}

void row::
locationID (const locationID_optional& x)
{
  this->locationID_ = x;
}

const row::itemID_type& row::
itemID () const
{
  return this->itemID_.get ();
}

row::itemID_type& row::
itemID ()
{
  return this->itemID_.get ();
}

void row::
itemID (const itemID_type& x)
{
  this->itemID_.set (x);
}

const row::flag_type& row::
flag () const
{
  return this->flag_.get ();
}

row::flag_type& row::
flag ()
{
  return this->flag_.get ();
}

void row::
flag (const flag_type& x)
{
  this->flag_.set (x);
}


// result
// 

const result::rowset_type& result::
rowset () const
{
  return this->rowset_.get ();
}

result::rowset_type& result::
rowset ()
{
  return this->rowset_.get ();
}

void result::
rowset (const rowset_type& x)
{
  this->rowset_.set (x);
}

void result::
rowset (::std::auto_ptr< rowset_type > x)
{
  this->rowset_.set (x);
}


// eveapi
// 

const eveapi::currentTime_type& eveapi::
currentTime () const
{
  return this->currentTime_.get ();
}

eveapi::currentTime_type& eveapi::
currentTime ()
{
  return this->currentTime_.get ();
}

void eveapi::
currentTime (const currentTime_type& x)
{
  this->currentTime_.set (x);
}

void eveapi::
currentTime (::std::auto_ptr< currentTime_type > x)
{
  this->currentTime_.set (x);
}

const eveapi::result_type& eveapi::
result () const
{
  return this->result_.get ();
}

eveapi::result_type& eveapi::
result ()
{
  return this->result_.get ();
}

void eveapi::
result (const result_type& x)
{
  this->result_.set (x);
}

void eveapi::
result (::std::auto_ptr< result_type > x)
{
  this->result_.set (x);
}

const eveapi::cachedUntil_type& eveapi::
cachedUntil () const
{
  return this->cachedUntil_.get ();
}

eveapi::cachedUntil_type& eveapi::
cachedUntil ()
{
  return this->cachedUntil_.get ();
}

void eveapi::
cachedUntil (const cachedUntil_type& x)
{
  this->cachedUntil_.set (x);
}

void eveapi::
cachedUntil (::std::auto_ptr< cachedUntil_type > x)
{
  this->cachedUntil_.set (x);
}

const eveapi::version_type& eveapi::
version () const
{
  return this->version_.get ();
}

eveapi::version_type& eveapi::
version ()
{
  return this->version_.get ();
}

void eveapi::
version (const version_type& x)
{
  this->version_.set (x);
}


// name
// 

name::
name (value v)
: ::xml_schema::string (_xsd_name_literals_[v])
{
}

name::
name (const char* v)
: ::xml_schema::string (v)
{
}

name::
name (const ::std::string& v)
: ::xml_schema::string (v)
{
}

name::
name (const ::xml_schema::string& v)
: ::xml_schema::string (v)
{
}

name::
name (const name& v,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::string (v, f, c)
{
}

name& name::
operator= (value v)
{
  static_cast< ::xml_schema::string& > (*this) = 
  ::xml_schema::string (_xsd_name_literals_[v]);

  return *this;
}


// key
// 

key::
key (value v)
: ::xml_schema::string (_xsd_key_literals_[v])
{
}

key::
key (const char* v)
: ::xml_schema::string (v)
{
}

key::
key (const ::std::string& v)
: ::xml_schema::string (v)
{
}

key::
key (const ::xml_schema::string& v)
: ::xml_schema::string (v)
{
}

key::
key (const key& v,
     ::xml_schema::flags f,
     ::xml_schema::container* c)
: ::xml_schema::string (v, f, c)
{
}

key& key::
operator= (value v)
{
  static_cast< ::xml_schema::string& > (*this) = 
  ::xml_schema::string (_xsd_key_literals_[v]);

  return *this;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// rowset
//

rowset::
rowset (const name_type& name,
        const key_type& key,
        const columns_type& columns)
: ::xml_schema::type (),
  row_ (::xml_schema::flags (), this),
  name_ (name, ::xml_schema::flags (), this),
  key_ (key, ::xml_schema::flags (), this),
  columns_ (columns, ::xml_schema::flags (), this)
{
}

rowset::
rowset (const rowset& x,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  row_ (x.row_, f, this),
  name_ (x.name_, f, this),
  key_ (x.key_, f, this),
  columns_ (x.columns_, f, this)
{
}

rowset::
rowset (const xercesc::DOMElement& e,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  row_ (f, this),
  name_ (f, this),
  key_ (f, this),
  columns_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
    this->parse (p, f);
  }
}

void rowset::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // row
    //
    if (n.name () == "row" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< row_type > r (
        row_traits::create (i, f, this));

      this->row_.push_back (r);
      continue;
    }

    break;
  }

  while (p.more_attributes ())
  {
    const xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "name" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< name_type > r (
        name_traits::create (i, f, this));

      this->name_.set (r);
      continue;
    }

    if (n.name () == "key" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< key_type > r (
        key_traits::create (i, f, this));

      this->key_.set (r);
      continue;
    }

    if (n.name () == "columns" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< columns_type > r (
        columns_traits::create (i, f, this));

      this->columns_.set (r);
      continue;
    }
  }

  if (!name_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "name",
      "");
  }

  if (!key_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "key",
      "");
  }

  if (!columns_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "columns",
      "");
  }
}

rowset* rowset::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class rowset (*this, f, c);
}

rowset::
~rowset ()
{
}

// row
//

row::
row (const typeID_type& typeID,
     const singleton_type& singleton,
     const quantity_type& quantity,
     const itemID_type& itemID,
     const flag_type& flag)
: ::xml_schema::type (),
  rowset_ (::xml_schema::flags (), this),
  typeID_ (typeID, ::xml_schema::flags (), this),
  singleton_ (singleton, ::xml_schema::flags (), this),
  quantity_ (quantity, ::xml_schema::flags (), this),
  locationID_ (::xml_schema::flags (), this),
  itemID_ (itemID, ::xml_schema::flags (), this),
  flag_ (flag, ::xml_schema::flags (), this)
{
}

row::
row (const row& x,
     ::xml_schema::flags f,
     ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  rowset_ (x.rowset_, f, this),
  typeID_ (x.typeID_, f, this),
  singleton_ (x.singleton_, f, this),
  quantity_ (x.quantity_, f, this),
  locationID_ (x.locationID_, f, this),
  itemID_ (x.itemID_, f, this),
  flag_ (x.flag_, f, this)
{
}

row::
row (const xercesc::DOMElement& e,
     ::xml_schema::flags f,
     ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  rowset_ (f, this),
  typeID_ (f, this),
  singleton_ (f, this),
  quantity_ (f, this),
  locationID_ (f, this),
  itemID_ (f, this),
  flag_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
    this->parse (p, f);
  }
}

void row::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // rowset
    //
    if (n.name () == "rowset" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< rowset_type > r (
        rowset_traits::create (i, f, this));

      if (!this->rowset_)
      {
        this->rowset_.set (r);
        continue;
      }
    }

    break;
  }

  while (p.more_attributes ())
  {
    const xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "typeID" && n.namespace_ ().empty ())
    {
      this->typeID_.set (typeID_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "singleton" && n.namespace_ ().empty ())
    {
      this->singleton_.set (singleton_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "quantity" && n.namespace_ ().empty ())
    {
      this->quantity_.set (quantity_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "locationID" && n.namespace_ ().empty ())
    {
      this->locationID_.set (locationID_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "itemID" && n.namespace_ ().empty ())
    {
      this->itemID_.set (itemID_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "flag" && n.namespace_ ().empty ())
    {
      this->flag_.set (flag_traits::create (i, f, this));
      continue;
    }
  }

  if (!typeID_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "typeID",
      "");
  }

  if (!singleton_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "singleton",
      "");
  }

  if (!quantity_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "quantity",
      "");
  }

  if (!itemID_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "itemID",
      "");
  }

  if (!flag_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "flag",
      "");
  }
}

row* row::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class row (*this, f, c);
}

row::
~row ()
{
}

// result
//

result::
result (const rowset_type& rowset)
: ::xml_schema::type (),
  rowset_ (rowset, ::xml_schema::flags (), this)
{
}

result::
result (::std::auto_ptr< rowset_type >& rowset)
: ::xml_schema::type (),
  rowset_ (rowset, ::xml_schema::flags (), this)
{
}

result::
result (const result& x,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  rowset_ (x.rowset_, f, this)
{
}

result::
result (const xercesc::DOMElement& e,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  rowset_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void result::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // rowset
    //
    if (n.name () == "rowset" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< rowset_type > r (
        rowset_traits::create (i, f, this));

      if (!rowset_.present ())
      {
        this->rowset_.set (r);
        continue;
      }
    }

    break;
  }

  if (!rowset_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "rowset",
      "");
  }
}

result* result::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class result (*this, f, c);
}

result::
~result ()
{
}

// eveapi
//

eveapi::
eveapi (const currentTime_type& currentTime,
        const result_type& result,
        const cachedUntil_type& cachedUntil,
        const version_type& version)
: ::xml_schema::type (),
  currentTime_ (currentTime, ::xml_schema::flags (), this),
  result_ (result, ::xml_schema::flags (), this),
  cachedUntil_ (cachedUntil, ::xml_schema::flags (), this),
  version_ (version, ::xml_schema::flags (), this)
{
}

eveapi::
eveapi (const currentTime_type& currentTime,
        ::std::auto_ptr< result_type >& result,
        const cachedUntil_type& cachedUntil,
        const version_type& version)
: ::xml_schema::type (),
  currentTime_ (currentTime, ::xml_schema::flags (), this),
  result_ (result, ::xml_schema::flags (), this),
  cachedUntil_ (cachedUntil, ::xml_schema::flags (), this),
  version_ (version, ::xml_schema::flags (), this)
{
}

eveapi::
eveapi (const eveapi& x,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  currentTime_ (x.currentTime_, f, this),
  result_ (x.result_, f, this),
  cachedUntil_ (x.cachedUntil_, f, this),
  version_ (x.version_, f, this)
{
}

eveapi::
eveapi (const xercesc::DOMElement& e,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  currentTime_ (f, this),
  result_ (f, this),
  cachedUntil_ (f, this),
  version_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
    this->parse (p, f);
  }
}

void eveapi::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // currentTime
    //
    if (n.name () == "currentTime" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< currentTime_type > r (
        currentTime_traits::create (i, f, this));

      if (!currentTime_.present ())
      {
        this->currentTime_.set (r);
        continue;
      }
    }

    // result
    //
    if (n.name () == "result" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< result_type > r (
        result_traits::create (i, f, this));

      if (!result_.present ())
      {
        this->result_.set (r);
        continue;
      }
    }

    // cachedUntil
    //
    if (n.name () == "cachedUntil" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< cachedUntil_type > r (
        cachedUntil_traits::create (i, f, this));

      if (!cachedUntil_.present ())
      {
        this->cachedUntil_.set (r);
        continue;
      }
    }

    break;
  }

  if (!currentTime_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "currentTime",
      "");
  }

  if (!result_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "result",
      "");
  }

  if (!cachedUntil_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "cachedUntil",
      "");
  }

  while (p.more_attributes ())
  {
    const xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "version" && n.namespace_ ().empty ())
    {
      this->version_.set (version_traits::create (i, f, this));
      continue;
    }
  }

  if (!version_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "version",
      "");
  }
}

eveapi* eveapi::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class eveapi (*this, f, c);
}

eveapi::
~eveapi ()
{
}

// name
//

name::
name (const xercesc::DOMElement& e,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::string (e, f, c)
{
  _xsd_name_convert ();
}

name::
name (const xercesc::DOMAttr& a,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::string (a, f, c)
{
  _xsd_name_convert ();
}

name::
name (const ::std::string& s,
      const xercesc::DOMElement* e,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::string (s, e, f, c)
{
  _xsd_name_convert ();
}

name* name::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class name (*this, f, c);
}

name::value name::
_xsd_name_convert () const
{
  ::xsd::cxx::tree::enum_comparator< char > c (_xsd_name_literals_);
  const value* i (::std::lower_bound (
                    _xsd_name_indexes_,
                    _xsd_name_indexes_ + 2,
                    *this,
                    c));

  if (i == _xsd_name_indexes_ + 2 || _xsd_name_literals_[*i] != *this)
  {
    throw ::xsd::cxx::tree::unexpected_enumerator < char > (*this);
  }

  return *i;
}

const char* const name::
_xsd_name_literals_[2] =
{
  "assets",
  "contents"
};

const name::value name::
_xsd_name_indexes_[2] =
{
  ::name::assets,
  ::name::contents
};

// key
//

key::
key (const xercesc::DOMElement& e,
     ::xml_schema::flags f,
     ::xml_schema::container* c)
: ::xml_schema::string (e, f, c)
{
  _xsd_key_convert ();
}

key::
key (const xercesc::DOMAttr& a,
     ::xml_schema::flags f,
     ::xml_schema::container* c)
: ::xml_schema::string (a, f, c)
{
  _xsd_key_convert ();
}

key::
key (const ::std::string& s,
     const xercesc::DOMElement* e,
     ::xml_schema::flags f,
     ::xml_schema::container* c)
: ::xml_schema::string (s, e, f, c)
{
  _xsd_key_convert ();
}

key* key::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class key (*this, f, c);
}

key::value key::
_xsd_key_convert () const
{
  ::xsd::cxx::tree::enum_comparator< char > c (_xsd_key_literals_);
  const value* i (::std::lower_bound (
                    _xsd_key_indexes_,
                    _xsd_key_indexes_ + 1,
                    *this,
                    c));

  if (i == _xsd_key_indexes_ + 1 || _xsd_key_literals_[*i] != *this)
  {
    throw ::xsd::cxx::tree::unexpected_enumerator < char > (*this);
  }

  return *i;
}

const char* const key::
_xsd_key_literals_[1] =
{
  "itemID"
};

const key::value key::
_xsd_key_indexes_[1] =
{
  ::key::itemID
};

#include <ostream>

::std::ostream&
operator<< (::std::ostream& o, const rowset& i)
{
  for (rowset::row_const_iterator
       b (i.row ().begin ()), e (i.row ().end ());
       b != e; ++b)
  {
    o << ::std::endl << "row: " << *b;
  }

  o << ::std::endl << "name: " << i.name ();
  o << ::std::endl << "key: " << i.key ();
  o << ::std::endl << "columns: " << i.columns ();
  return o;
}

::std::ostream&
operator<< (::std::ostream& o, const row& i)
{
  if (i.rowset ())
  {
    o << ::std::endl << "rowset: " << *i.rowset ();
  }

  o << ::std::endl << "typeID: " << i.typeID ();
  o << ::std::endl << "singleton: " << i.singleton ();
  o << ::std::endl << "quantity: " << i.quantity ();
  if (i.locationID ())
  {
    o << ::std::endl << "locationID: " << *i.locationID ();
  }

  o << ::std::endl << "itemID: " << i.itemID ();
  o << ::std::endl << "flag: " << i.flag ();
  return o;
}

::std::ostream&
operator<< (::std::ostream& o, const result& i)
{
  o << ::std::endl << "rowset: " << i.rowset ();
  return o;
}

::std::ostream&
operator<< (::std::ostream& o, const eveapi& i)
{
  o << ::std::endl << "currentTime: " << i.currentTime ();
  o << ::std::endl << "result: " << i.result ();
  o << ::std::endl << "cachedUntil: " << i.cachedUntil ();
  o << ::std::endl << "version: " << i.version ();
  return o;
}

::std::ostream&
operator<< (::std::ostream& o, name::value i)
{
  return o << name::_xsd_name_literals_[i];
}

::std::ostream&
operator<< (::std::ostream& o, const name& i)
{
  return o << static_cast< const ::xml_schema::string& > (i);
}

::std::ostream&
operator<< (::std::ostream& o, key::value i)
{
  return o << key::_xsd_key_literals_[i];
}

::std::ostream&
operator<< (::std::ostream& o, const key& i)
{
  return o << static_cast< const ::xml_schema::string& > (i);
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::eveapi >
eveapi_ (const ::std::string& u,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::eveapi > r (
    ::eveapi_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::eveapi >
eveapi_ (const ::std::string& u,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::eveapi > r (
    ::eveapi_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::eveapi >
eveapi_ (const ::std::string& u,
         xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::eveapi > r (
    ::eveapi_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::eveapi >
eveapi_ (::std::istream& is,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::eveapi_ (isrc, f, p);
}

::std::auto_ptr< ::eveapi >
eveapi_ (::std::istream& is,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::eveapi_ (isrc, h, f, p);
}

::std::auto_ptr< ::eveapi >
eveapi_ (::std::istream& is,
         xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::eveapi_ (isrc, h, f, p);
}

::std::auto_ptr< ::eveapi >
eveapi_ (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::eveapi_ (isrc, f, p);
}

::std::auto_ptr< ::eveapi >
eveapi_ (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::eveapi_ (isrc, h, f, p);
}

::std::auto_ptr< ::eveapi >
eveapi_ (::std::istream& is,
         const ::std::string& sid,
         xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::eveapi_ (isrc, h, f, p);
}

::std::auto_ptr< ::eveapi >
eveapi_ (xercesc::InputSource& i,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::eveapi > r (
    ::eveapi_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::eveapi >
eveapi_ (xercesc::InputSource& i,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::eveapi > r (
    ::eveapi_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::eveapi >
eveapi_ (xercesc::InputSource& i,
         xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::eveapi > r (
    ::eveapi_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::eveapi >
eveapi_ (const xercesc::DOMDocument& d,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > c (
      static_cast< xercesc::DOMDocument* > (d.cloneNode (true)));

    ::std::auto_ptr< ::eveapi > r (
      ::eveapi_ (
        c, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  const xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "eveapi" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::eveapi > r (
      ::xsd::cxx::tree::traits< ::eveapi, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "eveapi",
    "");
}

::std::auto_ptr< ::eveapi >
eveapi_ (::xml_schema::dom::auto_ptr< xercesc::DOMDocument >& d,
         ::xml_schema::flags f,
         const ::xml_schema::properties&)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "eveapi" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::eveapi > r (
      ::xsd::cxx::tree::traits< ::eveapi, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "eveapi",
    "");
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

void
eveapi_ (::std::ostream& o,
         const ::eveapi& s,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::eveapi_ (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
eveapi_ (::std::ostream& o,
         const ::eveapi& s,
         ::xml_schema::error_handler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::eveapi_ (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
eveapi_ (::std::ostream& o,
         const ::eveapi& s,
         xercesc::DOMErrorHandler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::eveapi_ (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
eveapi_ (xercesc::XMLFormatTarget& t,
         const ::eveapi& s,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::eveapi_ (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
eveapi_ (xercesc::XMLFormatTarget& t,
         const ::eveapi& s,
         ::xml_schema::error_handler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::eveapi_ (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
eveapi_ (xercesc::XMLFormatTarget& t,
         const ::eveapi& s,
         xercesc::DOMErrorHandler& h,
         const ::xml_schema::namespace_infomap& m,
         const ::std::string& e,
         ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::eveapi_ (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
eveapi_ (xercesc::DOMDocument& d,
         const ::eveapi& s,
         ::xml_schema::flags)
{
  xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "eveapi" &&
      n.namespace_ () == "")
  {
    e << s;
  }
  else
  {
    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "eveapi",
      "");
  }
}

::xml_schema::dom::auto_ptr< xercesc::DOMDocument >
eveapi_ (const ::eveapi& s,
         const ::xml_schema::namespace_infomap& m,
         ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::serialize< char > (
      "eveapi",
      "",
      m, f));

  ::eveapi_ (*d, s, f);
  return d;
}

void
operator<< (xercesc::DOMElement& e, const rowset& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // row
  //
  for (rowset::row_const_iterator
       b (i.row ().begin ()), n (i.row ().end ());
       b != n; ++b)
  {
    xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "row",
        e));

    s << *b;
  }

  // name
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "name",
        e));

    a << i.name ();
  }

  // key
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "key",
        e));

    a << i.key ();
  }

  // columns
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "columns",
        e));

    a << i.columns ();
  }
}

void
operator<< (xercesc::DOMElement& e, const row& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // rowset
  //
  if (i.rowset ())
  {
    xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "rowset",
        e));

    s << *i.rowset ();
  }

  // typeID
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "typeID",
        e));

    a << i.typeID ();
  }

  // singleton
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "singleton",
        e));

    a << i.singleton ();
  }

  // quantity
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "quantity",
        e));

    a << i.quantity ();
  }

  // locationID
  //
  if (i.locationID ())
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "locationID",
        e));

    a << *i.locationID ();
  }

  // itemID
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "itemID",
        e));

    a << i.itemID ();
  }

  // flag
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "flag",
        e));

    a << i.flag ();
  }
}

void
operator<< (xercesc::DOMElement& e, const result& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // rowset
  //
  {
    xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "rowset",
        e));

    s << i.rowset ();
  }
}

void
operator<< (xercesc::DOMElement& e, const eveapi& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // currentTime
  //
  {
    xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "currentTime",
        e));

    s << i.currentTime ();
  }

  // result
  //
  {
    xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "result",
        e));

    s << i.result ();
  }

  // cachedUntil
  //
  {
    xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "cachedUntil",
        e));

    s << i.cachedUntil ();
  }

  // version
  //
  {
    xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "version",
        e));

    a << i.version ();
  }
}

void
operator<< (xercesc::DOMElement& e, const name& i)
{
  e << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (xercesc::DOMAttr& a, const name& i)
{
  a << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (::xml_schema::list_stream& l,
            const name& i)
{
  l << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (xercesc::DOMElement& e, const key& i)
{
  e << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (xercesc::DOMAttr& a, const key& i)
{
  a << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (::xml_schema::list_stream& l,
            const key& i)
{
  l << static_cast< const ::xml_schema::string& > (i);
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

