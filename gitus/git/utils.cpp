#include "utils.h"

#include "zlib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/uuid/detail/sha1.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>

std::string calculateSHA(const std::string string){
    std::string SHAFinal = "";

    boost::uuids::detail::sha1 sha;
    sha.process_bytes(string.c_str(), string.length());

    unsigned int hash[5];
	sha.get_digest(hash);

	std::stringstream stream;
	for (int i = 0; i < 5; ++i) {
		stream << std::hex << hash[i];
	}
	SHAFinal =  stream.str();

    return SHAFinal;
}

void makeObject(const std::string SHA, const std::string content){
    auto path = boost::filesystem::current_path();

    // Creer le dossier 'content.substr(0, 2)'
    const auto pathFolderContent = path.append(".git/objects/" + SHA.substr(0, 2));
    boost::filesystem::create_directory(pathFolderContent);

	// Creer le fichier 'content' et le remplit
	writeFile(path.append(SHA.substr(2,-1)).c_str(),content);
    

}


// CREDIT POUR LES FONCTIONS readFile et writeFile
// https://stackoverflow.com/a/15108952 et https://stackoverflow.com/questions/34049802/decompress-zlib-with-boost-library

std::string readFile(const std::string filename)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);

    file.seekg (0, std::ios::end);
    const int length = file.tellg();
    file.seekg (0, std::ios::beg);

    std::vector<char> data(length);
    file.read(&data[0], length);
    file.close();

    std::cout << length <<std::endl;

    boost::iostreams::filtering_streambuf<boost::iostreams::input>in;
    in.push(boost::iostreams::zlib_decompressor());
    in.push(boost::make_iterator_range(data));
    std::string decompressed;
    boost::iostreams::copy(in, boost::iostreams::back_inserter(decompressed));


    return decompressed;


}

void writeFile(const std::string filename, const std::string data)
{

    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
	in.push(boost::iostreams::zlib_compressor());
	in.push(boost::make_iterator_range(data));
	std::string compressed;
	boost::iostreams::copy(in, boost::iostreams::back_inserter(compressed));

    std::ofstream file;
    file.open(filename, std::ios::binary);
    file.write(&compressed[0], compressed.size());
    file.close();


}