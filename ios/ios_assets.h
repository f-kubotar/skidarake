#ifndef __kawaii__ios_assets__
#define __kawaii__ios_assets__

#include "kawaii/assets.h"
#include "kawaii/ios/platform.h"

namespace kawaii {

using namespace std;

class IOSAssets : public Assets {
public:
    IOSAssets() {
        suffixes_[kiPhone]              = "";
        suffixes_[kiPhoneRetinaDisplay] = "@x2";
        suffixes_[kiPad]                = "-ipad";
        suffixes_[kiPadRetinaDisplay]   = "-ipad@x2";
    }

    vector<char> ReadBytes(const string& relative_path);
    shared_ptr<Texture2D> ReadTexture(const string &relative_path);
    string ReadString(const string& relative_path);

private:
    const string FullPathFromRelativePath(const string& relative_path);

    bool EndsWith(const string& str, const string& suffix) {
        if (str.length() >= suffix.length()) {
            return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
        } else {
            return false;
        }
    }

    string suffixes_[kDevice_MAX];
};

} 

#endif /* defined(__kawaii__ios_assets__) */
