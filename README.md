# Disk I/O error when SQLITE_DEFAULT_PAGE_SIZE<2048 bytes

Steps to build
```
mkdir build
cd build
cmake ..
cmake --build .
```
Run the execuable from the `build/` folder.
The application needs to find `../haccp.sqlite` file.

`./sqlite_vfs_example`

The expected output from SQLite callbacks log is:
```
[Demo VFS Log] (Err code: 284) automatic index on haccpDetail(haccpUuid)
[Demo VFS Log] (Err code: 10) statement aborts at 13: [SELECT  haccpDetail.uuid  FROM haccp LEFT JOIN haccpDetail ON haccpDetail.haccpUuid = haccp.uuid] disk I/O error
```

The problem is solved if one of the following condiions is met:
- `SQLITE_DEFAULT_PAGE_SIZE=2048` compile definition is used
- an `INNER JOIN` instead of a `LEFT JOIN` is used
- the automatic-index feature is not used, and the index on the `haccpDetail.haccpUuid` field is defined in the schema.