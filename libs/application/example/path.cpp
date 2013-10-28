// -----------------------------------------------------------------------------
// path.cpp : examples that show how use 
// Boost.Application to make a simplest interactive (terminal) application 
//
// Note 1: The Boost.Application (Aspects v4) and this sample are in 
//         development process.
// -----------------------------------------------------------------------------

// Copyright 2011-2013 Renato Tegon Forti
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// -----------------------------------------------------------------------------

#define BOOST_ALL_DYN_LINK
#define BOOST_LIB_DIAGNOSTIC

#include <iostream>
#include <boost/application.hpp>

using namespace boost;

class myapp
{
public:

   // param
   int operator()(application::context& context)
   {
      BOOST_APPLICATION_FEATURE_SELECT

      std::cout << "Test" << std::endl;

      shared_ptr<application::path> path 
         = context.get_aspect<application::path>();

      std::cout << "executable_path      : " << path->executable_path()      << std::endl;
      std::cout << "current_path         : " << path->current_path()         << std::endl;
      std::cout << "executable_name      : " << path->executable_name()      << std::endl;
      std::cout << "executable_full_name : " << path->executable_full_name() << std::endl;
      std::cout << "executable_path_name : " << path->executable_path_name() << std::endl;

      // e.g.: "executable_path      : E:\project.boost.app.v4\libs\application\vc11ide\Debug"
      // e.g.: "current_path         : E:\project.boost.app.v4\libs\application\vc11ide"
      // e.g.: "executable_name      : path"
      // e.g.: "executable_full_name : path.exe"
      // e.g.: "executable_path_name : E:\project.boost.app.v4\libs\application\vc11ide\Debug\path.exe"

      return 0;
   }
};

// main

int main(int argc, char *argv[])
{   
   BOOST_APPLICATION_FEATURE_SELECT

   myapp app;
   application::context app_context;

  app_context.add_aspect<application::path>(
     make_shared<application::path_default_behaviour>(argc, argv));

   return application::launch<application::common>(app, app_context);
}