#define CATCH_CONFIG_MAIN

// RTFM catch2:
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

#include "catch.hpp"

#include <dummy.h>

#include <argc.h>


TEST_CASE("is the world ok") {
	REQUIRE(GetAnswerToLifeUniverseAndEverything() == 42);
	REQUIRE(GetAnswerToLifeUniverseAndEverything() != 41);
	REQUIRE(GetAnswerToLifeUniverseAndEverything() != 43);
}

TEST_CASE("Test du nombre d'arguements places en parametre") {
	REQUIRE(getNbArgc(1) == false);
	REQUIRE(getNbArgc(3) == false);
	REQUIRE(getNbArgc(2) == true);
}


