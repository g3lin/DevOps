#define CATCH_CONFIG_MAIN

// RTFM catch2:
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

#include "catch.hpp"
#include <argc.h>
#include <buildus.h>




TEST_CASE("Lecture du fichier") {
	REQUIRE(getNbArgc(1) == false);
	REQUIRE(getNbArgc(3) == false);
	REQUIRE(getNbArgc(2) == true);

	REQUIRE(checkArgv("test.txt") == false);
	REQUIRE(checkArgv("test.buildus") == true);
}


TEST_CASE("Compilation minimale"){

}

TEST_CASE("Enregistrement .o"){
	getConfig("config.buildus");


}

TEST_CASE("generation executable"){

}

TEST_CASE("clean intermediate"){

}




