# SQLite tcl interface
Write Programs That Use SQLite
Below is a simple TCL program that demonstrates how to use the TCL interface to SQLite. The program executes the SQL statements given as the second argument on the database defined by the first argument. The commands to watch for are the sqlite3 command on line 7 which opens an SQLite database and creates a new object named "db" to access that database, the use of the eval method on the db object on line 8 to run SQL commands against the database, and the closing of the database connection on the last line of the script.
```
01  #!/usr/bin/tclsh
02  if {$argc!=2} {
03    puts stderr "Usage: %s DATABASE SQL-STATEMENT"
04    exit 1
05  }
06  package require sqlite3
07  sqlite3 db [lindex $argv 0]
08  db eval [lindex $argv 1] x {
09    foreach v $x(*) {
10      puts "$v = $x($v)"
11    }
12    puts ""
13  }
14  db close
```

https://www.sqlite.org/quickstart.html
---
# SQLite C Interface

The database connection and prepared statement objects are controlled by a small set of C/C++ interface routine listed below.

sqlite3_open()
sqlite3_prepare()
sqlite3_step()
sqlite3_column()
sqlite3_finalize()
sqlite3_close()

## object types
- sqlite3 → The database connection object. Created by sqlite3_open() and destroyed by sqlite3_close().
- sqlite3_stmt → The prepared statement object. Created by sqlite3_prepare() and destroyed by sqlite3_finalize().
## functions 
- sqlite3_open() → Open a connection to a new or existing SQLite database. The constructor for sqlite3.
- sqlite3_prepare() → Compile SQL text into byte-code that will do the work of querying or updating the database. The constructor for sqlite3_stmt.
- sqlite3_step() → Advance an sqlite3_stmt to the next result row or to completion.
- sqlite3_column() → Column values in the current result row for an sqlite3_stmt.
- sqlite3_finalize() → Destructor for sqlite3_stmt.
- sqlite3_close() → Destructor for sqlite3.
- sqlite3_exec() → A wrapper function that does sqlite3_prepare(), sqlite3_step(), sqlite3_column(), and sqlite3_finalize() for a string of one or more SQL statements.

---
### One-Step Query Execution Interface
```C
int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);
```
---
## SQLite features 
- Shared Cache Mode → Version 3.3.0 and later supports the ability for two or more database connections to share the same page and schema cache. This feature is useful for certain specialized applications.
- URI Filenames → The names of database files can be specified using either an ordinary filename or a URI. Using URI filenames provides additional capabilities, as this document describes.
---
### [Uniform Resource Identifiers](https://www.sqlite.org/uri.html)
* URI Filenames In SQLite
>Beginning with version 3.7.7 (2011-06-23), the SQLite database file argument to the sqlite3_open(), sqlite3_open16(), and sqlite3_open_v2() interfaces and to the ATTACH command can be specified either as an ordinary filename or as a Uniform Resource Identifier or URI. The advantage of using a URI filename is that query parameters on the URI can be used to control details of the newly created database connection. For example, an alternative VFS can be specified using a "vfs=" query parameter. Or the database can be opened read-only by using "mode=ro" as a query parameter.
* what is URI Filenames
>If URI filename interpretation is enabled, and the filename argument begins with "file:", then the filename is interpreted as a URI.
[examples](https://www.sqlite.org/c3ref/open.html#urifilenameexamples)

