/*-------------------------------------------------------------------------
 *
 *   FILE
 *	pglobject.cc
 *
 *   DESCRIPTION
 *      implementation of the PgLargeObject class.
 *   PgLargeObject encapsulates a frontend to backend connection
 *
 * Copyright (c) 1994, Regents of the University of California
 *
 * IDENTIFICATION
 *	  $Header: /cvsroot/pgsql-server/src/interfaces/libpq++/Attic/pglobject.cc,v 1.8 2001/09/30 22:30:37 tgl Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "pglobject.h"
 
extern "C" {
#include "libpq/libpq-fs.h"
}

#ifdef HAVE_NAMESPACE_STD
using namespace std;
#endif


// ****************************************************************
//
// PgLargeObject Implementation
//
// ****************************************************************
// default constructor
// creates a large object in the default database
// See PQconnectdb() for conninfo usage
PgLargeObject::PgLargeObject(const char* conninfo)
	: PgConnection(conninfo)
{
  Init();
  if (! ConnectionBad()) {
	  Create();
	  Open();
  }
}

// constructor
// open an existing large object in the default database
// See PQconnectdb() for conninfo usage
PgLargeObject::PgLargeObject(Oid lobjId, const char* conninfo) 
	: PgConnection(conninfo)
{
  Init(lobjId);
  if (! ConnectionBad()) {
	  if ( !pgObject )
		  Create();
	  Open();
  }
}

// destructor -- closes large object
PgLargeObject::~PgLargeObject()
{
  Close();
}

// PgLargeObject::Init
// Initialize the variables
void PgLargeObject::Init(Oid lobjId)
{
  pgFd = -1;
  pgObject = lobjId;
}

// PgLargeObject::create
// create large object and check for errors
void PgLargeObject::Create()
{
  // Create the object
  pgObject = lo_creat(pgConn, INV_READ|INV_WRITE);
  
  // Check for possible errors
  if (!pgObject)
	loStatus = "PgLargeObject: can't create large object" ;
  else
	loStatus = "PgLargeObject: created large object" ;
}

// PgLargeObject::open
// open large object and check for errors
void PgLargeObject::Open()
{
  // Close any prior object
  Close();
  // Open the object
  pgFd = lo_open(pgConn, pgObject, INV_READ|INV_WRITE);
  
  // Check for possible errors
  string objStr( IntToString(pgObject) );
  if (pgFd < 0)
      loStatus = "PgLargeObject: can't open large object " + objStr ;
  else
      loStatus = "PgLargeObject: created and opened large object " + objStr ;
}

// PgLargeObject::unlink
// destruct large object and delete from it from the database
int PgLargeObject::Unlink()
{
  // Unlink the object
  int temp = lo_unlink(pgConn, pgObject);
  
  // Initialize the large object upon success
  if (!temp) {
      Close();
      Init();
  }
  
  // Return the status
  return temp;
}



void PgLargeObject::Close()
{ 
  if (pgFd >= 0) lo_close(pgConn, pgFd);
  pgFd = -1;
}


int PgLargeObject::Read(char* buf, int len)
{ 
  return lo_read(pgConn, pgFd, buf, len); 
}


int PgLargeObject::Write(const char* buf, int len)
{ 
  return lo_write(pgConn, pgFd, (char*)buf, len); 
}


int PgLargeObject::LSeek(int offset, int whence)
{ 
  return lo_lseek(pgConn, pgFd, offset, whence); 
}


int PgLargeObject::Tell() const
{ 
  return lo_tell(pgConn, pgFd); 
}


Oid PgLargeObject::Import(const char* filename) 
{ 
  return pgObject = lo_import(pgConn, (char*)filename); 
}


int PgLargeObject::Export(const char* filename) 
{ 
  return lo_export(pgConn, pgObject, (char*)filename); 
}


string PgLargeObject::Status() const
{ 
  return loStatus; 
}
