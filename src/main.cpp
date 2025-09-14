#include "SaveCrypto.h"
#include <iostream>
#include <fstream>

int main()
{
    try
    {
        std::ifstream inFile("GameDataDemo.json", std::ios::binary);
        if (!inFile)
        {
            std::cerr << "Could not open input file\n";
            return 1;
        }
        std::vector<uint8_t> encrypted((std::istreambuf_iterator<char>(inFile)), {});

        std::vector<uint8_t> decrypted = SaveCrypto::Decrypt(encrypted, "uoiyiuh_+=-5216gh;lj??!/345");

        std::ofstream outFile("GameDataDemo.json", std::ios::binary);
        outFile.write(reinterpret_cast<const char *>(decrypted.data()), decrypted.size());

        std::cout << "Decryption complete.\n";
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
