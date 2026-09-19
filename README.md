# Mini Database Engine

A small C++17 relational database engine supporting `CREATE TABLE`, `INSERT`, `SELECT`, `UPDATE`, `DELETE`, and equality `WHERE` conditions. Tables persist as files in `data/`.

## Build

```powershell
cmake -S . -B build
cmake --build build
./build/minidb_cli.exe
```

GoogleTest is downloaded during configuration when tests are enabled. To build without tests: `cmake -S . -B build -DBUILD_TESTING=OFF`.

## Example

```sql
CREATE TABLE users (id INT, name TEXT);
INSERT INTO users VALUES (1, 'Nitin1');
SELECT * FROM users WHERE id = 1;
UPDATE users SET name = 'Nitin2' WHERE id = 1;
DELETE FROM users WHERE id = 1;
```

The first `INT` column is maintained in a simple B+ tree-style leaf index, rebuilt after table changes and when tables are loaded.
# Mini-DB-Engine
