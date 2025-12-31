#pragma once

#include <string>
#include <cstdint>
#include <compare>

namespace amb {

class Version {
private:
    uint32_t major_ = 0;
    uint32_t minor_ = 0;
    uint32_t patch_ = 0;
    std::string prerelease_;
    std::string build_;
    
public:
    // Constructors
    Version() = default;
    Version(uint32_t major, uint32_t minor, uint32_t patch = 0)
        : major_(major), minor_(minor), patch_(patch) {}
    
    explicit Version(const std::string& str) { fromString(str); }
    
    // Getters
    uint32_t major() const { return major_; }
    uint32_t minor() const { return minor_; }
    uint32_t patch() const { return patch_; }
    const std::string& prerelease() const { return prerelease_; }
    const std::string& build() const { return build_; }
    
    // Conversion
    std::string toString() const;
    bool fromString(const std::string& str);
    
    // Validation
    bool isValid() const { return true; } // Simplified for MVP
    
    // Comparison operators
    std::strong_ordering operator<=>(const Version& other) const;
    bool operator==(const Version& other) const = default;
    
    // Range checking
    bool satisfies(const std::string& range) const; // For future use
};

// Current version of amb
extern const Version AMB_VERSION;

} // namespace amb