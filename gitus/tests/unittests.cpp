#define CATCH_CONFIG_MAIN

// RTFM catch2:
// https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top

#include "catch.hpp"


#include <init.h>
#include <add.h>
#include <commit.h>



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

}

TEST_CASE("Test commande 'commit'") {
	// Verifier si les fonctions s'executent bien
	REQUIRE(getCommitHelp() == true);

	std::ifstream headFileB(".git/HEAD");
	std::string headBeforeCommit { 
        std::istreambuf_iterator<char>(headFileB), std::istreambuf_iterator<char>() 
    };
	REQUIRE(setCommit("Validation du test", "unitTestUser", "nobody@usherbrooke.ca") == true);
	std::ifstream headFileA(".git/HEAD");
	std::string headAfterCommit { 
        std::istreambuf_iterator<char>(headFileA), std::istreambuf_iterator<char>() 
    };
	REQUIRE(headBeforeCommit != headAfterCommit);
	
	// Verifier si les dossiers/fichiers sont bien crees
	// REQUIRE(checkInit() == true);
	
}