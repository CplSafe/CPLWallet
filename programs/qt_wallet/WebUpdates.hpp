#pragma once

#include <ohl/blockchain/config.hpp>
#include <ohl/blockchain/types.hpp>

#include <fc/io/json.hpp>
#include <fc/reflect/reflect.hpp>
#include <fc/time.hpp>

#include <set>
#include <vector>

const static char*                                          WEB_UPDATES_MANIFEST_URL = "https://ohlshares.org/manifest.json";
const static uint8_t                                        WEB_UPDATES_SIGNATURE_REQUIREMENT = 2;
const static std::unordered_set<ohl::blockchain::address>   WEB_UPDATES_SIGNING_KEYS ({
    ohl::blockchain::address( OHL_ADDRESS_PREFIX + std::string( "29Q5JSk35JXqLhdDeYxjtFNveEuavHacJ" ) ),
    ohl::blockchain::address( OHL_ADDRESS_PREFIX + std::string( "2xE2fG2uSKRp6TUZJ5rhucLwTKHi3r3oo" ) ),
    ohl::blockchain::address( OHL_ADDRESS_PREFIX + std::string( "HGPxYjgsDuhtCineuaC4P4r9jZWMBue1W" ) ),
    ohl::blockchain::address( OHL_ADDRESS_PREFIX + std::string( "62VST9FZZVMtTKurzzfpK9hp9sijQjkT3" ) )
});

struct WebUpdateManifest
{
    struct UpdateDetails
    {
        //The version number; must be unique within the manifest.
        //An update will only be installed in a client whose major, fork, and
        //minor versions match those of the update.
        uint8_t majorVersion;
        uint8_t forkVersion;
        uint8_t minorVersion;
        //Patch version is formatted as a char.
        uint8_t patchVersion;

        //Set of signatures for this update; must contain signatures
        //corresponding to at least WEB_UPDATES_SIGNATURE_REQUIREMENT unique
        //keys in WEB_UPDATES_SIGNING_KEYS.
        std::unordered_set<fc::ecc::compact_signature> signatures;

        //Human-readable description of update. May include description,
        //changelog, known issues, etc.
        std::string releaseNotes;

        //Full URL (i.e. https://ohlshares.org/toolkit/updates/0.2.4-c.pak)
        //to update package.
        std::string updatePackageUrl;

        //Timestamp of update
        fc::time_point_sec timestamp;

        UpdateDetails()
            : majorVersion(0),
              forkVersion(4),
              minorVersion(16),
              patchVersion('a')
        {}

        bool operator< (const UpdateDetails& other) const
        {
            if (majorVersion != other.majorVersion) return majorVersion < other.majorVersion;
            if (forkVersion != other.forkVersion) return forkVersion < other.forkVersion;
            if (minorVersion != other.minorVersion) return minorVersion < other.minorVersion;
            return patchVersion < other.patchVersion;
        }

        std::string signable_string() {
            UpdateDetails ud = *this;
            ud.signatures.clear();
            return fc::json::to_string(ud);
        }
    };

    std::set<UpdateDetails> updates;
};

FC_REFLECT(WebUpdateManifest::UpdateDetails, (majorVersion)(forkVersion)(minorVersion)(patchVersion)(signatures)(releaseNotes)(updatePackageUrl)(timestamp))
FC_REFLECT(WebUpdateManifest, (updates))
