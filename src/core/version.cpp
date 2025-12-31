#include "amb/version.hpp"
#include <regex>
#include <sstream>

namespace amb {

const Version AMB_VERSION(0, 1, 0);

std::string Version::toString() const {
    std::stringstream ss;
    ss << major_ << "." << minor_ << "." << patch_;
    
    if (!prerelease_.empty()) {
        ss << "-" << prerelease_;
    }
    
    if (!build_.empty()) {
        ss << "+" << build_;
    }
    
    return ss.str();
}

bool Version::fromString(const std::string& str) {
    // Regex simples para MVP
    std::regex pattern(R"(^(\d+)\.(\d+)\.(\d+)(?:-([a-zA-Z0-9.-]+))?(?:\+([a-zA-Z0-9.-]+))?$)");
    std::smatch match;
    
    if (!std::regex_match(str, match, pattern)) {
        return false;
    }
    
    try {
        major_ = std::stoi(match[1]);
        minor_ = std::stoi(match[2]);
        patch_ = std::stoi(match[3]);
        
        if (match[4].matched) {
            prerelease_ = match[4];
        }
        
        if (match[5].matched) {
            build_ = match[5];
        }
        
        return true;
    } catch (...) {
        return false;
    }
}

std::strong_ordering Version::operator<=>(const Version& other) const {
    if (auto cmp = major_ <=> other.major_; cmp != 0) return cmp;
    if (auto cmp = minor_ <=> other.minor_; cmp != 0) return cmp;
    return patch_ <=> other.patch_;
}

bool Version::satisfies(const std::string& range) const {
    // Implementação simplificada para MVP
    // TODO: Implementar SemVer range parsing
    return true;
}

} // namespace amb