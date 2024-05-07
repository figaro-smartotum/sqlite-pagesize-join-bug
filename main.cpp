#include <iostream>
#include "./sqlite3.h"

const char *DATABASE_FILE = "../haccp.sqlite";

void perform_left_join_query() {

    sqlite3 *db;
    char *errMsg{nullptr};
    int rc;

    rc = sqlite3_open_v2(DATABASE_FILE,
                         &db,
                         SQLITE_OPEN_READONLY,
                         "demo");
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *select_sql = "SELECT "
                             " haccpDetail.uuid "
                             // Everything work if I use an INNER JOIN
                             " FROM haccp LEFT JOIN haccpDetail ON haccpDetail.haccpUuid = haccp.uuid";

    sqlite3_stmt *stmt_select;
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt_select, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    while ((rc = sqlite3_step(stmt_select)) == SQLITE_ROW)
    {
        printf("Found UUID: %u\n", sqlite3_column_int(stmt_select, 0));
    }

    sqlite3_finalize(stmt_select);

    sqlite3_close(db);
}

int main(int argc, char **argv) {
    auto rc = sqlite3_initialize();
    if (rc != SQLITE_OK)
        exit(1);

    perform_left_join_query();

    return 0;
}
