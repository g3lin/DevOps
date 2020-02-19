#define CATCH_CONFIG_MAIN

// RTFM catch2:
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

#include "catch.hpp"
#include <utils.h>
#include <buildus.h>




TEST_CASE("Lecture du fichier") {
	REQUIRE(getNbArgc(1) == false);
	REQUIRE(getNbArgc(3) == false);
	REQUIRE(getNbArgc(2) == true);

	REQUIRE(checkArgv("test.txt") == false);
	REQUIRE(checkArgv("test.buildus") == true);
}

TEST_CASE("clean intermediate"){
	getConfig("config.buildus");
	REQUIRE(checkIfFileExists("intermediate/f1.o") == true);
	REQUIRE(checkIfFileExists("intermediate/.cache") == true);
	cleanIntermediate();
	REQUIRE(checkIfFileExists("intermediate/f1.o") == false);
	REQUIRE(checkIfFileExists("intermediate/.cache") == false);
}


TEST_CASE("Compilation minimale"){
	getConfig("config.buildus");
	std::string OldSHA = getCacheSHA();
	getConfig("config.buildus");
	REQUIRE(OldSHA == getCacheSHA());

	std::fstream mainCompileFile;
	mainCompileFile.open("main.cpp", std::ios::app);
    mainCompileFile << " ";
    mainCompileFile.close();
	getConfig("config.buildus");
	REQUIRE(OldSHA != getCacheSHA());


}

TEST_CASE("Enregistrement .o"){
	getConfig("config.buildus");
	REQUIRE(checkIfFileExists("intermediate/f1.o") == true);
	REQUIRE(checkIfFileExists("intermediate/f2.o") == true);
	cleanIntermediate();
}

TEST_CASE("generation executable"){
	getConfig("config.buildus");
	REQUIRE(checkIfFileExists("app1") == true);
	getConfig("config2.buildus");
	REQUIRE(checkIfFileExists("app1") == true);
}






