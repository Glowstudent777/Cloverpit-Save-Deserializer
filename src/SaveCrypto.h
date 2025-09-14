#ifndef SAVECRYPTO_H
#define SAVECRYPTO_H

#include <string>
#include <vector>
#include <cstdint>

class SaveCrypto
{
private:
    static constexpr const char *GAME_PASSWORD = "uoiyiuh_+=-5216gh;lj??!/345";
    static constexpr const char *ACHIEVEMENTS_PASSWORD = "afhjttiojd?s0989sdfl12";

    static int CryptoShiftsNumber(const std::string &password);
    static std::vector<uint8_t> GenerateTempKey(const std::vector<uint8_t> &password);

public:
    static std::vector<uint8_t> Decrypt(const std::vector<uint8_t> &input, const std::string &password);
    static std::vector<uint8_t> DecryptSaveFile(const std::string &filePath, bool isGameData = true);
};

#endif
