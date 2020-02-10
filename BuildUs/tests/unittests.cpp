#define CATCH_CONFIG_MAIN

// RTFM catch2:
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

#include "catch.hpp"

#include <dummy.h>


TEST_CASE("is the world ok") {
	REQUIRE(GetAnswerToLifeUniverseAndEverything() == 42);
	REQUIRE(GetAnswerToLifeUniverseAndEverything() != 41);
	REQUIRE(GetAnswerToLifeUniverseAndEverything() != 43);
}

/**
TEST_CASE("Test commande 'init'") {
	// Verifier si les fonctions s'executent bien
	REQUIRE(getInitHelp() == true);
	REQUIRE(setInit() == true);
	
	// Verifier si les dossiers/fichiers sont bien crees
	REQUIRE(checkInit() == true);
	
}

TEST_CASE("Test commande 'add'") {
	// Verifier si les fonctions s'executent bien
	REQUIRE(getAddHelp() == true);

	const char* file_to_add = "test.txt";
	REQUIRE(setAddFile(file_to_add) == true);

	// Verifier le rapport entre les dossiers/fichiers creent et index
	REQUIRE(checkAdd() == true);

}*/
