#ifndef __sometuke__ios_assets_loader__
#define __sometuke__ios_assets_loader__

#include "sometuke/assets_loader.h"
#include "sometuke/ios/devices.h"

namespace sometuke {

using namespace std;

class IOSAssetsLoader : public AssetsLoader {
public:
    IOSAssetsLoader() {
        suffixes_[kiPhone]              = "";
        suffixes_[kiPhoneRetinaDisplay] = "@x2";
        suffixes_[kiPad]                = "-ipad";
        suffixes_[kiPadRetinaDisplay]   = "-ipad@x2";
    }

    vector<char> ReadBytes(const string& relative_path);
    shared_ptr<Texture2D> ReadTexture(const string &relative_path);
    string ReadString(const string& relative_path);
    const string FullPathFromRelativePath(const string& relative_path);

private:
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

#endif /* defined(__sometuke__ios_assets_loader__) */
