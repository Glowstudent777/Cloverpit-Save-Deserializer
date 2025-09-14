#include "SaveCrypto.h"
#include <fstream>
#include <stdexcept>
#include <cmath>

int SaveCrypto::CryptoShiftsNumber(const std::string &password)
{
    int shifts = 8;
    for (char c : password)
        shifts += static_cast<unsigned char>(c);
    while (shifts > 16 || shifts < 8)
    {
        if (shifts > 16)
            shifts -= 16;
        if (shifts < 8)
            shifts += 8;
    }
    return shifts;
}

std::vector<uint8_t> SaveCrypto::GenerateTempKey(const std::vector<uint8_t> &password)
{
    std::vector<uint8_t> temp(password.size());
    for (size_t i = 0; i < password.size(); i++)
    {
        int index = std::abs(static_cast<int>(password[i] % password.size()));
        size_t newIndex = (i + index) % password.size();
        temp[i] = password[newIndex];
        temp[i] = static_cast<uint8_t>(temp[i] ^ password[i]);
    }
    return temp;
}

std::vector<uint8_t> SaveCrypto::Decrypt(const std::vector<uint8_t> &input, const std::string &password)
{
    if (input.empty() || password.empty())
        return {};

    int shifts = CryptoShiftsNumber(password);
    (void)shifts;

    std::vector<uint8_t> data = input;

    std::vector<uint8_t> pwdBytes(password.begin(), password.end());
    std::vector<uint8_t> tempKey = GenerateTempKey(pwdBytes);

    for (size_t j = 0; j < data.size(); j++)
    {
        data[j] = static_cast<uint8_t>(data[j] ^ tempKey[j % tempKey.size()]);
    }
    return data;
}

std::vector<uint8_t> SaveCrypto::DecryptSaveFile(const std::string &filePath, bool isGameData)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::vector<uint8_t> encrypted((std::istreambuf_iterator<char>(file)), {});
    std::string password = isGameData ? GAME_PASSWORD : ACHIEVEMENTS_PASSWORD;
    return Decrypt(encrypted, password);
}
