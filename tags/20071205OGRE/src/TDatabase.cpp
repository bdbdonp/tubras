//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"


namespace Tubras
{
    int sqlite3_callback(void* userData,int cols,char** values, char** colNames)
    {
        int rc = 0;
        if(userData)
        {
            ((TDatabase*)userData)->callback(cols,values,colNames);
        }
        return rc;
    }

    //-----------------------------------------------------------------------
    //                          T D a t a b a s e 
    //-----------------------------------------------------------------------
    TDatabase::TDatabase()
    {
        m_lastError = NULL;
        m_rowCount = 0;
    }

    //-----------------------------------------------------------------------
    //                         ~ T D a t a b a s e 
    //-----------------------------------------------------------------------
    TDatabase::~TDatabase()
    {
        if(m_db)
            close();
    }

    //-----------------------------------------------------------------------
    //                              o p e n 
    //-----------------------------------------------------------------------
    int TDatabase::open(TString dbName)
    {
        int rc;

        m_dbName = dbName;
        rc = sqlite3_open(m_dbName.c_str(),&m_db);
        if( rc )
        {
            close();
        }
        return rc;
    }

    //-----------------------------------------------------------------------
    //                              c l o s e
    //-----------------------------------------------------------------------
    int TDatabase::close()
    {
        int rc = sqlite3_close(m_db);
        m_db = NULL;
        return rc;
    }

    //-----------------------------------------------------------------------
    //                               e x e c
    //-----------------------------------------------------------------------
    int TDatabase::exec(TString sql)
    {
        m_rowCount = 0;
        int rc = sqlite3_exec(m_db,sql.c_str(),sqlite3_callback,this,&m_lastError);
        return rc;
    }

    //-----------------------------------------------------------------------
    //                           c a l l b a c k
    //-----------------------------------------------------------------------
    int TDatabase::callback(int cols,char** values, char** colNames)
    {
        ++m_rowCount;
        return 0;
    }
}