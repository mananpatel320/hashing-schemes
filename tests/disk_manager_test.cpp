#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <filesystem>

#define private public

#include "DiskManager.hpp"


class DiskManagerFixture {
private:

    static std::string get_temp_db_path() {
        auto path = std::filesystem::temp_directory_path();
        path /= "temp.db";
        return path;
    }

protected:
    const std::string path = get_temp_db_path();
    DiskManager dm;

    DiskManagerFixture() : dm(DiskManager(path)) {}

public:
    virtual ~DiskManagerFixture() {
        std::filesystem::remove(path);
    }

};

TEST_SUITE("DiskManager") {
    TEST_CASE_FIXTURE(DiskManagerFixture, "Create/open file") {
        REQUIRE(dm.db_file.is_open());
    }

    TEST_CASE_FIXTURE(DiskManagerFixture, "Read/write") {
        auto cur_page = dm.new_page();
        CHECK(cur_page == 0);

        const int page_size = 1 << 16;

        auto* data = new char[page_size];
        auto* read_buf = new char[page_size];
        sprintf(data, "Hello");

        dm.write_page(cur_page, data);
        dm.read_page(cur_page, read_buf);

        CHECK(strcmp(read_buf, "Hello") == 0);
        cur_page = dm.new_page();
        CHECK(cur_page == 1);

        sprintf(data, "World");

        dm.write_page(cur_page, data);
        dm.read_page(cur_page, read_buf);

        CHECK(strcmp(read_buf, "World") == 0);

        delete[] data;
        delete[] read_buf;
    }
}
