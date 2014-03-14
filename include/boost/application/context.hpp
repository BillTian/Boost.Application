// context.hpp  --------------------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2011-2013 Renato Tegon Forti

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 14-10-2013 dd-mm-yyyy - Initial Release
//
// Note about this LIBRARY
//
// This is a test that add "aspect" concept on Boost.Application interface.
//
// The main purpose of this test is to see how it
// looks and how it behaves in a final use (interface use).
//
// To get older version of Boost.Appliation refer to:
// https://sourceforge.net/projects/boostapp/
// -----------------------------------------------------------------------------

#ifndef BOOST_APPLICATION_CONTEXT_HPP
#define BOOST_APPLICATION_CONTEXT_HPP

// application
#include <boost/application/config.hpp>
#include <boost/application/detail/csbl.hpp>
#include <boost/application/aspect_map.hpp>

namespace boost { namespace application {

namespace detail {
   template <class T> struct T_instance
   {
      static csbl::shared_ptr<T> ptr;
   };

   template <class T> csbl::shared_ptr<T> T_instance<T>::ptr;
} //application::detail

   /*!
    * \brief This class is the base of Boost.Application.
    *        This class can hold any apect, and user can add one,
    *        or use some application modes that will add specifics
    *        aspects to it.
    *
    *        The heavy work is done by aspect_map.
    *
    *        Thanks to Vicente J. Botet Escriba that provide this
    *        important class and concept to the Boost.Application
    *        library.
    *
    * This class hold all aspects of an application.
    * you can use one of the ready-to-use aspects provided by library,
    * or define your own aspects.
    *
    *
    *
    */
   class basic_context
      : public aspect_map, noncopyable
   {
   public:
      // nothing here! Reserved for future use.
   };



   class global_context : public basic_context
   {
   public:
      static inline csbl::shared_ptr<global_context> create()
      {
         boost::mutex::scoped_lock(lock);
         if(already_created())
            BOOST_THROW_EXCEPTION(std::logic_error("global context is already created"));
         instance_t::ptr.reset(new context_t());
         return instance_t::ptr;
      }
      static inline void destroy()
      {
         boost::mutex::scoped_lock(lock);
         if(!already_created())
         BOOST_THROW_EXCEPTION(std::logic_error("no global context to destroy"));
         instance_t::ptr.reset();
      }
      static inline csbl::shared_ptr<global_context> get()
      {
         boost::mutex::scoped_lock(lock);
         if(!already_created())
            BOOST_THROW_EXCEPTION(std::logic_error("there is no global context"));
         return instance_t::ptr;
      }
   protected:
      global_context() { }
   private:
      typedef global_context context_t;
      typedef detail::T_instance<context_t> instance_t;
      typedef csbl::shared_ptr<context_t> context_ptr_t;
      static inline bool already_created() {
          return (instance_t::ptr != 0);
      }
      static boost::mutex lock;
   };
   boost::mutex global_context::lock;


   typedef basic_context context;
   typedef csbl::shared_ptr<global_context> global_context_ptr;
   typedef csbl::shared_ptr<basic_context> context_ptr;

}} // boost::application

#endif // BOOST_APPLICATION_CONTEXT_HPP

