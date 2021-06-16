#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "ParserModule"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

#include "../src/document.h"

#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE( parser )
{
    const char* testHtmlFile = STR(TEST_PATH)"/data/example1.html";
    TDocument htmlDocument(testHtmlFile);

    const char* testJsonFile = STR(TEST_PATH)"/data/example1.json";
    TDocument jsonDocument(testJsonFile);

    BOOST_REQUIRE_EQUAL(htmlDocument.Title, jsonDocument.Title);
    BOOST_REQUIRE_EQUAL(htmlDocument.Url, jsonDocument.Url);
    BOOST_REQUIRE_EQUAL(htmlDocument.Description, jsonDocument.Description);
    BOOST_REQUIRE_EQUAL(htmlDocument.SiteName, jsonDocument.SiteName);
    BOOST_REQUIRE_EQUAL(htmlDocument.Author, jsonDocument.Author);
}

