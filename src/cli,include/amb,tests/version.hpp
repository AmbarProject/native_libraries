#pragma once

#include <string>
#include <cstdint>
#include <compare>

namespace amb {

class Version {
private:
    uint32_t major_;
    uint32_t minor_;
    uint32_t patch_;
    std::string prerelease_;
    std::string build_;
    
public:
    // Construtores
    Version() : major_(0), minor_(0), patch_(0) {}
    Version(uint32_t major, uint32_t minor = 0, uint32_t patch = 0)
        : major_(major), minor_(minor), patch_(patch) {}
    
    // Parsing from string
    static Version fromString(const std::string& str);
    
    // To string
    std::string toString() const;
    
    // Getters
    uint32_t major() const { return major_; }
    uint32_t minor() const { return minor_; }
    uint32_t patch() const { return patch_; }
    const std::string& prerelease() const { return prerelease_; }
    const std::string& build() const { return build_; }
    
    // Comparison operators (C++20 spaceship)
    auto operator<=>(const Version& other) const = default;
    
    // Helper methods
    bool isPrerelease() const { return !prerelease_.empty(); }
    bool isStable() const { return prerelease_.empty(); }
    
    // Compatibility checks
    bool isCompatibleWith(const Version& other) const;
};

// Versão atual do amb
extern const Version AMB_VERSION;

// Versão do protocolo do registry
extern const Version REGISTRY_PROTOCOL_VERSION;

} // namespace amb