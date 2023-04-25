#ifndef PROOF_OF_WORK_H
#define PROOF_OF_WORK_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

class ProofOfWork {
public:
    static std::string generateProofOfWork(const std::string& message, const int difficulty) {
        std::string target(difficulty, '0');
        std::string nonce = "";
        std::string hash;
        int i = 0;

        while (hash.substr(0, difficulty) != target) {
            nonce = std::to_string(i);
            hash = sha256(message + nonce);
            i++;
        }

        return nonce;
    }

private:
    static std::string sha256(const std::string str) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, str.c_str(), str.length());
        SHA256_Final(hash, &sha256);
        std::stringstream ss;

        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }

        return ss.str();
    }
};

#endif // PROOF_OF_WORK_H
